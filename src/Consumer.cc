#include "Consumer.h"

using namespace Napi;

Consumer::Consumer(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
//    Napi::HandleScope scope(env);


    // Create a ThreadSafeFunction and store it in private class member
    callback = ThreadSafeFunction::New(
        env,
        info[2].As<Function>(),  // JavaScript function called asynchronously
        "EMS Consumer",    // Name
        20,                      // TODO: makge configurable (queue length)
        1,                       // Only one thread will use this initially
        []( Napi::Env ) {        // Finalizer used to clean threads up
            printf("ThreadSafeFunction finalizer called\n");
        }
    );

    /*
     REMOVED
     At this point I would start an EMS consumer, which calls a callback.
     The callback is a static function of this class (removed for brevity). That
     callback would be passed a pointer to this class, which allows it to access
     the `callback` and invoke `callback.BlockingCall(...)`

     As the issue is reproducible without all that code I removed it.
    */
}

Napi::Value Consumer::Close(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    printf("Consumer::Close called. releasing tsfn...\n");
    callback.Release();
    printf("Consumer::Close called. tsfn released.\n");
    return env.Undefined();
}

Napi::FunctionReference Consumer::constructor;

void Consumer::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Consumer", {
        Consumer::InstanceMethod("close", &Consumer::Close),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Consumer", func);
}
