/*
 * UserMenu.c
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#include "UserMenu.h"
#include "hal_LCD.h"
#include <stdio.h>
#include "HighScore.h"
#include "HardwareManager.h"

MenuState menuState = MENUSTATE_OPTIONSTARTGAME;

char scrollText[256];

void UpdateMenu()
{
    switch (menuState)
    {
    case MENUSTATE_OPTIONSTARTGAME:
        displayScrollText("1-START GAME");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_INSTRUCTION;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_STARTGAME;
        }
        break;

    case MENUSTATE_INSTRUCTION:
        displayScrollText("2-INSTRUCTIONS");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_HIGHSCORE;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_SHOWINSTRUCTIONS;
        }
        break;

    case MENUSTATE_HIGHSCORE:
        displayScrollText("3-HIGHSCORES");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONRESETHIGHSCORE;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            currentHighScoreRank = 1;
            menuState = MENUSTATE_SHOWHIGHSCORES;
        }
        break;

    case MENUSTATE_OPTIONRESETHIGHSCORE:
        displayScrollText("4-RESET HIGHSCORES");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONSTARTGAME;
        }
        else if( S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_RESETHIGHSCORE;
        }
        break;


    case MENUSTATE_SHOWINSTRUCTIONS:
        displayScrollText("COLLECT THE * AND AVOID THE + - DO THIS BY PRESSING S2");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_INSTRUCTION;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_INSTRUCTION;
        }
        break;

    case MENUSTATE_SHOWHIGHSCORES:
        displayHighScoreRank( currentHighScoreRank );
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            currentHighScoreRank++;
            if(currentHighScoreRank > maxNumHighScores)
            {
                currentHighScoreRank = 1;
            }
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            currentHighScoreRank = 1;
            menuState = MENUSTATE_HIGHSCORE;
        }
        break;



    default:
        menuState = MENUSTATE_STARTGAME;
        break;
    }
}

void showMenu(){
    char buffer[4] = "MENU";
    showChar(buffer[0], pos2);
    showChar(buffer[1], pos3);
    showChar(buffer[2], pos4);
    showChar(buffer[3], pos5);
    __delay_cycles(1000000);
}

