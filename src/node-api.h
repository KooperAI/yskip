#include "js_native_api_types.h"
#include <node.h>
#include <node_api.h>

napi_value SayHello(napi_env env, napi_callback_info info);
napi_value Init(napi_env env, napi_value exports);
NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
