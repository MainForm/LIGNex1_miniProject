/**
  ******************************************************************************
  * @file    cnn_mnist.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-02-18T02:49:59+0900
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "cnn_mnist.h"
#include "cnn_mnist_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_cnn_mnist
 
#undef AI_CNN_MNIST_MODEL_SIGNATURE
#define AI_CNN_MNIST_MODEL_SIGNATURE     "0x054cb875ef15604850834cf7957e4097"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2026-02-18T02:49:59+0900"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_CNN_MNIST_N_BATCHES
#define AI_CNN_MNIST_N_BATCHES         (1)

static ai_ptr g_cnn_mnist_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_cnn_mnist_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _conv1_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6272, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _relu_LeakyRelu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6272, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _conv2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 784, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 784, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _conv3_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 49, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 49, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _flatten_Flatten_output_0_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 49, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  _fc1_Gemm_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _relu_3_LeakyRelu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _fc2_Gemm_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _relu_4_LeakyRelu_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  output_softmax_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  output_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _conv1_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 72, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _conv1_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _conv2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _conv2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _conv3_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _conv3_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  _fc1_Gemm_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 784, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  _fc1_Gemm_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  _fc2_Gemm_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 160, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  _fc2_Gemm_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  _conv1_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  _conv2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 72, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  _conv2_Conv_output_0_scratch1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 224, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  _conv3_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  _conv3_Conv_output_0_scratch1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 28, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_bias, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_bn1d_2_BatchNormalization_output_0_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_bn1d_2_BatchNormalization_output_0_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_scale, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_bn1d_2_BatchNormalization_output_0_scale_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_bias, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_bn2d_1_BatchNormalization_output_0_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 14, 14), AI_STRIDE_INIT(4, 4, 4, 16, 224),
  1, &_bn2d_1_BatchNormalization_output_0_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_scale, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_bn2d_1_BatchNormalization_output_0_scale_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_bn2d_2_BatchNormalization_output_0_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 7, 7), AI_STRIDE_INIT(4, 4, 4, 4, 28),
  1, &_bn2d_2_BatchNormalization_output_0_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_scale, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_bn2d_2_BatchNormalization_output_0_scale_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _conv1_Conv_output_0_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_conv1_Conv_output_0_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _conv1_Conv_output_0_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 28, 28), AI_STRIDE_INIT(4, 4, 4, 32, 896),
  1, &_conv1_Conv_output_0_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _conv1_Conv_output_0_scratch0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 3, 3), AI_STRIDE_INIT(4, 4, 4, 4, 12),
  1, &_conv1_Conv_output_0_scratch0_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _conv1_Conv_output_0_weights, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 8), AI_STRIDE_INIT(4, 4, 4, 32, 96),
  1, &_conv1_Conv_output_0_weights_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  _conv2_Conv_output_0_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_conv2_Conv_output_0_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _conv2_Conv_output_0_output, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 14, 14), AI_STRIDE_INIT(4, 4, 4, 16, 224),
  1, &_conv2_Conv_output_0_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _conv2_Conv_output_0_scratch0, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 3, 3), AI_STRIDE_INIT(4, 4, 4, 32, 96),
  1, &_conv2_Conv_output_0_scratch0_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _conv2_Conv_output_0_scratch1, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 28, 2), AI_STRIDE_INIT(4, 4, 4, 16, 448),
  1, &_conv2_Conv_output_0_scratch1_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _conv2_Conv_output_0_weights, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 8, 3, 3, 4), AI_STRIDE_INIT(4, 4, 32, 128, 384),
  1, &_conv2_Conv_output_0_weights_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _conv3_Conv_output_0_bias, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_conv3_Conv_output_0_bias_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  _conv3_Conv_output_0_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 7, 7), AI_STRIDE_INIT(4, 4, 4, 4, 28),
  1, &_conv3_Conv_output_0_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  _conv3_Conv_output_0_scratch0, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 3, 3), AI_STRIDE_INIT(4, 4, 4, 16, 48),
  1, &_conv3_Conv_output_0_scratch0_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  _conv3_Conv_output_0_scratch1, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 14, 2), AI_STRIDE_INIT(4, 4, 4, 4, 56),
  1, &_conv3_Conv_output_0_scratch1_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  _conv3_Conv_output_0_weights, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 4, 3, 3, 1), AI_STRIDE_INIT(4, 4, 16, 16, 48),
  1, &_conv3_Conv_output_0_weights_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  _fc1_Gemm_output_0_bias, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_fc1_Gemm_output_0_bias_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  _fc1_Gemm_output_0_output, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_fc1_Gemm_output_0_output_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  _fc1_Gemm_output_0_weights, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 49, 16, 1, 1), AI_STRIDE_INIT(4, 4, 196, 3136, 3136),
  1, &_fc1_Gemm_output_0_weights_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  _fc2_Gemm_output_0_bias, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_fc2_Gemm_output_0_bias_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  _fc2_Gemm_output_0_output, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_fc2_Gemm_output_0_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  _fc2_Gemm_output_0_weights, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 16, 10, 1, 1), AI_STRIDE_INIT(4, 4, 64, 640, 640),
  1, &_fc2_Gemm_output_0_weights_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  _flatten_Flatten_output_0_to_chlast_output, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 7, 1), AI_STRIDE_INIT(4, 4, 4, 28, 196),
  1, &_flatten_Flatten_output_0_to_chlast_output_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  _flatten_Flatten_output_0_to_chlast_output0, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 49, 1, 1), AI_STRIDE_INIT(4, 4, 4, 196, 196),
  1, &_flatten_Flatten_output_0_to_chlast_output_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  _relu_3_LeakyRelu_output_0_output, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_relu_3_LeakyRelu_output_0_output_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  _relu_4_LeakyRelu_output_0_output, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &_relu_4_LeakyRelu_output_0_output_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  _relu_LeakyRelu_output_0_output, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 28, 28), AI_STRIDE_INIT(4, 4, 4, 32, 896),
  1, &_relu_LeakyRelu_output_0_output_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 28, 28), AI_STRIDE_INIT(4, 4, 4, 4, 112),
  1, &input_output_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  output_output, AI_STATIC,
  35, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &output_output_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  output_softmax_output, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &output_softmax_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_softmax_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_layer, 19,
  NL_TYPE, 0x0, NULL,
  nl, forward_log,
  &output_chain,
  NULL, &output_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_softmax_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_bn1d_2_BatchNormalization_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_softmax_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_softmax_layer, 18,
  SM_TYPE, 0x0, NULL,
  sm, forward_sm,
  &output_softmax_chain,
  NULL, &output_layer, AI_STATIC, 
  .nl_params = NULL, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_relu_4_LeakyRelu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_bn1d_2_BatchNormalization_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_bn1d_2_BatchNormalization_output_0_scale, &_bn1d_2_BatchNormalization_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _bn1d_2_BatchNormalization_output_0_layer, 17,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_bn1d_2_BatchNormalization_output_0_chain,
  NULL, &output_softmax_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _relu_4_LeakyRelu_output_0_nl_params_data[] = { 0.0, 0.009999999776482582, -1 };
AI_ARRAY_OBJ_DECLARE(
    _relu_4_LeakyRelu_output_0_nl_params, AI_ARRAY_FORMAT_FLOAT,
    _relu_4_LeakyRelu_output_0_nl_params_data, _relu_4_LeakyRelu_output_0_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _relu_4_LeakyRelu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_fc2_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_relu_4_LeakyRelu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _relu_4_LeakyRelu_output_0_layer, 16,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_relu_4_LeakyRelu_output_0_chain,
  NULL, &_bn1d_2_BatchNormalization_output_0_layer, AI_STATIC, 
  .nl_params = &_relu_4_LeakyRelu_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _fc2_Gemm_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_relu_3_LeakyRelu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_fc2_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_fc2_Gemm_output_0_weights, &_fc2_Gemm_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _fc2_Gemm_output_0_layer, 15,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &_fc2_Gemm_output_0_chain,
  NULL, &_relu_4_LeakyRelu_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _relu_3_LeakyRelu_output_0_nl_params_data[] = { 0.0, 0.009999999776482582, -1 };
AI_ARRAY_OBJ_DECLARE(
    _relu_3_LeakyRelu_output_0_nl_params, AI_ARRAY_FORMAT_FLOAT,
    _relu_3_LeakyRelu_output_0_nl_params_data, _relu_3_LeakyRelu_output_0_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _relu_3_LeakyRelu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_fc1_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_relu_3_LeakyRelu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _relu_3_LeakyRelu_output_0_layer, 13,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_relu_3_LeakyRelu_output_0_chain,
  NULL, &_fc2_Gemm_output_0_layer, AI_STATIC, 
  .nl_params = &_relu_3_LeakyRelu_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _fc1_Gemm_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_flatten_Flatten_output_0_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_fc1_Gemm_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_fc1_Gemm_output_0_weights, &_fc1_Gemm_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _fc1_Gemm_output_0_layer, 12,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &_fc1_Gemm_output_0_chain,
  NULL, &_relu_3_LeakyRelu_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _flatten_Flatten_output_0_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_bn2d_2_BatchNormalization_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_flatten_Flatten_output_0_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _flatten_Flatten_output_0_to_chlast_layer, 11,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_flatten_Flatten_output_0_to_chlast_chain,
  NULL, &_fc1_Gemm_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_conv3_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_bn2d_2_BatchNormalization_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_bn2d_2_BatchNormalization_output_0_scale, &_bn2d_2_BatchNormalization_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _bn2d_2_BatchNormalization_output_0_layer, 10,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_bn2d_2_BatchNormalization_output_0_chain,
  NULL, &_flatten_Flatten_output_0_to_chlast_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _conv3_Conv_output_0_nl_params_data[] = { 0.0, 0.009999999776482582, -1 };
AI_ARRAY_OBJ_DECLARE(
    _conv3_Conv_output_0_nl_params, AI_ARRAY_FORMAT_FLOAT,
    _conv3_Conv_output_0_nl_params_data, _conv3_Conv_output_0_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _conv3_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_bn2d_1_BatchNormalization_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_conv3_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_conv3_Conv_output_0_weights, &_conv3_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_conv3_Conv_output_0_scratch0, &_conv3_Conv_output_0_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  _conv3_Conv_output_0_layer, 9,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_if32of32wf32_nl_pool,
  &_conv3_Conv_output_0_chain,
  NULL, &_bn2d_2_BatchNormalization_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = &_conv3_Conv_output_0_nl_params, 
  .nl_func = AI_HANDLE_PTR(forward_lite_nl_relu_generic_if32of32), 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_ap_array_f32), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_conv2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_bn2d_1_BatchNormalization_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_bn2d_1_BatchNormalization_output_0_scale, &_bn2d_1_BatchNormalization_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _bn2d_1_BatchNormalization_output_0_layer, 6,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_bn2d_1_BatchNormalization_output_0_chain,
  NULL, &_conv3_Conv_output_0_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float _conv2_Conv_output_0_nl_params_data[] = { 0.0, 0.009999999776482582, -1 };
AI_ARRAY_OBJ_DECLARE(
    _conv2_Conv_output_0_nl_params, AI_ARRAY_FORMAT_FLOAT,
    _conv2_Conv_output_0_nl_params_data, _conv2_Conv_output_0_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _conv2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_relu_LeakyRelu_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_conv2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_conv2_Conv_output_0_weights, &_conv2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_conv2_Conv_output_0_scratch0, &_conv2_Conv_output_0_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  _conv2_Conv_output_0_layer, 5,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_if32of32wf32_nl_pool,
  &_conv2_Conv_output_0_chain,
  NULL, &_bn2d_1_BatchNormalization_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .nl_params = &_conv2_Conv_output_0_nl_params, 
  .nl_func = AI_HANDLE_PTR(forward_lite_nl_relu_generic_if32of32), 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_ap_array_f32), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


AI_STATIC_CONST ai_float _relu_LeakyRelu_output_0_nl_params_data[] = { 0.0, 0.009999999776482582, -1 };
AI_ARRAY_OBJ_DECLARE(
    _relu_LeakyRelu_output_0_nl_params, AI_ARRAY_FORMAT_FLOAT,
    _relu_LeakyRelu_output_0_nl_params_data, _relu_LeakyRelu_output_0_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _relu_LeakyRelu_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_conv1_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_relu_LeakyRelu_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _relu_LeakyRelu_output_0_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &_relu_LeakyRelu_output_0_chain,
  NULL, &_conv2_Conv_output_0_layer, AI_STATIC, 
  .nl_params = &_relu_LeakyRelu_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _conv1_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_conv1_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_conv1_Conv_output_0_weights, &_conv1_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_conv1_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _conv1_Conv_output_0_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_conv1_Conv_output_0_chain,
  NULL, &_relu_LeakyRelu_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 5636, 1, 1),
    5636, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 28260, 1, 1),
    28260, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNN_MNIST_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNN_MNIST_OUT_NUM, &output_output),
  &_conv1_Conv_output_0_layer, 0x156bbd97, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 5636, 1, 1),
      5636, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 28260, 1, 1),
      28260, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNN_MNIST_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNN_MNIST_OUT_NUM, &output_output),
  &_conv1_Conv_output_0_layer, 0x156bbd97, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool cnn_mnist_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_cnn_mnist_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 36);
    input_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 36);
    _conv1_Conv_output_0_scratch0_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _conv1_Conv_output_0_scratch0_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _conv1_Conv_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 3172);
    _conv1_Conv_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 3172);
    _relu_LeakyRelu_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 3172);
    _relu_LeakyRelu_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 3172);
    _conv2_Conv_output_0_scratch0_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _conv2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _conv2_Conv_output_0_scratch1_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 288);
    _conv2_Conv_output_0_scratch1_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 288);
    _conv2_Conv_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 2692);
    _conv2_Conv_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 2692);
    _bn2d_1_BatchNormalization_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 5828);
    _bn2d_1_BatchNormalization_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 5828);
    _conv3_Conv_output_0_scratch0_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _conv3_Conv_output_0_scratch0_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _conv3_Conv_output_0_scratch1_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 144);
    _conv3_Conv_output_0_scratch1_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 144);
    _conv3_Conv_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 256);
    _conv3_Conv_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 256);
    _bn2d_2_BatchNormalization_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _bn2d_2_BatchNormalization_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _flatten_Flatten_output_0_to_chlast_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 196);
    _flatten_Flatten_output_0_to_chlast_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 196);
    _fc1_Gemm_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _fc1_Gemm_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _relu_3_LeakyRelu_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 64);
    _relu_3_LeakyRelu_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 64);
    _fc2_Gemm_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _fc2_Gemm_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _relu_4_LeakyRelu_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 40);
    _relu_4_LeakyRelu_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 40);
    _bn1d_2_BatchNormalization_output_0_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    _bn1d_2_BatchNormalization_output_0_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    output_softmax_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 40);
    output_softmax_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 40);
    output_output_array.data = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    output_output_array.data_start = AI_PTR(g_cnn_mnist_activations_map[0] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool cnn_mnist_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_cnn_mnist_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    _conv1_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _conv1_Conv_output_0_weights_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 0);
    _conv1_Conv_output_0_weights_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 0);
    _conv1_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _conv1_Conv_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 288);
    _conv1_Conv_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 288);
    _conv2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _conv2_Conv_output_0_weights_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 320);
    _conv2_Conv_output_0_weights_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 320);
    _conv2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _conv2_Conv_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1472);
    _conv2_Conv_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1472);
    _bn2d_1_BatchNormalization_output_0_scale_array.format |= AI_FMT_FLAG_CONST;
    _bn2d_1_BatchNormalization_output_0_scale_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1488);
    _bn2d_1_BatchNormalization_output_0_scale_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1488);
    _bn2d_1_BatchNormalization_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _bn2d_1_BatchNormalization_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1504);
    _bn2d_1_BatchNormalization_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1504);
    _conv3_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _conv3_Conv_output_0_weights_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1520);
    _conv3_Conv_output_0_weights_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1520);
    _conv3_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _conv3_Conv_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1664);
    _conv3_Conv_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1664);
    _bn2d_2_BatchNormalization_output_0_scale_array.format |= AI_FMT_FLAG_CONST;
    _bn2d_2_BatchNormalization_output_0_scale_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1668);
    _bn2d_2_BatchNormalization_output_0_scale_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1668);
    _bn2d_2_BatchNormalization_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _bn2d_2_BatchNormalization_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1672);
    _bn2d_2_BatchNormalization_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1672);
    _fc1_Gemm_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _fc1_Gemm_output_0_weights_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 1676);
    _fc1_Gemm_output_0_weights_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 1676);
    _fc1_Gemm_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _fc1_Gemm_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 4812);
    _fc1_Gemm_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 4812);
    _fc2_Gemm_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _fc2_Gemm_output_0_weights_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 4876);
    _fc2_Gemm_output_0_weights_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 4876);
    _fc2_Gemm_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _fc2_Gemm_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 5516);
    _fc2_Gemm_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 5516);
    _bn1d_2_BatchNormalization_output_0_scale_array.format |= AI_FMT_FLAG_CONST;
    _bn1d_2_BatchNormalization_output_0_scale_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 5556);
    _bn1d_2_BatchNormalization_output_0_scale_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 5556);
    _bn1d_2_BatchNormalization_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _bn1d_2_BatchNormalization_output_0_bias_array.data = AI_PTR(g_cnn_mnist_weights_map[0] + 5596);
    _bn1d_2_BatchNormalization_output_0_bias_array.data_start = AI_PTR(g_cnn_mnist_weights_map[0] + 5596);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_cnn_mnist_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_CNN_MNIST_MODEL_NAME,
      .model_signature   = AI_CNN_MNIST_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 324461,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x156bbd97,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_cnn_mnist_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_CNN_MNIST_MODEL_NAME,
      .model_signature   = AI_CNN_MNIST_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 324461,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x156bbd97,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_cnn_mnist_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_cnn_mnist_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_cnn_mnist_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_cnn_mnist_create(network, AI_CNN_MNIST_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_cnn_mnist_data_params_get(&params) != true) {
    err = ai_cnn_mnist_get_error(*network);
    return err;
  }
#if defined(AI_CNN_MNIST_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_CNN_MNIST_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_cnn_mnist_init(*network, &params) != true) {
    err = ai_cnn_mnist_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_cnn_mnist_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_cnn_mnist_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_cnn_mnist_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_cnn_mnist_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= cnn_mnist_configure_weights(net_ctx, params);
  ok &= cnn_mnist_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_cnn_mnist_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_cnn_mnist_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_CNN_MNIST_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

