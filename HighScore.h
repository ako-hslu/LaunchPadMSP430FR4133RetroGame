/*
 * HighScore.h
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

struct HighScore {
    int rank;
    char name[3];
    int score;
};

void displayHighScoreRank( int selectedRank );

extern const int maxNumHighScores;
extern int currentHighScoreRank;

#endif /* HIGHSCORE_H_ */
