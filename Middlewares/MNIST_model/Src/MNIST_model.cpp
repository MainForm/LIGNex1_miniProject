#include "MNIST_model.hpp"
#include "cnn_mnist.h"

#include <cstring>

namespace AI_Model{

    /*
    activationAddress is need to be align by 4.
    */
    bool MNIST_model::initialize(ai_u8 * activationAddress){
        const ai_handle acts[] = { activationAddress};

        ai_error err = ai_cnn_mnist_create_and_init (&_mnist_model, acts, NULL);
        if (err.type != AI_ERROR_NONE) {
            return false;
        }

        _mnist_input = ai_cnn_mnist_inputs_get(_mnist_model, NULL);
        _mnist_output = ai_cnn_mnist_outputs_get(_mnist_model, NULL);

        if (!_mnist_input || !_mnist_output) {
            return false;
        }

        return true;
    }

    int32_t MNIST_model::run(const InputType& input,OutputType& output){
        constexpr uint32_t inputSize = AI_CNN_MNIST_IN_1_HEIGHT * AI_CNN_MNIST_IN_1_WIDTH;
        memcpy(_mnist_input->data,input.data()->data(),inputSize*sizeof(float));

        ai_i32 batches = ai_cnn_mnist_run(_mnist_model,_mnist_input,_mnist_output);

        if(batches < 0){
            return batches;
        }

        float* rawOutput = reinterpret_cast<float*>(_mnist_output->data);

        output = 0;
        float* maxOutputValue = &rawOutput[0];
        for(size_t idx = 1; idx < AI_CNN_MNIST_OUT_1_SIZE; idx++){
            if(*maxOutputValue < rawOutput[idx]){
                maxOutputValue = &rawOutput[idx];
                output = idx;
            }
        }
        
        return batches;
    }
}