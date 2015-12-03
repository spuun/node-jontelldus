#include <string>
#include <map>

#include "JonTelldus.h"
#include "QueueInvoker.h"
#include "RawDeviceEventCallbackInvoker.h"
#include "SensorEventCallbackInvoker.h"
#include "DeviceEventCallbackInvoker.h"
#include "GetDevicesWorker.h"
#include "IntIdWorker.h"
#include "SendRawCommandWorker.h"

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

  struct keyvalue {
    const char *key;
    int value;
  };

  struct keyvalue sensorValueTypes[] = {
    {"Temperature", TELLSTICK_TEMPERATURE },
    {"Humidity", TELLSTICK_HUMIDITY },
    {"RainTotal", TELLSTICK_RAINTOTAL },
    {"RainRate", TELLSTICK_RAINRATE },
    {"WindDirection", TELLSTICK_WINDDIRECTION },
    {"WindAverage", TELLSTICK_WINDAVERAGE },
    {"WindGust", TELLSTICK_WINDGUST }
  };
  struct keyvalue methods[] = {
    { "TurnOn", TELLSTICK_TURNON },
    { "TurnOff", TELLSTICK_TURNOFF },
    { "Bell", TELLSTICK_BELL },
    { "Toggle", TELLSTICK_TOGGLE },
    { "Dim", TELLSTICK_DIM },
    { "Execute", TELLSTICK_EXECUTE },
    { "Up", TELLSTICK_UP},
    { "Down", TELLSTICK_DOWN },
    { "Stop", TELLSTICK_STOP },
  };
  struct keyvalue errorCodes[] = {
    { "NoError", TELLSTICK_SUCCESS },
    { "NotFound", TELLSTICK_ERROR_NOT_FOUND }, 
    { "PermissionDenied", TELLSTICK_ERROR_PERMISSION_DENIED },
    { "DeviceNotFound", TELLSTICK_ERROR_DEVICE_NOT_FOUND },
    { "MethodNotSupported", TELLSTICK_ERROR_METHOD_NOT_SUPPORTED },
    { "Communication", TELLSTICK_ERROR_COMMUNICATION },
    { "ConnectingService", TELLSTICK_ERROR_CONNECTING_SERVICE },
    { "UnknownResponse", TELLSTICK_ERROR_UNKNOWN_RESPONSE },
    { "Syntax", TELLSTICK_ERROR_SYNTAX },
    { "BrokenPipe", TELLSTICK_ERROR_BROKEN_PIPE },
    { "CommunicatingService", TELLSTICK_ERROR_COMMUNICATING_SERVICE },
    { "Unknown", TELLSTICK_ERROR_UNKNOWN }
  };

#define ADD_METHOD(target,name) \
  Set(target, #name, Nan::GetFunction(Nan::New<FunctionTemplate>(name)).ToLocalChecked());

#define ADD_ENUM(target, name, values)\
  {\
    v8::Local<v8::Object> enumObj = Nan::New<v8::Object>();\
    for (auto& item: values)\
      Set(enumObj, item.key, item.value, (v8::PropertyAttribute)(v8::ReadOnly|v8::DontDelete));\
    Set(target, name, enumObj, (v8::PropertyAttribute)(v8::ReadOnly|v8::DontDelete)); \
  }

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

  void deviceEventCallback(
      int deviceId,
      int method,
      const char *data,
      int callbackId,
      void *context) {
    Nan::Callback *callback = static_cast<Nan::Callback *>(context);
    QueueCallback(new DeviceEventCallbackInvoker(callback, deviceId, method, data));
  }

  NAN_METHOD(addDeviceEventListener) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("argument must be function");
      return;
    }
    Nan::Callback *callback = new Nan::Callback(info[0].As<Function>());
    tdRegisterDeviceEvent(&deviceEventCallback, callback);
    info.GetReturnValue().Set(Nan::Undefined());
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

  NAN_METHOD(sendRawCommand) {
    if (info.Length() < 1 || !info[0]->IsString()) {
      Nan::ThrowSyntaxError("Missing argument command or not a string.");
      return;
    }

    Nan::Callback *callback = 0;
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<Function>());
    }
    v8::String::Utf8Value utf8String(info[0]->ToString());
    Nan::AsyncQueueWorker(new SendRawCommandWorker(callback, *utf8String));
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
    ADD_METHOD(target, getDevices);
    ADD_METHOD(target, turnOn);
    ADD_METHOD(target, turnOff);
    ADD_METHOD(target, bell);
    ADD_METHOD(target, up);
    ADD_METHOD(target, down);
    ADD_METHOD(target, execute);
    ADD_METHOD(target, stop);
    ADD_METHOD(target, learn);
    ADD_METHOD(target, addRawDeviceEventListener);
    ADD_METHOD(target, addSensorEventListener);
    ADD_METHOD(target, addDeviceEventListener);
    ADD_METHOD(target, sendRawCommand);

    ADD_ENUM(target, "sensorValueType", sensorValueTypes);
    ADD_ENUM(target, "method", methods);
    ADD_ENUM(target, "errorCode", errorCodes);
  }
  NODE_MODULE(jontelldus, Init)
}
