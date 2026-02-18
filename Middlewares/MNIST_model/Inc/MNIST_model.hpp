#ifndef __MW_MNIST_MODEL_H__
#define __MW_MNIST_MODEL_H__

#include "ai_platform.h"
#include "cnn_mnist.h"
#include <array>

namespace AI_Model{
    class MNIST_model{
    public:
        using InputType = std::array<std::array<float,AI_CNN_MNIST_IN_1_HEIGHT>,AI_CNN_MNIST_IN_1_WIDTH>;
        using OutputType = uint32_t;
    private:
        ai_handle _mnist_model = AI_HANDLE_NULL;

        ai_buffer* _mnist_input = nullptr;
        ai_buffer* _mnist_output = nullptr;
        
    public:
        bool initialize(ai_u8 * activationAddress);
        int32_t run(const InputType& input,OutputType& output);
    };
}

#endif // __MW_MNIST_MODEL_H__