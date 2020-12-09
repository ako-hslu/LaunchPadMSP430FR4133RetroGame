#include <msp430.h> 
#include "driverlib.h"
#include "hal_LCD.h"
#include <stdlib.h>
#include <time.h>
#include "GameLogic.h"
#include "HardwareManager.h"

//Position LCD
#define pos1 4   /* Digit A1 - L4  */
#define pos2 6   /* Digit A2 - L6  */
#define pos3 8   /* Digit A3 - L8  */
#define pos4 10  /* Digit A4 - L10 */
#define pos5 2   /* Digit A5 - L2  */
#define pos6 18  /* Digit A6 - L18 */

//Define Symbols
#define DIAMONDUP   0xA080
#define DIAMONDDOWN 0x0A10
#define BRICKUP     0x00C7
#define BRICKDOWN   0x003B


typedef enum {
    OBJ_EMPTY,
    OBJ_BRICKUP,
    OBJ_BRICKDOWN,
    OBJ_DIAMONDUP,
    OBJ_DIAMONDDOWN
} ObjectType;

GameState gameState = GAMESTATE_INIT;

// Define word access definitions to LCD memories
#define LCDMEMW ((int*)LCDMEM)


int levelSwitch         = 0;
const unsigned int startSpeed    = 50000;
unsigned int speed          = 50000;
int ziffer[6]               = {0};
int leer                    = 180;  //180
int diamantOben             = 210;  //210;
int diamantUnten            = 240;
int steinOben               = 270;  //270;
int steinUnten              = 300;  //300;
unsigned int i              = 0;
unsigned int currentScore   = 0;
unsigned int currentLevel   = 0;
int levelScore              = 10;

unsigned char gateS1IsUp = 0;
unsigned char gateS2IsUp = 0;

void displayDiamondsAndBricks(int c, int position);
void updateGatePosition( void );
void BatLevel(int batt);

void initGameLogic( void )
{
    srand(time(NULL));
    speed = startSpeed;
    levelSwitch = 0;
    int i = 0;
    for(i = 0; i<6; i++)
    {
        ziffer[i] = 0;
    }
    gateS1IsUp = 0;
    gateS2IsUp = 0;
    currentScore = 0;
}


void pushDiamondsAndBricks()
{
    // Zeichen weitergeben und neue zufällig generieren
    for(i = 0; i<5; i++)
    {
        ziffer[i] = ziffer[i+1];
    }
        ziffer[5] = rand() % 300;
 
    updateGatePosition();

    // Auf den Display anzeigen
    displayDiamondsAndBricks(ziffer[0], pos6);
    displayDiamondsAndBricks(ziffer[1], pos5);
    displayDiamondsAndBricks(ziffer[2], pos4);
    displayDiamondsAndBricks(ziffer[3], pos3);
    displayDiamondsAndBricks(ziffer[4], pos2);
    displayDiamondsAndBricks(ziffer[5], pos1);

    // nach 20 Zeichen Spiel schwieriger machen
    if(currentScore == levelScore ) //
    {
        if(currentLevel < 20)
        {
        leer = leer - 4;
        diamantOben = diamantOben - 3;
        diamantUnten = diamantUnten - 2;
        steinOben = steinOben -1;
        speed = speed - 2000;
        levelScore = levelScore+10;
        currentLevel++;
        }
        else
        {
        levelScore = 0;
        }
    }
    

    for(i = 0; i < speed; i++)
    {
        if( i == speed/2){
            updateGatePosition();
        }
        // Geschwindigkeit Zeichenwechsel
    }

    BatLevel(currentLevel);
}

void updateGatePosition( void )
{
    if(S1ButtonSignal == 1)
    {
        S1ButtonSignal = 0;
        if(gateS1IsUp == 0)
        {
            gateS1IsUp = 1;

        }
        else
        {
            gateS1IsUp = 0;

        }

    }
    else if (S2ButtonSignal == 1)
    {
        S2ButtonSignal = 0;
        if(gateS2IsUp == 0 ){
            gateS2IsUp = 1;
            LCDMEMW[pos6/2] &= ~0x0020;
            LCDMEMW[pos6/2] |= 0x0040;
        }
        else
        {
            gateS2IsUp = 0;
            LCDMEMW[pos6/2] |= 0x0020;
            LCDMEMW[pos6/2] &= ~0x0040;

        }
    }
}


void displayDiamondsAndBricks(int c, int position)
{
    ObjectType objType = OBJ_EMPTY;
    if (c <= leer)
    {
        // Display space
        LCDMEMW[position/2] = 0;
    }
    else if (c > leer && c <= diamantOben)
    {
        // Display Diamant up
        LCDMEMW[position/2] = DIAMONDUP;
        objType = OBJ_DIAMONDUP;
    }
    else if (c > diamantOben && c <= diamantUnten)
    {
        // Display Diamant down
        LCDMEMW[position/2] = DIAMONDDOWN;
        objType = OBJ_DIAMONDDOWN;
    }
    else if (c > diamantUnten && c <= steinOben)
    {
        // Display Stone up
        LCDMEMW[position/2] = BRICKUP;
        objType = OBJ_BRICKUP;

    }
    else if (c > steinOben && c <= steinUnten)
    {
        // Display Stone down
        LCDMEMW[position/2] = BRICKDOWN;
        objType = OBJ_BRICKDOWN;
    }
    else
    {
        // Display Stone down
        LCDMEMW[position/2] = BRICKDOWN;  // FAFF
        objType = OBJ_BRICKDOWN;
    }
    if( position == pos6)
    {
        // gate S2 down: 0x0020;
        // gate S2 up: 0x0040;
        if(gateS2IsUp == 1)
        {
            LCDMEMW[position/2] |= 0x0040;
            if(objType == OBJ_BRICKDOWN || objType == OBJ_DIAMONDUP )
            {
                currentScore++;
            }

            if( objType == OBJ_BRICKUP || objType == OBJ_DIAMONDDOWN )
            {
                gameState = GAMESTATE_GAMEOVER;
            }

        }
        else
        {
            // gate is down
            if(objType == OBJ_BRICKUP || objType == OBJ_DIAMONDDOWN )
            {
                currentScore++;
            }

            if( objType == OBJ_BRICKDOWN || objType == OBJ_DIAMONDUP)
            {
                gameState = GAMESTATE_GAMEOVER;
            }

            LCDMEMW[position/2] |= 0x0020;
        }
    }
}

void BatLevel(int batt)
{if(batt ==1){
        LCDMEM[13]=0b1;
        LCDMEM[12]=0b10000000;
    }
    else if(batt==2){
        LCDMEM[13]=0b1001;
        LCDMEM[12]=0b10000000;
    }
    else if(batt==3){
        LCDMEM[13]=0b1001;
        LCDMEM[12]=0b11000000;
    }
    else if(batt==4){
        LCDMEM[13]=0b1101;
        LCDMEM[12]=0b11000000;
    }
    else if(batt==5){
        LCDMEM[13]=0b1101;
        LCDMEM[12]=0b11100000;
    }
    else if(batt>=6){
        LCDMEM[13]=0b1111;
        LCDMEM[12]=0b11100000;
    }
    else{
        LCDMEM[13]=0b1;
        LCDMEM[12]=0b0;
        
    }
    
}

