/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserve.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

// #include "ConvOp.h"

namespace paddle {

/* The storage format of the coldata in the Im2ColFunctor and Col2ImFunctor. */
enum ColFormat { kCFO = 0, kOCF = 1 };

/*
 * \brief Converts the image data of four dimensions(NCHW) into a colData.
 *        Then you can reshape colData to a convolution matrix for
 *        convolution calculation based on matrix multiplication.
 *
 * \param imData  Image data of NCHW format.
 *                The format of imData is:
 *                [input_channels, input_height, input_width].
 * \param colData colData data.
 *                If the template argument Format is kCFO,
 *                the format of colData is:
 *                [input_channels,
 *                 filter_height,
 *                 filter_width,
 *                 output_height,
 *                 output_width]
 *                If the template argument Format is kOCF,
 *                the format of colData is:
 *                [output_height,
 *                 output_width,
 *                 input_channels,
 *                 filter_height,
 *                 filter_width]
 * TODO(hedaoyuan): Refactor the arguments of the interface with TensorShape.
 */
template <ColFormat Format, DeviceType Device, class T>
class Im2ColFunctor {
public:
  void operator()(const T* imData,
                  int inputChannels,
                  int inputHeight,
                  int inputWidth,
                  int filterHeight,
                  int filterWidth,
                  int strideHeight,
                  int strideWidth,
                  int paddingHeight,
                  int paddingWidth,
                  int outputHeight,
                  int outputWidth,
                  T* colData);
};

template <ColFormat Format, DeviceType Device, class T>
class Col2ImFunctor {
public:
  void operator()(const T* colData,
                  int inputChannels,
                  int inputHeight,
                  int inputWidth,
                  int filterHeight,
                  int filterWidth,
                  int strideHeight,
                  int strideWidth,
                  int paddingHeight,
                  int paddingWidth,
                  int outputHeight,
                  int outputWidth,
                  T* imData);
};

}  // namespace paddle
