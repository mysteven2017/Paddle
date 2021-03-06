/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "paddle/fluid/operators/fill_constant_batch_size_like_op.h"
#include "paddle/fluid/operators/batch_size_like.h"

namespace paddle {
namespace operators {

class FillConstantBatchSizeLikeOp : public BatchSizeLikeOp {
 protected:
  using BatchSizeLikeOp::BatchSizeLikeOp;
  framework::OpKernelType GetExpectedKernelType(
      const framework::ExecutionContext &ctx) const override {
    return framework::OpKernelType(
        static_cast<framework::proto::VarType::Type>(ctx.Attr<int>("dtype")),
        ctx.device_context());
  }
};

class FillConstantBatchSizeLikeOpMaker : public BatchSizeLikeOpMaker {
 public:
  FillConstantBatchSizeLikeOpMaker(OpProto *proto, OpAttrChecker *op_checker)
      : BatchSizeLikeOpMaker(proto, op_checker) {
    AddAttr<int>("dtype",
                 "(int, default 5 (FP32)) "
                 "Output data type")
        .SetDefault(framework::proto::VarType::FP32);
    AddAttr<float>("value", "(float, default 0) The value to be filled")
        .SetDefault(0.0f);
    AddComment(R"DOC(
FillConstantBatchSizeLike Operator.

Fill up a variable with specified constant value.

)DOC");
  }
};
}  // namespace operators
}  // namespace paddle

namespace ops = paddle::operators;
REGISTER_OPERATOR(fill_constant_batch_size_like,
                  ops::FillConstantBatchSizeLikeOp,
                  paddle::framework::EmptyGradOpMaker,
                  ops::FillConstantBatchSizeLikeOpMaker);
REGISTER_OP_CPU_KERNEL(
    fill_constant_batch_size_like,
    ops::FillConstantBatchSizeLikeOpKernel<paddle::platform::CPUDeviceContext,
                                           float>,
    ops::FillConstantBatchSizeLikeOpKernel<paddle::platform::CPUDeviceContext,
                                           double>,
    ops::FillConstantBatchSizeLikeOpKernel<paddle::platform::CPUDeviceContext,
                                           int>,
    ops::FillConstantBatchSizeLikeOpKernel<paddle::platform::CPUDeviceContext,
                                           int64_t>);
