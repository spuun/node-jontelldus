#include "GetDevicesWorker.h"

#include <telldus-core.h>
#include <algorithm>

namespace JonTelldus {

  GetDevicesWorker::GetDevicesWorker(Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {};

  void GetDevicesWorker::Execute() {
    for (int i = 0; i < tdGetNumberOfDevices(); i++)
    {
      int deviceId = tdGetDeviceId(i);
      if (deviceId == -1) {
        continue;
      }
      Device * device = new Device();
      device->id = deviceId;

      char *name = tdGetName(device->id);
      char *protocol = tdGetProtocol(device->id);
      char *model = tdGetModel(device->id);

      device->name = name;
      device->protocol = protocol;
      device->model = model;

      tdReleaseString(name);
      tdReleaseString(protocol);
      tdReleaseString(model);

      for (auto& key: deviceParameterNames) {
        char *paramValue = tdGetDeviceParameter(device->id, key.c_str(), "");
        std::string paramStrValue(paramValue);
        tdReleaseString(paramValue);
        if (paramStrValue.length() > 0) {
          device->parameters[key] = paramStrValue; 
        }
      }

      int supportedMethods = tdMethods(device->id, 0xFFFF);      
      for (auto& method: methods) {
        if (supportedMethods & method.value) {
          device->methods.push_back(method.key);
        }
      }
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

        v8::Local<v8::Object> paramObj = Nan::New<v8::Object>();
        for (auto it = device->parameters.begin(); it != device->parameters.end(); ++it) {
          Set(paramObj, it->first.c_str(), it->second.c_str());
        }
        Set(deviceObj, "parameters", paramObj);
        v8::Local<v8::Array> methodArr = Nan::New<v8::Array>();
        for (auto it = device->methods.begin(); it != device->methods.end(); ++it) {
          Set(methodArr, (int)methodArr->Length(), it->c_str());
        }
        Set(deviceObj, "methods", methodArr);
        Set(ret, ret->Length(), deviceObj);
        delete device;
        });

    v8::Handle<v8::Value> argv[] = {
      ret
    };
    callback->Call(1, argv);
  }

}
