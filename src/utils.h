#ifndef LIBTORCHJS_UTILS_H
#define LIBTORCHJS_UTILS_H

#include <napi.h>
#include <stdlib.h>

namespace libtorchjs {

    std::vector<int64_t> napiArrayToVector(Napi::Array arr);

}

#endif