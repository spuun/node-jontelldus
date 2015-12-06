#include "AddDeviceWorker.h"

#include <telldus-core.h>

AddDeviceWorker::AddDeviceWorker(
      Nan::Callback *callback, 
      const char *name_,
      const char *protocol_,
      const char *model_) 
  : Nan::AsyncWorker(callback),
    name(name_),
    protocol(protocol_),
    model(model_) {
}

void AddDeviceWorker::Execute() {
  deviceId = tdAddDevice();
  if (deviceId < 0) {
    const char *errorString = tdGetErrorString(deviceId);
    SetErrorMessage(errorString);
    delete errorString;
    return;
  }

  if (!tdSetName(deviceId, name.c_str())) {
    SetErrorMessage("Failed to set name.");
    return;
  }

  if (!tdSetProtocol(deviceId, protocol.c_str())) {
    SetErrorMessage("Failed to set protocol.");
    return;
  }

  if (!tdSetModel(deviceId, model.c_str())) {
    SetErrorMessage("Failed to set model.");
    return;
  }
}

void AddDeviceWorker::HandleOKCallback() {
  v8::Handle<v8::Value> argv[] = {
    Nan::Null(),
    Nan::New<v8::Number>(deviceId)
  };
  callback->Call(2, argv);
}