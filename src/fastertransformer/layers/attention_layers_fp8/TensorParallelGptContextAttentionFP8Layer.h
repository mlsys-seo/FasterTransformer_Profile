/*
 * Copyright (c) 2022-2023, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "src/fastertransformer/layers/attention_layers_fp8/GptContextAttentionFP8Layer.h"
#include "src/fastertransformer/utils/nccl_utils.h"

namespace fastertransformer {

template<typename T1, typename T2>
class TensorParallelGptContextAttentionFP8Layer: public GptContextAttentionFP8Layer<T1, T2> {
private:
    NcclParam tensor_para_;

public:
    TensorParallelGptContextAttentionFP8Layer(size_t           head_num,
                                              size_t           size_per_head,
                                              size_t           rotary_embedding_dim,
                                              NcclParam        tensor_para,
                                              cudaStream_t     stream,
                                              cublasMMWrapper* cublas_wrapper,
                                              IAllocator*      allocator,
                                              bool             is_free_buffer_after_forward,
                                              bool             is_qk_buf_float,
                                              bool             sparse = false);

    TensorParallelGptContextAttentionFP8Layer(TensorParallelGptContextAttentionFP8Layer<T1, T2> const& attention_layer);

    ~TensorParallelGptContextAttentionFP8Layer() = default;

    void
    forward(TensorMap* output_tensors, TensorMap* input_tensors, const AttentionWeight<T1>* attention_weights, const int max_seq_len=0) override;
};

}  // namespace fastertransformer
