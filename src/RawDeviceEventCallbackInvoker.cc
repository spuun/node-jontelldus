#include "RawDeviceEventCallbackInvoker.h"

namespace JonTelldus {

	RawDeviceEventCallbackInvoker::RawDeviceEventCallbackInvoker(Nan::Callback *callback, int controllerId_, const char *data_) 
	  : CallbackInvoker(callback), controllerId(controllerId_), data(data_) {
	}
	void RawDeviceEventCallbackInvoker::Execute() {
	  v8::Handle<v8::Value> argv[] = {
	    Nan::New<v8::Number>(controllerId),
	    Nan::New<v8::String>(data.c_str()).ToLocalChecked()
	  };
  callback->Call(2, argv);
	}

}
