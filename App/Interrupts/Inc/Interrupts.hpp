#ifndef __APP_ISR_H__
#define __APP_ISR_H__

#include "main.h"

typedef void (*InterruptCallback)(void);

extern InterruptCallback GPIO_PortA0_Callback;

#endif // __APP_ISR_H__