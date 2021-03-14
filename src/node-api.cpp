#include "node-api.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi.h"

#include <string>

/**
 * Mostly based at the example at:
 * https://www.lohika.com/node-js-n-api-implementation-and-performance-comparison
 */
napi_value sayHello(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  // Validate argument count and type
  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Input argument must be a string")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  // Get input parameter
  const Napi::String input_string = info[0].As<Napi::String>();
  std::string result_string = Napi::String::New(env, "");
  result_string.insert(0, "Hello, ");
  result_string.append(input_string);

  return Napi::String::New(env, result_string); 
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
      Napi::String::New(env, "sayHello"),
      Napi::Function::New(env, sayHello));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
