#include "AddDeviceWorker.h"

#include <telldus-core.h>

namespace JonTelldus {

  AddDeviceWorker::AddDeviceWorker(Nan::Callback *callback, const Device& device_) 
    : UpdateDeviceWorker(callback, device_) {

  }

  void AddDeviceWorker::Execute() {
    int deviceId = tdAddDevice();
    if (deviceId < 0) {
      char *error= tdGetErrorString(deviceId);
      SetErrorMessage(error);
      tdReleaseString(error);
      return;
    }
    device.id = deviceId;
    UpdateDeviceWorker::Execute();
  }

  AddDeviceWorker *AddDeviceWorker::CreateFromArguments(Nan::NAN_METHOD_ARGS_TYPE info) {

    v8::Local<v8::Object> deviceObj = info[0]->ToObject();

    Device device = Device::CreateFromObject(deviceObj);

    Nan::Callback *callback = 0;
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<v8::Function>());
    }

    return new AddDeviceWorker(callback, device);
  }

}
