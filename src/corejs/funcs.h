#pragma once
#include "v8.h"

namespace corejs {
    void registerGlobals(v8::Isolate* isolate, v8::Local<v8::Context>& context);
    namespace funcs {
        void stub(const v8::FunctionCallbackInfo<v8::Value>& info);

        namespace console {
            void log(const v8::FunctionCallbackInfo<v8::Value>& info);
        }
    }
}