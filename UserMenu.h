/*
 * UserMenu.h
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#ifndef _USERMENU_H_
#define _USERMENU_H_


typedef enum {
    MENUSTATE_SHOWMENUOPERATION,
    MENUSTATE_OPTIONHIGHSCORES,
    MENUSTATE_SHOWHIGHSCORE,
    MENUSTATE_OPTIONCONTROLS,
    MENUSTATE_SHOWCONTROLS,
    MENUSTATE_OPTIONSTARTGAME,
    MENUSTATE_STARTGAME,
    MENUSTATE_OPTIONDEMOMODE,
    MENUSTATE_DEMOMODE
} MenuState;


extern MenuState menuState;

void UpdateMenu(void);


#endif /* _USERMENU_H_ */
