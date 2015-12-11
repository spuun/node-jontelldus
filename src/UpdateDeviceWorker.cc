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
    v8::Local<v8::Object> deviceObj = info[0]->ToObject();
  
    if (!Has(deviceObj, "id")) {
      Nan::ThrowError("Missing device id.");
      return static_cast<UpdateDeviceWorker*>(0);
    }

    Device device = Device::CreateFromObject(deviceObj);

    Nan::Callback *callback = 0;
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<v8::Function>());
    }
    return new UpdateDeviceWorker(callback, device);
  }

}
