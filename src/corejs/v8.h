#pragma once

#include <libplatform/libplatform.h>
#include <v8.h>
#include <v8-context.h>
#include <v8-initialization.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-primitive.h>
#include <v8-script.h>

inline v8::MaybeLocal<v8::String> V8String(const char* str) {
	return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str);
}

inline v8::Local<v8::String> LV8String(const char* str) {
	v8::MaybeLocal<v8::String> ret = V8String(str);
	if (ret.IsEmpty()) {
		return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "").ToLocalChecked();
	}
	return ret.ToLocalChecked();
}
inline v8::Local<v8::String> ValueToString(v8::Local<v8::Value> val) {
	return val->ToString(v8::Isolate::GetCurrent()->GetCurrentContext()).ToLocalChecked();
}
inline std::string V8CString(const v8::Local<v8::String>& str) {
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::String::Utf8Value result(isolate, str);
	std::string cppStr(*result);
	return cppStr;
}
inline std::string V8CString(const v8::Local<v8::Value>& str) {
	return V8CString(ValueToString(str));
}
