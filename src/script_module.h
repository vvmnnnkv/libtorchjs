#ifndef LIBTORCHJS_JIT_SCRIPT_MODULE_H
#define LIBTORCHJS_JIT_SCRIPT_MODULE_H

#include <napi.h>
#include <torch/script.h>

namespace libtorchjs {

    class ScriptModule : public Napi::ObjectWrap<ScriptModule> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        explicit ScriptModule(const Napi::CallbackInfo &info);

        void setModule(std::shared_ptr<torch::jit::script::Module> module);

        static Napi::Object NewInstance();

    private:
        static Napi::FunctionReference constructor;

        void forward(const Napi::CallbackInfo &info);

        std::shared_ptr<torch::jit::script::Module> module;
    };

}

#endif