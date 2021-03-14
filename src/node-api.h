#include "js_native_api_types.h"
#include <node.h>
#include <napi.h>
#include <node_api.h>

napi_value SayHello(const Napi::CallbackInfo &info);
Napi::Object Init(Napi::Env env, Napi::Object exports);
