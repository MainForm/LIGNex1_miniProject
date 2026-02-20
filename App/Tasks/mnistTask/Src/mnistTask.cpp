#include "mnistTask.hpp"

#include "FreeRTOS_Handles.h"
#include "MutexGuard.hpp"

#include "MNIST_model.hpp"
#include "MNIST_image.h"
#include "cnn_mnist_data.h"

#include "usart.h"
#include "i2c.h"

#include "CharacterLCD.hpp"

#include <cstdio>
#include <cstring>

AI_Model::MNIST_model mnist;

// AI_ALIGNED(4)
// static ai_u8 mnist_activations[AI_CNN_MNIST_DATA_ACTIVATIONS_SIZE];

ai_u8* mnist_activations = reinterpret_cast<ai_u8*>(0xD0050000);

MNIST_image inputImg;


CharacterLCD::LCD_I2C clcd(&hi2c3);

extern "C"
void mnistTaskHandler(void *argument){
    uint8_t mqPriority;
    uint8_t Message[32] = "";

    mnist.initialize(mnist_activations);

    {
        AppCommon::MutexGuard mutexLock(I2C3_mutexHandle);

        clcd.initialize();

        clcd.setCursor(0, 0);
        clcd.print("MNIST test");
    }

    for(;;){
        if(osMessageQueueGet(MNIST_QueueHandle,&inputImg,&mqPriority,osWaitForever) == osOK){
            AI_Model::MNIST_model::InputType input;
            AI_Model::MNIST_model::OutputType output;
            memcpy(input.data()->data(),inputImg.data,28*28*sizeof(float));

            if(mnist.run(input,output) > 0){
                sprintf((char*)Message,"result : %ld",output);
                HAL_UART_Transmit(&huart1, Message, strlen((char*)Message), HAL_MAX_DELAY);
                HAL_UART_Transmit(&huart1, (uint8_t*)'\n', 1, HAL_MAX_DELAY);
                {
                    AppCommon::MutexGuard mutexLock(I2C3_mutexHandle);

                    clcd.clearDisplay();
                    clcd.setCursor(0, 0);
                    clcd.print("MNIST test");
                    clcd.setCursor(0, 1);
                    clcd.print((char*)Message);
                }
            }
        }
    }
}