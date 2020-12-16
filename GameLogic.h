/*
 * GameLogic.h
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_


typedef enum  {
    GAMESTATE_INIT,
    GAMESTATE_MENUMODE,
    GAMESTATE_GAMEINIT,
    GAMESTATE_PLAYMODE,
    GAMESTATE_GAMEOVER,
    GAMESTATE_RESETHIGHSCORES
} GameState;


extern GameState gameState;
extern unsigned int currentScore;
extern unsigned int currentLevel;


void initGameLogic( void );

void pushDiamondsAndBricks(void );


#endif /* _GAMELOGIC_H_ */
