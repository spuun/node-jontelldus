#include <algorithm>
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
#include "AddDeviceWorker.h"
#include "UpdateDeviceWorker.h"
#include "RemoveDeviceWorker.h"
#include "ListenerRegister.h"
#include "Singleton.h"
#include "RemoveListenerWorker.h"
#include "DimDeviceWorker.h"

namespace JonTelldus {

  template class Singleton<ListenerRegister, Raw>;
  template class Singleton<ListenerRegister, Sensor>;
  template class Singleton<ListenerRegister, Device>;

  jstrarray deviceParameterNames = create_jstrarray
   ("devices")
   ("house")
   ("unit")
   ("code")
   ("system")
   ("units")
   ("fade");

  jenum methods = create_jenum
    ("TurnOn", TELLSTICK_TURNON)
    ("TurnOff", TELLSTICK_TURNOFF)
    ("Bell", TELLSTICK_BELL)
    ("Toggle", TELLSTICK_TOGGLE)
    ("Dim", TELLSTICK_DIM)
    ("Execute", TELLSTICK_EXECUTE)
    ("Up", TELLSTICK_UP)
    ("Down", TELLSTICK_DOWN)
    ("Stop", TELLSTICK_STOP);

  jenum sensorValueTypes = create_jenum
    ("Temperature", TELLSTICK_TEMPERATURE)
    ("Humidity", TELLSTICK_HUMIDITY)
    ("RainTotal", TELLSTICK_RAINTOTAL)
    ("RainRate", TELLSTICK_RAINRATE)
    ("WindDirection", TELLSTICK_WINDDIRECTION)
    ("WindAverage", TELLSTICK_WINDAVERAGE)
    ("WindGust", TELLSTICK_WINDGUST);

  jenum errorCodes = create_jenum
    ("NoError", TELLSTICK_SUCCESS)
    ("NotFound", TELLSTICK_ERROR_NOT_FOUND)
    ("PermissionDenied", TELLSTICK_ERROR_PERMISSION_DENIED)
    ("DeviceNotFound", TELLSTICK_ERROR_DEVICE_NOT_FOUND)
    ("MethodNotSupported", TELLSTICK_ERROR_METHOD_NOT_SUPPORTED)
    ("Communication", TELLSTICK_ERROR_COMMUNICATION)
    ("ConnectingService", TELLSTICK_ERROR_CONNECTING_SERVICE)
    ("UnknownResponse", TELLSTICK_ERROR_UNKNOWN_RESPONSE)
    ("Syntax", TELLSTICK_ERROR_SYNTAX)
    ("BrokenPipe", TELLSTICK_ERROR_BROKEN_PIPE)
    ("CommunicatingService", TELLSTICK_ERROR_COMMUNICATING_SERVICE)
    ("Unknown", TELLSTICK_ERROR_UNKNOWN);

  #define ADD_ENUM_MAP(target, name, values)\
  {\
    v8::Local<v8::Object> enumObj = Nan::New<v8::Object>();\
    for (jenum::iterator it = values.begin(); it != values.end(); ++it) \
      Set(enumObj, it->first.c_str(), it->second, (v8::PropertyAttribute)(v8::ReadOnly|v8::DontDelete)); \
    Set(target, name, enumObj, (v8::PropertyAttribute)(v8::ReadOnly|v8::DontDelete)); \
  }

  #define ADD_METHOD(target,name) \
    Set(target, #name, Nan::GetFunction(Nan::New<v8::FunctionTemplate>(name)).ToLocalChecked());

  #define INT_ID_METHOD(name, fn) \
  NAN_METHOD(name) { \
    if (info.Length() < 1) { \
      Nan::ThrowSyntaxError("Missing arguments. Id required, callback optional."); \
      return; \
    } \
    if (!info[0]->IsInt32()) { \
      Nan::ThrowSyntaxError("Id must be integer"); \
      return; \
    } \
    if (info.Length() > 1 && !info[1]->IsFunction()) { \
      Nan::ThrowSyntaxError("Callback must be function, duh"); \
      return; \
    } \
    Nan::Callback *callback = static_cast<Nan::Callback *>(0); \
    if (info.Length() > 1 && info[1]->IsFunction()) \
      callback = new Nan::Callback(info[1].As<v8::Function>()); \
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
      Nan::ThrowSyntaxError("Argument must be function");
      return;
    }
    ListenerRegister& reg = Singleton<ListenerRegister, Device>::getInstance();
    Nan::Callback *callback = new Nan::Callback(info[0].As<v8::Function>());
    reg.Register(callback, tdRegisterDeviceEvent(&deviceEventCallback, callback));
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
      Nan::ThrowSyntaxError("Argument must be function");
      return;
    }
    ListenerRegister& reg = Singleton<ListenerRegister, Sensor>::getInstance();
    Nan::Callback *callback = new Nan::Callback(info[0].As<v8::Function>());
    reg.Register(callback, tdRegisterSensorEvent(&sensorEventCallback, callback));
    info.GetReturnValue().Set(Nan::Undefined());
  }

  void rawDeviceEventCallback(const char* data, int controllerId, int callbackId, void *context) {
    Nan::Callback *callback = static_cast<Nan::Callback *>(context);
    QueueCallback(new RawDeviceEventCallbackInvoker(callback, data));
  }

  NAN_METHOD(addRawDeviceEventListener) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("Argument must be function");
      return;
    }
    ListenerRegister& reg = Singleton<ListenerRegister, Raw>::getInstance();
    Nan::Callback *callback = new Nan::Callback(info[0].As<v8::Function>());
    reg.Register(callback, tdRegisterRawDeviceEvent(&rawDeviceEventCallback, callback));
    info.GetReturnValue().Set(Nan::Undefined());
  }

  Nan::NAN_METHOD_RETURN_TYPE removeListener(Nan::NAN_METHOD_ARGS_TYPE info, ListenerRegister& reg) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("First argument must be function");
      return;
    }
    info.GetReturnValue().Set(Nan::Undefined());
    
    int tdid = reg.UnRegister(info[0].As<v8::Function>());
    Nan::Callback *callback = static_cast<Nan::Callback *>(0);
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<v8::Function>());
    }
    if (tdid == 0) {
      if (callback != 0){
        v8::Local<v8::Value> argv[] =  {
          Nan::Error("Listener is not registered")
        };
        callback->Call(1, argv);
      }
      return;
    }
    Nan::AsyncQueueWorker(new RemoveListenerWorker(callback, tdid));
  }

  NAN_METHOD(removeRawDeviceEventListener) {
    removeListener(info, Singleton<ListenerRegister, Raw>::getInstance());
  }
  NAN_METHOD(removeDeviceEventListener) {
    removeListener(info, Singleton<ListenerRegister, Device>::getInstance());
  }
  NAN_METHOD(removeSensorEventListener) {
    removeListener(info, Singleton<ListenerRegister, Sensor>::getInstance());
  }


  NAN_METHOD(getDevices) {
    if (info.Length() < 1 || !info[0]->IsFunction()) {
      Nan::ThrowSyntaxError("Argument must be function");
      return;
    }
    Nan::Callback *callback = new Nan::Callback(info[0].As<v8::Function>());
    Nan::AsyncQueueWorker(new GetDevicesWorker(callback));
    info.GetReturnValue().Set(Nan::Undefined());
  }

  NAN_METHOD(sendRawCommand) {
    if (info.Length() < 1 || !info[0]->IsString()) {
      Nan::ThrowSyntaxError("Missing argument command or not a string.");
      return;
    }

    Nan::Callback *callback = static_cast<Nan::Callback *>(0);
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<v8::Function>());
    }
    v8::String::Utf8Value utf8String(info[0]->ToString());
    Nan::AsyncQueueWorker(new SendRawCommandWorker(callback, *utf8String));
    info.GetReturnValue().Set(Nan::Undefined());
  }

  NAN_METHOD(addDevice) {    
    if (info.Length() < 1 || !info[0]->IsObject()) {
      Nan::ThrowSyntaxError("Missing device configuration object.");
      return;
    }

    AddDeviceWorker *worker = AddDeviceWorker::CreateFromArguments(info);
    if (worker != 0) {
      Nan::AsyncQueueWorker(worker);
      info.GetReturnValue().Set(Nan::Undefined());
    }
  }
  NAN_METHOD(updateDevice) {    
    if (info.Length() < 1 || !info[0]->IsObject()) {
      Nan::ThrowSyntaxError("Missing device configuration object.");
      return;
    }

    UpdateDeviceWorker *worker = UpdateDeviceWorker::CreateFromArguments(info);
    if (worker != 0) {
      Nan::AsyncQueueWorker(worker);
    }
    info.GetReturnValue().Set(Nan::Undefined());
  }
  NAN_METHOD(removeDevice) {    
    if (info.Length() < 1 || !info[0]->IsInt32()) {
      Nan::ThrowSyntaxError("Missing device id or not an integer value");
      return;
    }

    Nan::Callback *callback = static_cast<Nan::Callback *>(0);
    if (info.Length() > 1 && info[1]->IsFunction()) {
      callback = new Nan::Callback(info[1].As<v8::Function>());
    }

    RemoveDeviceWorker *worker = new RemoveDeviceWorker(callback, info[0]->IntegerValue());
    Nan::AsyncQueueWorker(worker);
    info.GetReturnValue().Set(Nan::Undefined());
  }

  NAN_METHOD(dim) {
    if (info.Length() < 2 || !info[0]->IsInt32() || !info[1]->IsInt32()) {
      Nan::ThrowSyntaxError("Id and level must be integers");
      return;
    }
    Nan::Callback *callback = static_cast<Nan::Callback *>(0);
    if (info.Length() > 2 && info[2]->IsFunction()) {
      callback = new Nan::Callback(info[2].As<v8::Function>());
    }

    DimDeviceWorker *worker = new DimDeviceWorker(callback, info[0]->IntegerValue(), info[1]->IntegerValue());
    Nan::AsyncQueueWorker(worker);
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
    ADD_METHOD(target, dim);
    ADD_METHOD(target, addRawDeviceEventListener);
    ADD_METHOD(target, removeRawDeviceEventListener);
    ADD_METHOD(target, addSensorEventListener);
    ADD_METHOD(target, removeSensorEventListener);
    ADD_METHOD(target, addDeviceEventListener);
    ADD_METHOD(target, removeDeviceEventListener);
    ADD_METHOD(target, sendRawCommand);
    ADD_METHOD(target, addDevice);
    ADD_METHOD(target, updateDevice);
    ADD_METHOD(target, removeDevice);

    ADD_ENUM_MAP(target, "sensorValueType", sensorValueTypes);
    ADD_ENUM_MAP(target, "method", methods);
    ADD_ENUM_MAP(target, "errorCode", errorCodes);
  }
  NODE_MODULE(jontelldus, Init)
}
