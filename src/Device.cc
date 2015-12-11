#include "Device.h"

namespace JonTelldus {

  Device Device::CreateFromObject(v8::Local<v8::Object> deviceObj) {
    Device device;
    if (Has(deviceObj, "id")) {
      device.id = Get(deviceObj, "id").ToLocalChecked()->IntegerValue();
    }
    if (Has(deviceObj, "name")) {
      v8::String::Utf8Value name(Get(deviceObj, "name").ToLocalChecked()->ToString());
      device.name = *name;
    }
    if (Has(deviceObj, "protocol")) {
      v8::String::Utf8Value protocol(Get(deviceObj, "protocol").ToLocalChecked()->ToString());
      device.protocol = *protocol;
    }
    if (Has(deviceObj, "model")) {
      v8::String::Utf8Value model(Get(deviceObj, "model").ToLocalChecked()->ToString());
      device.model = *model;
    }
    if (Has(deviceObj, "parameters")) {
      v8::Local<v8::Object> parametersObj = Get(deviceObj, "parameters").ToLocalChecked()->ToObject();
      for (jstrarray::iterator it = deviceParameterNames.begin(); 
            it != deviceParameterNames.end(); ++it) {
        if (Has(parametersObj, it->c_str())) {
          v8::String::Utf8Value parameterValue(Get(parametersObj, it->c_str()).ToLocalChecked()->ToString());
          device.parameters[*it] = std::string(*parameterValue);
        }
      }
    }

    return device;
  }

  void Device::UpdateDevice(const Device& device) {
    if (device.name.length() > 0) {
      tdSetName(device.id, device.name.c_str());
    }
    if (device.protocol.length() > 0) {
      tdSetProtocol(device.id, device.protocol.c_str());
    }
    if (device.model.length() > 0) {
      tdSetModel(device.id, device.model.c_str());
    }
    for (jstrarray::iterator name = deviceParameterNames.begin();
        name != deviceParameterNames.end(); ++name) {
      std::map<std::string, std::string>::const_iterator it = device.parameters.find(*name);
      if (it != device.parameters.end()) {
        tdSetDeviceParameter(device.id, it->first.c_str(), it->second.c_str());
      }
    }
  }
}
