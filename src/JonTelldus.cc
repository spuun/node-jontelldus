#include <string>
#include <map>

#include "JonTelldus.h"
#include "QueueInvoker.h"
#include "RawDeviceEventCallbackInvoker.h"
#include "SensorEventCallbackInvoker.h"
#include "GetDevicesWorker.h"
#include "IntIdWorker.h"

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

#define INT_ID_METHOD(name, fn) \
  NAN_METHOD(name) { \
    if (info.Length() < 2) { \
      Nan::ThrowSyntaxError("Missing arguments. Id and callback needed."); \
      return; \
    } \
    if (!info[0]->IsInt32()) { \
      Nan::ThrowSyntaxError("Id must be integer"); \
      return; \
    } \
    if (!info[1]->IsFunction()) { \
      Nan::ThrowSyntaxError("Callback must be function, duh"); \
      return; \
    } \
    Nan::Callback *callback = new Nan::Callback(info[1].As<Function>()); \
    Nan::AsyncQueueWorker(new IntIdWorker(callback, fn, info[0]->IntegerValue())); \
    info.GetReturnValue().Set(Nan::Undefined()); \
  } 


  void sensorEventCallback(
      const char *protocol,
      const char *model,
      int id,
      int dataType,
      const char *value,
      int timestamp,
      int callbackId,
      void *context) {
    Nan::Callback *callback = static_cast<Nan::Callback *>(context);
    QueueCallback(new SensorEventCallbackInvoker(callback, protocol, model, id, dataType, value, timestamp));
  }

  NAN_METHOD(addSensorEventListener) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("argument must be function");
      return;
    }
    Nan::Callback *callback = new Nan::Callback(info[0].As<Function>());
    tdRegisterSensorEvent(&sensorEventCallback, callback);
    info.GetReturnValue().Set(Nan::Undefined());
  }

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


  INT_ID_METHOD(up, tdUp);
  INT_ID_METHOD(down, tdDown);
  INT_ID_METHOD(bell, tdBell);
  INT_ID_METHOD(turnOn, tdTurnOn);
  INT_ID_METHOD(turnOff, tdTurnOff);
  INT_ID_METHOD(execute, tdExecute);
  INT_ID_METHOD(stop, tdStop);
  INT_ID_METHOD(learn, tdLearn);

  NAN_MODULE_INIT(Init) {
    tdInit();
    Set(target, "getDevices", Nan::GetFunction(Nan::New<FunctionTemplate>(getDevices)).ToLocalChecked());
    Set(target, "turnOn", Nan::GetFunction(Nan::New<FunctionTemplate>(turnOn)).ToLocalChecked());
    Set(target, "turnOff",Nan::GetFunction(Nan::New<FunctionTemplate>(turnOff)).ToLocalChecked());
    Set(target, "bell",Nan::GetFunction(Nan::New<FunctionTemplate>(bell)).ToLocalChecked());
    Set(target, "up",Nan::GetFunction(Nan::New<FunctionTemplate>(up)).ToLocalChecked());
    Set(target, "down",Nan::GetFunction(Nan::New<FunctionTemplate>(down)).ToLocalChecked());
    Set(target, "execute",Nan::GetFunction(Nan::New<FunctionTemplate>(execute)).ToLocalChecked());
    Set(target, "stop",Nan::GetFunction(Nan::New<FunctionTemplate>(stop)).ToLocalChecked());
    Set(target, "learn",Nan::GetFunction(Nan::New<FunctionTemplate>(learn)).ToLocalChecked());
    Set(target, "addRawDeviceEventListener", Nan::GetFunction(Nan::New<FunctionTemplate>(addRawDeviceEventListener)).ToLocalChecked());
    Set(target, "addSensorEventListener", Nan::GetFunction(Nan::New<FunctionTemplate>(addSensorEventListener)).ToLocalChecked());

    // "ENUMS"
    v8::PropertyAttribute readOnlyDontDelete = (v8::PropertyAttribute)(v8::ReadOnly|v8::DontDelete);
    // data type enum
    v8::Local<v8::Object> datatypesObj = Nan::New<v8::Object>();
    Set(datatypesObj, "Temperature", TELLSTICK_TEMPERATURE, readOnlyDontDelete);
    Set(datatypesObj, "Humidity", TELLSTICK_HUMIDITY, readOnlyDontDelete);
    Set(datatypesObj, "RainTotal", TELLSTICK_RAINTOTAL, readOnlyDontDelete);
    Set(datatypesObj, "RainRate", TELLSTICK_RAINRATE, readOnlyDontDelete);
    Set(datatypesObj, "WindDirection", TELLSTICK_WINDDIRECTION, readOnlyDontDelete);
    Set(datatypesObj, "WindAverage", TELLSTICK_WINDAVERAGE, readOnlyDontDelete);
    Set(datatypesObj, "WindGust", TELLSTICK_WINDGUST, readOnlyDontDelete);
    Set(target, "sensorValueType", datatypesObj, readOnlyDontDelete); 
    // methods enum
    v8::Local<v8::Object> methodsObj = Nan::New<v8::Object>();
    Set(methodsObj, "TurnOn", TELLSTICK_TURNON, readOnlyDontDelete);
    Set(methodsObj, "TurnOff", TELLSTICK_TURNOFF, readOnlyDontDelete);
    Set(methodsObj, "Bell", TELLSTICK_BELL, readOnlyDontDelete);
    Set(methodsObj, "Toggle", TELLSTICK_TOGGLE, readOnlyDontDelete);
    Set(methodsObj, "Dim", TELLSTICK_DIM, readOnlyDontDelete);
    Set(methodsObj, "Execute", TELLSTICK_EXECUTE, readOnlyDontDelete);
    Set(methodsObj, "Up", TELLSTICK_UP, readOnlyDontDelete);
    Set(methodsObj, "Down", TELLSTICK_DOWN, readOnlyDontDelete);
    Set(methodsObj, "Stop", TELLSTICK_STOP, readOnlyDontDelete);
    Set(target, "method", methodsObj, readOnlyDontDelete);
    // error codes
    v8::Local<v8::Object> errorObj = Nan::New<v8::Object>();
    Set(errorObj, "NoError", TELLSTICK_SUCCESS, readOnlyDontDelete);
    Set(errorObj, "NotFound", TELLSTICK_ERROR_NOT_FOUND, readOnlyDontDelete);
    Set(errorObj, "PermissionDenied", TELLSTICK_ERROR_PERMISSION_DENIED, readOnlyDontDelete);
    Set(errorObj, "DeviceNotFound", TELLSTICK_ERROR_DEVICE_NOT_FOUND, readOnlyDontDelete);
    Set(errorObj, "MethodNotSupported", TELLSTICK_ERROR_METHOD_NOT_SUPPORTED, readOnlyDontDelete);
    Set(errorObj, "Communication", TELLSTICK_ERROR_COMMUNICATION, readOnlyDontDelete);
    Set(errorObj, "ConnectingService", TELLSTICK_ERROR_CONNECTING_SERVICE, readOnlyDontDelete);
    Set(errorObj, "UnknownResponse", TELLSTICK_ERROR_UNKNOWN_RESPONSE, readOnlyDontDelete);
    Set(errorObj, "Syntax", TELLSTICK_ERROR_SYNTAX, readOnlyDontDelete);
    Set(errorObj, "BrokenPipe", TELLSTICK_ERROR_BROKEN_PIPE, readOnlyDontDelete);
    Set(errorObj, "CommunicatingService", TELLSTICK_ERROR_COMMUNICATING_SERVICE, readOnlyDontDelete);
    Set(errorObj, "Unknown", TELLSTICK_ERROR_UNKNOWN, readOnlyDontDelete);
    Set(target, "errorCode", errorObj, readOnlyDontDelete);
  }
  NODE_MODULE(jontelldus, Init)
}
