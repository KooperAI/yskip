#include "js_native_api_types.h"
#include <node.h>
#include <napi.h>
#include <node_api.h>

#include "skipgram.h"

Napi::Object Init(Napi::Env env, Napi::Object exports);

/**
 * Skipgram wrapper for NodeJS
 */
class Skipgram : public Napi::ObjectWrap<Skipgram> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Skipgram(const Napi::CallbackInfo& info);
    Napi::Value getAlpha(const Napi::CallbackInfo &info);
    ~Skipgram();
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

  private:
    Napi::Value testMethod(const Napi::CallbackInfo& info);
    yskip::Skipgram *_instance;
};

