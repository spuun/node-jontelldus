#include "RawDeviceEventCallbackInvoker.h"

namespace JonTelldus {

  RawDeviceEventCallbackInvoker::RawDeviceEventCallbackInvoker(Nan::Callback *callback, const char *data_) 
    : CallbackInvoker(callback), data(data_) {
    }
  void RawDeviceEventCallbackInvoker::Execute() {
    v8::Local<v8::Value> argv[] = {
      Nan::New<v8::String>(data.c_str()).ToLocalChecked()
    };
    callback->Call(1, argv);
  }

}
