#include "SensorEventCallbackInvoker.h"

namespace JonTelldus {

  SensorEventCallbackInvoker::SensorEventCallbackInvoker(
      Nan::Callback *callback,
      const char *protocol_,
      const char *model_,
      int id_,
      int dataType_,
      const char *value_,
      int timestamp_)
        : CallbackInvoker(callback), 
        protocol(protocol_),
        model(model_),
        id(id_),
        dataType(dataType_),
        value(value_),
        timestamp(timestamp_) {   }
  void SensorEventCallbackInvoker::Execute() {

    v8::Handle<v8::Object> eventObj = Nan::New<v8::Object>();

    Set(eventObj, "id", id);
    Set(eventObj, "model", model.c_str());
    Set(eventObj, "protocol", protocol.c_str());
    Set(eventObj, "dataType", dataType);
    Set(eventObj, "value", value.c_str());
    Set(eventObj, "timestamp", Nan::New<v8::Date>((double)timestamp).ToLocalChecked());

    v8::Handle<v8::Value> argv[] = {
      eventObj
    };
    callback->Call(1, argv);
  }

}
