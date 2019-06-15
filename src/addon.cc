
#include "Consumer.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Consumer::Init(env, exports);
    return exports;
}

NODE_API_MODULE(addon, Init)
