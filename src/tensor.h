#ifndef LIBTORCHJS_TENSOR_H
#define LIBTORCHJS_TENSOR_H

#include <napi.h>
#include <torch/torch.h>

namespace libtorchjs {

    class Tensor : public Napi::ObjectWrap<Tensor> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        explicit Tensor(const Napi::CallbackInfo &info);

        void setTensor(at::Tensor tensor);

        Napi::Value toString(const Napi::CallbackInfo &info);

        Napi::Value toUint8Array(const Napi::CallbackInfo &info);

        Napi::Value view(const Napi::CallbackInfo &info);

        torch::Tensor getTensor();

        static Napi::Object NewInstance();

    private:
        static Napi::FunctionReference constructor;

        torch::Tensor tensor;
    };

}

#endif //LIBTORCHJS_TENSOR_H
