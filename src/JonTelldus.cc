
#include <string>
#include <map>

#include "JonTelldus.h"
#include "QueueInvoker.h"
#include "RawDeviceEventCallbackInvoker.h"
#include "GetDevicesWorker.h"

namespace JonTelldus {

  using v8::FunctionTemplate;
  using v8::Handle;
  using v8::Local;
  using v8::Isolate;
  using v8::Array;
  using v8::FunctionCallbackInfo;
  using v8::Value;
  using v8::Object;
  using v8::String;
  using v8::Number;
  using v8::Exception;
  using v8::Persistent;
  using v8::Function;

  void rawDeviceEventCallback(const char* data, int controllerId, int callbackId, void *context) {
    Nan::Callback *callback = static_cast<Nan::Callback *>(context);
		QueueCallback(new RawDeviceEventCallbackInvoker(callback, controllerId, data));
  }

  NAN_METHOD(addRawDeviceEventListener) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("argument must be function");
       return;
    }
    Nan::Callback *callback = new Nan::Callback(info[0].As<Function>());
    tdRegisterRawDeviceEvent(&rawDeviceEventCallback, callback);
    info.GetReturnValue().Set(Nan::Undefined());
  }

  NAN_METHOD(getDevices) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("argument must be function");
       return;
    }
    Nan::Callback *callback = new Nan::Callback(info[0].As<Function>());
    Nan::AsyncQueueWorker(new GetDevicesWorker(callback));
    info.GetReturnValue().Set(Nan::Undefined());
  }

  NAN_METHOD(turnOn) {
    if (info.Length() < 1) {
        Nan::ThrowSyntaxError("Missing id");
        return;
    }
    if (!info[0]->IsInt32()) {
      Nan::ThrowTypeError("Id must be integer");
      return;
    }
    info.GetReturnValue().Set(Nan::New<Number>(tdTurnOn(info[0]->IntegerValue())));
  }
  NAN_METHOD(turnOff) {
    if (info.Length() < 1) {
        Nan::ThrowSyntaxError("Missing id");
        return;
    }
    if (!info[0]->IsInt32()) {
      Nan::ThrowTypeError("Id must be integer");
      return;
    }
    info.GetReturnValue().Set(Nan::New<Number>(tdTurnOff(info[0]->IntegerValue())));
  }

NAN_MODULE_INIT(Init) {
  tdInit();
  Nan::Set(target, Nan::New<String>("getDevices").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(getDevices)).ToLocalChecked());
  Nan::Set(target, Nan::New<String>("turnOn").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(turnOn)).ToLocalChecked());
  Nan::Set(target, Nan::New<String>("turnOff").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(turnOff)).ToLocalChecked());
  Nan::Set(target, Nan::New<String>("addRawDeviceEventListener").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(addRawDeviceEventListener)).ToLocalChecked());
	// data type enum
	std::map<std::string, int> datatypes;
	datatypes["Temperature"] = TELLSTICK_TEMPERATURE;
	datatypes["Humidity"] = TELLSTICK_HUMIDITY;
	datatypes["RainTotal"] = TELLSTICK_RAINTOTAL;
	datatypes["RainRate"] = TELLSTICK_RAINRATE;
	datatypes["WindDirection"] = TELLSTICK_WINDDIRECTION;
	datatypes["WindAverage"] = TELLSTICK_WINDAVERAGE;
	datatypes["WindGust"] = TELLSTICK_WINDGUST;

	v8::Local<v8::Object> datatypesObj = Nan::New<v8::Object>();
	for (auto it = datatypes.begin(); it != datatypes.end(); ++it){
		Nan::Set(datatypesObj, Nan::New<v8::String>(it->first.c_str()).ToLocalChecked(),
			Nan::New<Number>(it->second));
	}
	Nan::Set(target, Nan::New<v8::String>("sensorValueType").ToLocalChecked(), datatypesObj);
 }
NODE_MODULE(jontelldus, Init)
}
