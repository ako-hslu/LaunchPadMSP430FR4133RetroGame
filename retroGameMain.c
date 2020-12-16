/*
 * retroGameMain.c
 *
 *  Created on: May 26, 2020
 *      Author: PRG_C FS20
 */



#include <msp430.h>
#include <stdio.h>
#include "driverlib.h"


#include "HardwareManager.h"
#include "UserMenu.h"
#include "GameLogic.h"
#include "hal_LCD.h"
#include "HighScore.h"




// function prototypes
void initHardware(void)
{
    Init_GPIO();
    Init_LCD();

    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN2);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN6);
    //*S1buttonDebounce = *S2buttonDebounce = 0;
    __enable_interrupt();
}



void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    char buf[20];

    initHardware();


    while(1)
    {
        switch(gameState)
        {
        case GAMESTATE_INIT:
          displayScrollText("HELLO PRESS S1 TO TOGGLE AND S2 TO SELECT");
          S1ButtonSignal = 0;
          S2ButtonSignal = 0;
          showMenu();
          gameState = GAMESTATE_MENUMODE;
          break;

        case GAMESTATE_MENUMODE:
            UpdateMenu();
            if(menuState == MENUSTATE_STARTGAME)
            {
                // reset the menuState
                menuState = MENUSTATE_OPTIONSTARTGAME;
                // switch the main state machine to Play Mode
                gameState = GAMESTATE_GAMEINIT;
            }
            if(menuState == MENUSTATE_RESETHIGHSCORE)
            {
                // reset the menuState
                menuState = MENUSTATE_OPTIONSTARTGAME;
                // switch the main state machine to Play Mode
                gameState = GAMESTATE_RESETHIGHSCORES;
            }
            break;
        case GAMESTATE_GAMEINIT:
            initGameLogic();
            gameState = GAMESTATE_PLAYMODE;
            break;

        case GAMESTATE_PLAYMODE:
            pushDiamondsAndBricks();
            break;

        case GAMESTATE_GAMEOVER:
            clearLCD();
            sprintf(buf, "SCORE %d LEVEL %d", currentScore, currentLevel); // MOD
            displayScrollText(buf);
            highscoreCheck(currentScore);
            gameState = GAMESTATE_MENUMODE;
            break;

        case GAMESTATE_RESETHIGHSCORES:
            resetHighscore();
            gameState = GAMESTATE_INIT;
            break;

        default:
            gameState = GAMESTATE_INIT;
            break;
        }

    }

}
