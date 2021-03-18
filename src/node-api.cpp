#include "node-api.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi.h"


#include "skipgram.h"
#include "random.h"
#include <string>
#include <vector>

/**
 * Class definition, which is invoked at our general Init below.
 */
Napi::Object Skipgram::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Skipgram", {
        InstanceMethod<&Skipgram::testMethod>("TestMethod"),
        InstanceAccessor<&Skipgram::getAlpha>("alpha"),
        StaticMethod<&Skipgram::CreateNewItem>("CreateNewItem"),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();

    *constructor = Napi::Persistent(func);
    exports.Set("Skipgram", func);

    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

/**
 * Performs main method (word embeddings)
 */
Napi::Value mainMethod(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  if (info.Length() < 2) 
    Napi::TypeError::New(env, "Input and output expected").ThrowAsJavaScriptException();
  else {
    int argc=info.Length()+1;
    std::vector<char *> argv_pre;
    std::string first_arg("yskip");
    argv_pre.push_back((char *)first_arg.c_str());
    std::vector<std::string> argv_string;

    for (unsigned int k = 0; k < argc - 1; k++) {
        auto el = info[k];
        argv_string.push_back(
            std::string(el.As<Napi::String>()));
    }  

    for (auto &str: argv_string) {
      argv_pre.push_back((char *)str.c_str());
    }
    int result = cmdline_parse(argc,&argv_pre.at(0));
    return Napi::Number::New(env, result);
  }
  return Napi::Number::New(env, 1);
}


/**
 * Returns the current instance alpha value from its options.
 */
Napi::Value Skipgram::getAlpha(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  float alpha_value = this->_instance->alpha();
  return Napi::Number::New(env, alpha_value);
}

/**
 * Constructor for the class
 */
Skipgram::Skipgram(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<Skipgram>(info) {
  Napi::Env env = info.Env();
  if (info.Length() == 0) 
    this->_instance = new yskip::Skipgram();
  else {
    if (info[0].IsNumber()) {
      float alpha_value = info[0].As<Napi::Number>().FloatValue();
      auto options = yskip::Skipgram::Option();
      options.alpha = alpha_value;
      this->_instance = new yskip::Skipgram(options);
    } else {
      Napi::TypeError::New(env, "Numberexpected").ThrowAsJavaScriptException();
    }
  }
}

/**
 * Destructor for the class
 */
Skipgram::~Skipgram() {
  free(this->_instance);
}

/**
 * Just a test method that returns true when invoked
 */
Napi::Value Skipgram::testMethod(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, true);
}

/**
 * When calling new at the NodeJS engine this function is invoked.
 */
Napi::Value Skipgram::CreateNewItem(const Napi::CallbackInfo& info) {
  Napi::FunctionReference* constructor =
      info.Env().GetInstanceData<Napi::FunctionReference>();
  return constructor->New({});
}

/**
 * Initialization for the Napi
 */
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  //Skipgram::Init(env, exports);
  exports.Set(Napi::String::New(env, "parse"), Napi::Function::New<mainMethod>(env));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
