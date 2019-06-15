#pragma once

#include <napi.h>

class Consumer : public Napi::ObjectWrap<Consumer>
{
public:
    Consumer(const Napi::CallbackInfo&);
    Napi::Value Close(const Napi::CallbackInfo&);

    static void Init(Napi::Env, Napi::Object);

private:
    static Napi::FunctionReference constructor;
    Napi::ThreadSafeFunction callback;
};
