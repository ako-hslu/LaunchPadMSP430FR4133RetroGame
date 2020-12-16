/*
 * HighScore.h
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

typedef struct{ //typdef, damit man variablen als Highscoretype benutzen kann
    int rank;
    char name[3];
    unsigned int score; //da current score auch unsigned int ist
} HighScore ;

void displayHighScoreRank( int selectedRank );

void highscoreCheck( unsigned int currentScore); //neue Funktion, um Highscore zu schreiben
char* pickLetter(void);                          // neue Funktion, um Namen zu wählen
void resetHighscore(void);                      //neue Funktion, um Highscore zu reseten
void readCurrentHighscore (void);              //neue Funktion, um Highscoreliste aus Fram zu lesen
void writeCurrentHighscore (void);

extern const int maxNumHighScores;
extern int currentHighScoreRank;

#endif /* HIGHSCORE_H_ */
