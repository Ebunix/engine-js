#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v8.h"
#include "corejs.h"
#include "funcs.h"

v8::Isolate::CreateParams create_params;
v8::Isolate* isolate;
std::unique_ptr<v8::Platform> currentPlatform;
bool globalsRegistered = false;

int corejs::init(char* data) {

  // Initialize V8.
  v8::V8::InitializeICUDefaultLocation(data);
  v8::V8::InitializeExternalStartupData(data);
  currentPlatform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(currentPlatform.get());
  v8::V8::Initialize();

  // Create a new Isolate and make it the current one.
  create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  isolate = v8::Isolate::New(create_params);

  return 0;
}

void corejs::destroy() {
  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete create_params.array_buffer_allocator;  
}

void corejs::run(const std::string& code) {
  v8::Isolate::Scope isolate_scope(isolate);
  v8::HandleScope handle_scope(isolate);
  v8::Local<v8::Context> context = v8::Context::New(isolate);
  v8::Context::Scope context_scope(context);
  {
    if (!globalsRegistered) {
      corejs::registerGlobals(isolate, context);
      globalsRegistered = true;
    }
    v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, code.c_str()).ToLocalChecked();
    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
    v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();
  }
}