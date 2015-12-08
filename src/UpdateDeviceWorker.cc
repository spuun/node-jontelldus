#include "UpdateDeviceWorker.h"

#include <telldus-core.h>

namespace JonTelldus {

  UpdateDeviceWorker::UpdateDeviceWorker(
      Nan::Callback *callback, 
      const Device &device_) 
    : WorkerBase(callback),
      device(device_)
    {
  }

  void UpdateDeviceWorker::Execute() {
    if (device.id <= 0) {
      SetErrorMessage("Invalid device id");
      return;
    }
    Device::UpdateDevice(device);
  }

  void UpdateDeviceWorker::HandleOKCallback() {
    if (callback == 0) {
      return;
    }
    v8::Handle<v8::Value> argv[] = {
      Nan::Null(),
      Nan::New<v8::Number>(device.id)
    };
    callback->Call(2, argv);
  }

  UpdateDeviceWorker *UpdateDeviceWorker::CreateFromArguments(Nan::NAN_METHOD_ARGS_TYPE info) {
    v8::Local<v8::Number> deviceId = info[0]->ToNumber();
    v8::Local<v8::Object> deviceObj = info[1]->ToObject();
  
    Device device = Device::CreateFromObject(deviceObj);
    device.id = deviceId->IntegerValue(); 

    Nan::Callback *callback = 0;
    if (info.Length() > 2 && info[2]->IsFunction()) {
      callback = new Nan::Callback(info[2].As<v8::Function>());
    }
    return new UpdateDeviceWorker(callback, device);
  }

}
