#include "AddDeviceWorker.h"

#include <telldus-core.h>

namespace JonTelldus {

  AddDeviceWorker::AddDeviceWorker(
      Nan::Callback *callback, 
      const char *name_,
      const char *protocol_,
      const char *model_,
      const std::map<std::string, std::string>& parameters_)
    : Nan::AsyncWorker(callback),
    name(name_),
    protocol(protocol_),
    model(model_),
    parameters(parameters_) {
    }

  void AddDeviceWorker::Execute() {
    deviceId = tdAddDevice();
    if (deviceId < 0) {
      const char *errorString = tdGetErrorString(deviceId);
      SetErrorMessage(errorString);
      delete errorString;
      return;
    }

    tdSetName(deviceId, name.c_str());
    tdSetProtocol(deviceId, protocol.c_str());
    tdSetModel(deviceId, model.c_str());
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
      tdSetDeviceParameter(deviceId, it->first.c_str(), it->second.c_str());
    }
  }

  void AddDeviceWorker::HandleOKCallback() {
    v8::Handle<v8::Value> argv[] = {
      Nan::Null(),
      Nan::New<v8::Number>(deviceId)
    };
    callback->Call(2, argv);
  }

  AddDeviceWorker *AddDeviceWorker::CreateFromArguments(Nan::NAN_METHOD_ARGS_TYPE info) {

    v8::Local<v8::Object> deviceObj = info[0]->ToObject();

    if (!Has(deviceObj, "name")) {
      Nan::ThrowError("No name property on device");
      return 0;
    }

    if (!Has(deviceObj, "protocol")) {
      Nan::ThrowError("No protocol property on device");
      return 0;
    }

    if (!Has(deviceObj, "model")) {
      Nan::ThrowError("No model property on device");
      return 0;
    }

    v8::String::Utf8Value name(Get(deviceObj, "name").ToLocalChecked()->ToString());
    v8::String::Utf8Value protocol(Get(deviceObj, "protocol").ToLocalChecked()->ToString());
    v8::String::Utf8Value model(Get(deviceObj, "model").ToLocalChecked()->ToString());

    std::map<std::string, std::string> deviceParameters;
    if (Has(deviceObj, "parameters")) {
      v8::Local<v8::Object> parametersObj = Get(deviceObj, "parameters").ToLocalChecked()->ToObject();
      for (auto& key: deviceParameterNames) {
        if (Has(parametersObj, key.c_str())) {
          v8::String::Utf8Value parameterValue(Get(parametersObj, key.c_str()).ToLocalChecked()->ToString());
          deviceParameters[key] = std::string(*parameterValue);
        }
      }
    }

    Nan::Callback *callback = 0;
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<v8::Function>());
    }

    return new AddDeviceWorker(callback, *name, *protocol, *model, deviceParameters);
  }

}
