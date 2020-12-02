/*
 * HardwareManager.h
 *
 *  Created on: May 27, 2020
 *      Author: PRG_C FS20
 */

#ifndef _HARDWAREMANAGER_H_
#define _HARDWAREMANAGER_H_

typedef volatile unsigned char ButtonSignal;

extern ButtonSignal S1ButtonSignal;
extern ButtonSignal S2ButtonSignal;

void Init_GPIO();
void Init_Clock();
void Init_RTC();
void Init_LCD();


#endif /* _HARDWAREMANAGER_H_ */
