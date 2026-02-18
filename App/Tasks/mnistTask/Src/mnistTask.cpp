#include "mnistTask.hpp"

#include "FreeRTOS_Handles.h"

#include "MNIST_model.hpp"
#include "MNIST_image.h"
#include "cnn_mnist_data.h"

#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"

#include <cstdio>
#include <cstring>

AI_Model::MNIST_model mnist;

AI_ALIGNED(4)
static ai_u8 mnist_activations[AI_CNN_MNIST_DATA_ACTIVATIONS_SIZE];

MNIST_image inputImg;

extern "C"
void mnistTaskHandler(void *argument){
    uint8_t mqPriority;
    uint8_t Message[32] = "";

    mnist.initialize(mnist_activations);

    for(;;){
        if(osMessageQueueGet(MNIST_QueueHandle,&inputImg,&mqPriority,osWaitForever) == osOK){
            AI_Model::MNIST_model::InputType input;
            AI_Model::MNIST_model::OutputType output;
            memcpy(input.data()->data(),inputImg.data,28*28*sizeof(float));

            if(mnist.run(input,output) > 0){
                sprintf((char*)Message,"Output : %ld\n",output);
                HAL_UART_Transmit(&huart1, Message, strlen((char*)Message), HAL_MAX_DELAY);
            }
        }
    }
}