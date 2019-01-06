#ifndef LIBTORCHJS_JIT_H
#define LIBTORCHJS_JIT_H

#include <napi.h>

namespace libtorchjs {

    Napi::Object JitInit(Napi::Env env, Napi::Object exports);

}

#endif