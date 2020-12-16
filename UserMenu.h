/*
 * UserMenu.h
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#ifndef _USERMENU_H_
#define _USERMENU_H_


typedef enum {
    MENUSTATE_STARTGAME,
    MENUSTATE_OPTIONSTARTGAME,
    MENUSTATE_INSTRUCTION,
    MENUSTATE_SHOWINSTRUCTIONS,
    MENUSTATE_HIGHSCORE,
    MENUSTATE_SHOWHIGHSCORES,
    MENUSTATE_OPTIONRESETHIGHSCORE,
    MENUSTATE_RESETHIGHSCORE

} MenuState;


extern MenuState menuState;

void UpdateMenu(void);
void showMenu(void);


#endif /* _USERMENU_H_ */
