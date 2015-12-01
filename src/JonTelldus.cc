
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
  Set(target, "getDevices", Nan::GetFunction(Nan::New<FunctionTemplate>(getDevices)).ToLocalChecked());
  Set(target, "turnOn", Nan::GetFunction(Nan::New<FunctionTemplate>(turnOn)).ToLocalChecked());
  Set(target, "turnOff",Nan::GetFunction(Nan::New<FunctionTemplate>(turnOff)).ToLocalChecked());
  Set(target, "addRawDeviceEventListener", Nan::GetFunction(Nan::New<FunctionTemplate>(addRawDeviceEventListener)).ToLocalChecked());
	// data type enum
	v8::Local<v8::Object> datatypesObj = Nan::New<v8::Object>();
	Set(datatypesObj, "Temperature", TELLSTICK_TEMPERATURE);
	Set(datatypesObj, "Humidity", TELLSTICK_HUMIDITY);
	Set(datatypesObj, "RainTotal", TELLSTICK_RAINTOTAL);
	Set(datatypesObj, "RainRate", TELLSTICK_RAINRATE);
	Set(datatypesObj, "WindDirection", TELLSTICK_WINDDIRECTION);
	Set(datatypesObj, "WindAverage", TELLSTICK_WINDAVERAGE);
	Set(datatypesObj, "WindGust", TELLSTICK_WINDGUST);
	Set(target, "sensorValueType", datatypesObj);
 }
NODE_MODULE(jontelldus, Init)
}
