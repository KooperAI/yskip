#include "node-api.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi.h"

#include "skipgram.h"
#include "random.h"
#include <string>

Napi::Object Skipgram::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Skipgram", {
        InstanceMethod<&Skipgram::testMethod>("testMethod"),
        StaticMethod<&Skipgram::CreateNewItem>("CreateNewItem"),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();

    *constructor = Napi::Persistent(func);
    exports.Set("Skipgram", func);

    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

Skipgram::Skipgram(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<Skipgram>(info) {
  Napi::Env env = info.Env();
  this->_instance = new yskip::Skipgram();
}

/**
 * Just a test method that returns true when invoked
 */
Napi::Value Skipgram::testMethod(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, true);
}

Napi::Value Skipgram::CreateNewItem(const Napi::CallbackInfo& info) {
  Napi::FunctionReference* constructor =
      info.Env().GetInstanceData<Napi::FunctionReference>();
  return constructor->New({});
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Skipgram::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
