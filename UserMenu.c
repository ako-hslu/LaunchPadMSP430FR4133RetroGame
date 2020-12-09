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

MenuState menuState = MENUSTATE_SHOWMENUOPERATION;

char scrollText[256];

void UpdateMenu()
{
    switch (menuState)
    {

    case MENUSTATE_SHOWMENUOPERATION:
        displayScrollText("S1 TO TOGGLE MENU S2 TO START GAME");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONHIGHSCORES;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_STARTGAME;
        }

        break;

    case MENUSTATE_OPTIONHIGHSCORES:
        displayScrollText("HIGHSCORES");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONCONTROLS;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            displayScrollText("S1 NEXT S2 EXIT");
            currentHighScoreRank = 1;
            menuState = MENUSTATE_SHOWHIGHSCORE;
        }
        break;

    case MENUSTATE_SHOWHIGHSCORE:
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
            menuState = MENUSTATE_OPTIONHIGHSCORES;
        }
        break;

    case MENUSTATE_OPTIONCONTROLS:
        displayScrollText("CONTROLS");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONDEMOMODE;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            displayScrollText("NO CONTROLS YET");
        }
        break;

    case MENUSTATE_OPTIONDEMOMODE:
        displayScrollText("DEMO MODE");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONSTARTGAME;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            displayScrollText("NO DEMO YET");
        }

        break;

    case MENUSTATE_OPTIONSTARTGAME:
        displayScrollText("S2 TO START GAME");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_OPTIONRESETSCORE;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_STARTGAME;
       }
        break;
        
    case MENUSTATE_OPTIONRESETSCORE:                    
        displayScrollText("S2 TO RESET HIGHSCORE");
        if(S1ButtonSignal == 1)
        {
            S1ButtonSignal = 0;
            menuState = MENUSTATE_SHOWMENUOPERATION;
        }
        else if (S2ButtonSignal == 1)
        {
            S2ButtonSignal = 0;
            menuState = MENUSTATE_RESETHIGHSCORE;
       }
        break;    

    default:
        menuState = MENUSTATE_SHOWMENUOPERATION;
        break;

    }
}

