#include "GetDevicesWorker.h"

#include <telldus-core.h>
#include <algorithm>
#include <functional>

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

      device->type = "Unknown";
      int type = tdGetDeviceType(device->id);
      jenum::const_iterator typeIt;
      for (typeIt = deviceTypes.begin(); typeIt != deviceTypes.end(); ++typeIt) {
        if (typeIt->second == type) {
          device->type = typeIt->first; 
        }
      }

      for (jstrarray::iterator name = deviceParameterNames.begin();
          name != deviceParameterNames.end(); ++name) {
        char *paramValue = tdGetDeviceParameter(device->id, name->c_str(), "");
        std::string paramStrValue(paramValue);
        tdReleaseString(paramValue);
        if (paramStrValue.length() > 0) {
          device->parameters[*name] = paramStrValue; 
        }
      }

      int supportedMethods = tdMethods(device->id, 0xFFFF);      
      for (jenum::iterator it = methods.begin(); it!= methods.end(); ++it) {
        if (supportedMethods & it->second) {
          device->methods.push_back(it->first);
        }
      }
      _devices.push_back(device);
    }
  }

  void GetDevicesWorker::HandleOKCallback() {
    v8::Local<v8::Array> ret = Nan::New<v8::Array>();

    std::vector<Device*>::iterator deviceIt;    
    for (deviceIt = _devices.begin(); deviceIt != _devices.end(); ++deviceIt) {
      Device *device = *deviceIt;
      v8::Local<v8::Object> deviceObj = Nan::New<v8::Object>();
      Set(deviceObj, "id", device->id);
      Set(deviceObj, "name", device->name.c_str());
      Set(deviceObj, "protocol", device->protocol.c_str());
      Set(deviceObj, "model", device->model.c_str());
      Set(deviceObj, "type", device->type.c_str());

      v8::Local<v8::Object> paramObj = Nan::New<v8::Object>();
      std::map<std::string, std::string>::iterator it;
      for (it = device->parameters.begin(); it != device->parameters.end(); ++it) {
        Set(paramObj, it->first.c_str(), it->second.c_str());
      }
      Set(deviceObj, "parameters", paramObj);
      v8::Local<v8::Array> methodArr = Nan::New<v8::Array>();
      for (jstrarray::iterator it = device->methods.begin(); it != device->methods.end(); ++it) {
        Set(methodArr, (int)methodArr->Length(), it->c_str());
      }
      Set(deviceObj, "methods", methodArr);
      Set(ret, ret->Length(), deviceObj);
      delete device;
    };

    v8::Local<v8::Value> argv[] = {
      ret
    };
    callback->Call(1, argv);
  }

}
