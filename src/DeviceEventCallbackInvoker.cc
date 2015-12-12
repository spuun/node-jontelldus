#include "DeviceEventCallbackInvoker.h"

namespace JonTelldus {

  DeviceEventCallbackInvoker::DeviceEventCallbackInvoker(
      Nan::Callback *callback, int deviceId_, int method_, const char* data_)
        : CallbackInvoker(callback), deviceId(deviceId_), method(method_), data(data_) {   }

  void DeviceEventCallbackInvoker::Execute() {

    v8::Local<v8::Object> eventObj = Nan::New<v8::Object>();

    Set(eventObj, "deviceId", deviceId);
    Set(eventObj, "method", method);
    Set(eventObj, "data", data.c_str());

    v8::Local<v8::Value> argv[] = {
      eventObj
    };
    callback->Call(1, argv);
  }

}
