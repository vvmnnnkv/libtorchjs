#include <napi.h>
#include <torch/script.h>
#include "script_module.h"
#include "tensor.h"
#include <stdlib.h>
#include <stdio.h>

namespace libtorchjs {

    class ScriptModuleForwardAsyncWorker : public Napi::AsyncWorker {
    public:
        static void forward(torch::jit::script::Module module,
                torch::Tensor tensor, Napi::Function cb) {
            auto *worker = new ScriptModuleForwardAsyncWorker(module, tensor, cb);
            worker->Queue();
        }

    protected:
        void Execute() override {
            // torch.forward
            outTensor = module.forward({inTensor}).toTensor();
        }

        void OnOK() override {
            Napi::HandleScope scope(Env());
            // create napi tensor with result & pass it to callback
            auto napiTensor = Tensor::NewInstance();
            Napi::ObjectWrap<Tensor>::Unwrap(napiTensor)->setTensor(outTensor);
            Callback().Call({Env().Undefined(), napiTensor});
        }

    private:
        ScriptModuleForwardAsyncWorker(torch::jit::script::Module module,
                                       torch::Tensor tensor, Napi::Function cb)
                : Napi::AsyncWorker(cb), inTensor(tensor), module(module) {}

        torch::jit::script::Module module;
        torch::Tensor inTensor;
        torch::Tensor outTensor;
    };


    Napi::FunctionReference ScriptModule::constructor;

    Napi::Object ScriptModule::Init(Napi::Env env, Napi::Object exports) {
        Napi::HandleScope scope(env);

        Napi::Function func = DefineClass(env, "ScriptModule", {
                InstanceMethod("forward", &ScriptModule::forward),
        });

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        exports.Set("ScriptModule", func);
        return exports;
    }

    ScriptModule::ScriptModule(const Napi::CallbackInfo &info) : Napi::ObjectWrap<ScriptModule>(info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
    }

    Napi::Object ScriptModule::NewInstance() {
        return constructor.New({});
    }

    void ScriptModule::forward(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        // assume first arg is napi tensor
        Tensor* napiTensor = Napi::ObjectWrap<Tensor>::Unwrap(info[0].As<Napi::Object>());
        // 2nd arg is callback
        Napi::Function cb = info[1].As<Napi::Function>();
        // run async worker
        torch::Tensor torchTensor = napiTensor->getTensor();
        ScriptModuleForwardAsyncWorker::forward(this->module, torchTensor, cb);
    }

    void ScriptModule::setModule(torch::jit::script::Module module) {
        this->module = module;
    }

}

