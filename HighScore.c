/*
 * HighScore.c
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#include "HighScore.h"
#include "hal_LCD.h"
#include "stdio.h"

#define NUMBEROFHIGHSCORES 4
const int maxNumHighScores = NUMBEROFHIGHSCORES;
struct HighScore highScore[NUMBEROFHIGHSCORES] = {
                                  /* DUMMY NUMBERS! */
                                  { 3, "ABC" , 223},
                                  { 1, "CDE" , 523},
                                  { 4, "FGH" , 123},
                                  { 2, "IJK" , 423} };


int currentHighScoreRank = 0;

struct HighScore *findHighScoreRankInArray( int selectedRank ){
    int i = 0;
    for(i = 0; i < NUMBEROFHIGHSCORES; i++)
    {
        if( highScore[i].rank == selectedRank ){
            break;
        }
    }
    return &highScore[i];
}

void displayHighScoreRank( int selectedRank )
{
    char buffer[20];
    struct HighScore *pHighScoreFound = findHighScoreRankInArray(selectedRank);

    if(pHighScoreFound != 0 )
    {
        /* pHighScoreFound->rank gleich (*pHighScoreFound).rank */
        sprintf(buffer, "%d %s %d", pHighScoreFound->rank, pHighScoreFound->name, pHighScoreFound->score);
        displayScrollText(buffer);
    } else {
        displayScrollText("ERROR NO HIGHSCORE FOUND");
    }
}




