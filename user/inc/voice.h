#ifndef _VOICE_H
#define _VOICE_H

#include "stm32f10x.h"
#include "led.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"  
#include "rgb.h" 

void Voice_Init(u32 baud);
void Voice_Rec(void);


#endif
