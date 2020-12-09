/*
 * HighScore.c
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#include "HighScore.h"
#include "hal_LCD.h"
#include "stdio.h"
#include "GameLogic.h"          //wegen Definitionen von Positionen auf LCD
#include "HardwareManager.h"    //für die ButtonSignal

#define NUMBEROFHIGHSCORES 4
const int maxNumHighScores = NUMBEROFHIGHSCORES;
HighScore highScore[NUMBEROFHIGHSCORES];

/*
HighScore highScore[NUMBEROFHIGHSCORES] = {
                                   DUMMY NUMBERS!
                                  { 1, "ABC" , 0},
                                  { 1, "CDE" , 0},
                                  { 1, "FGH" , 0},
                                  { 1, "IJK" , 0} };
*/

int currentHighScoreRank = 0;

HighScore findHighScoreRankInArray( int selectedRank ){
    int i = 0;
    for(i = 0; i < NUMBEROFHIGHSCORES; i++)
    {
        if( highScore[i].rank == selectedRank ){
            break;
        }
    }
    return highScore[i];
}

void displayHighScoreRank( int selectedRank )
{
    readCurrentHighscore();
    char buffer[30];
    HighScore highScoreFound = highScore[selectedRank-1];
    sprintf(buffer, "%d %s %d", highScoreFound.rank, highScoreFound.name, highScoreFound.score);
    displayScrollText(buffer);
    return;
}

void highscoreCheck( unsigned int currentScore){
    
    readCurrentHighscore();
    if (currentScore>highScore[NUMBEROFHIGHSCORES-1].score){
        int i =0;
        HighScore temp;
        HighScore buffer = {99,"AAA",000};
        char *pLeter = 0;
        readCurrentHighscore();
        
        temp.score = currentScore;  //gets Score from game
        pLeter = pickLeter();       // chooses name for new score
        for(i =0; i<3 ; i++){       //writes name in to new score
            temp.name[i] = *pLeter;
            pLeter++;
        }
        
        
        for(i = 0 ; i<NUMBEROFHIGHSCORES ; i++){    //sorts the highscores new
            
            if (temp.score > highScore[i].score){   //searches for next position of temp.
                
                buffer = highScore[i];
                highScore[i]=temp;
                highScore[i].rank = i+1;
                temp = buffer;
                
                
            }else if(temp.score == highScore[i].score){//handling for even scores
                int n =0;
                for(n=0; (i+n)<NUMBEROFHIGHSCORES ; n++){//looks for more even scores
                    
                   if(temp.score == highScore[i+n].score){//changes rank of next even score
                        buffer = highScore[i+n];
                        highScore[i+n]=temp;
                        highScore[i+n].rank = i+1;
                    }else if(temp.score > highScore[i+n].score){//detects end of ven scores and adds new score in the end
                        buffer = highScore[i+n];
                        highScore[i+n]=temp;
                        highScore[i+n].rank = i+1;
                        temp = buffer;
                        i = i+n;                                // sets i to current position
                        break;
                    }
                }
            }
        }
        
        writeCurrentHighscore();
        
        return;
    }else{
        return;
    }
    
}




char* pickLeter (void){                 //lets player choose new Name
    char leter = 'A';
    char name[3] = {'A','A','A'};
    char* pName = NULL;
    int counter =0;
    
    while(counter<3){
        showChar(leter, pos6);
        showChar(name[0], pos1);
        showChar(name[1], pos2);
        showChar(name[2], pos3);
        
        if(S1ButtonSignal == 1){
            S1ButtonSignal = 0;
            if(leter<='Z'){
                leter++;
            }else{
                leter ='A';
            }
            
        }else if(S2ButtonSignal == 1){
            S2ButtonSignal = 0;
            name[counter]= leter;
            counter++;
            leter ='A';
        }
       
    }
    pName=&name[0];
    return pName;
}

void readCurrentHighscore (void){
    int i = 0;
    HighScore* pBootHighScore = (HighScore*)0x1800;
    for(i=0 ; i<NUMBEROFHIGHSCORES;i++){
        highScore[i].rank = pBootHighScore->rank;
        highScore[i].name[0] = pBootHighScore->name[0];
        highScore[i].name[1] = pBootHighScore->name[1];
        highScore[i].name[2] = pBootHighScore->name[2];
        highScore[i].score = pBootHighScore->score;
        pBootHighScore++;
    }
    return;
}

void writeCurrentHighscore (void){
    int i =0;
    HighScore* pBootHighScore = (HighScore*)0x1800;
    SYSCFG0 &= ~DFWP;
    for(i=0 ; i<NUMBEROFHIGHSCORES;i++) {
        pBootHighScore->rank = highScore[i].rank;
        pBootHighScore->name[0] = highScore[i].name[0];
        pBootHighScore->name[1] = highScore[i].name[1];
        pBootHighScore->name[2] = highScore[i].name[2];
        pBootHighScore->score = highScore[i].score;
        pBootHighScore++;
    }
    SYSCFG0 |= DFWP;
}

void resetHighscore(void){
    int i =0;
    for(i=0;i<NUMBEROFHIGHSCORES;i++){
        highScore[i].rank = 1;
        highScore[i].name[0] = 'A';
        highScore[i].name[1] = 'A';
        highScore[i].name[2] = 'A';
        highScore[i].score = 0;
    }
    writeCurrentHighscore();
    
    return;
}

 //  bootCounter = *pBootCounter;
 //  bootCounter++;
 // *pBootCounter = bootCounter;




