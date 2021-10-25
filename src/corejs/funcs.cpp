#include "funcs.h"
#include <stdio.h>

using namespace v8;

void addFunctionToTemplate(Isolate* isolate, Local<ObjectTemplate> templ, std::string name, FunctionCallback callback)
{
	Local<Object> data = Object::New(isolate);
	data->Set(isolate->GetCurrentContext(), LV8String("funcName"), LV8String(name.c_str()));
	templ->Set(LV8String(name.c_str()), FunctionTemplate::New(isolate, callback, data));
}

void createNamedGlobalObject(const std::string& name, Local<ObjectTemplate>& console, Local<Context>& context)
{
	Local<Object> consoleInstance;
	if (console->NewInstance(context).ToLocal(&consoleInstance)) {
		context->Global()->Set(context, LV8String(name.c_str()), consoleInstance);
	}
}

void corejs::funcs::stub(const FunctionCallbackInfo<Value>& info) { }
void corejs::funcs::console::log(const v8::FunctionCallbackInfo<v8::Value>& info) {
    for (int i = 0; i < info.Length(); ++i) {
        fputs(V8CString(info[i]).c_str(), stdout);
		fputs(" ");
    }
    fputs("\n", stdout);
}

void corejs::registerGlobals(Isolate* isolate, Local<Context>& context) {
    Local<ObjectTemplate> console = ObjectTemplate::New(isolate);
	addFunctionToTemplate(isolate, console, "assert", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "clear", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "count", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "countReset", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "debug", corejs::funcs::console::log);
	addFunctionToTemplate(isolate, console, "dir", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "dirxml", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "error", corejs::funcs::console::log);
	addFunctionToTemplate(isolate, console, "exception", corejs::funcs::console::log);
	addFunctionToTemplate(isolate, console, "group", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "groupCollapsed", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "groupEnd", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "info", corejs::funcs::console::log);
	addFunctionToTemplate(isolate, console, "log", corejs::funcs::console::log);
	addFunctionToTemplate(isolate, console, "table", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "time", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "timeEnd", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "timeLog", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "trace", corejs::funcs::stub);
	addFunctionToTemplate(isolate, console, "warn", corejs::funcs::console::log);

	createNamedGlobalObject("console", console, context);
}