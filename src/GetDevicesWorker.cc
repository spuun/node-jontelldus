#include "GetDevicesWorker.h"

#include <telldus-core.h>
#include <algorithm>

namespace JonTelldus {

  GetDevicesWorker::GetDevicesWorker(Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {};

  void GetDevicesWorker::Execute() {
    for (int i = 0; i < tdGetNumberOfDevices(); i++)
    {
      Device * device = new Device();
      device->id = tdGetDeviceId(i);

      char *name = tdGetName(device->id);
      char *protocol = tdGetProtocol(device->id);
      char *model = tdGetModel(device->id);

      device->name = name;
      device->protocol = protocol;
      device->model = model;

      tdReleaseString(name);
      tdReleaseString(protocol);
      tdReleaseString(model);

      _devices.push_back(device);
    }
  }

  void GetDevicesWorker::HandleOKCallback() {
    v8::Local<v8::Array> ret = Nan::New<v8::Array>();

    std::for_each(_devices.begin(), _devices.end(), [ret](Device* device) {
        v8::Local<v8::Object> deviceObj = Nan::New<v8::Object>();
        Set(deviceObj, "id", device->id);
        Set(deviceObj, "name", device->name.c_str());
        Set(deviceObj, "protocol", device->protocol.c_str());
        Set(deviceObj, "model", device->model.c_str());
        Set(ret, ret->Length(), deviceObj);
        delete device;
        });

    v8::Handle<v8::Value> argv[] = {
      ret
    };
    callback->Call(1, argv);
  }

}
