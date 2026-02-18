#include "Interrupts.hpp"

InterruptCallback GPIO_PortA0_Callback = nullptr;

extern "C"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_0){
        if(GPIO_PortA0_Callback != nullptr){
            GPIO_PortA0_Callback();
        }
    }
}