#include "mainTask.hpp"

#include "cmsis_os2.h"

extern "C"
void mainTaskHandler(void *argument){

    for(;;){
        osDelay(1000);
    }
}