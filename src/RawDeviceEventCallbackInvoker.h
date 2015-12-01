#ifndef _RawDeviceEventCallbackCaller_h_
#define _RawDeviceEventCallbackCaller_h_

#include "JonTelldus.h"
#include "QueueInvoker.h" 

namespace JonTelldus {

class RawDeviceEventCallbackInvoker
	: public CallbackInvoker {
		private:
			int controllerId;
			std::string data;
		public:
	RawDeviceEventCallbackInvoker(Nan::Callback *callback, int controllerId_, const char *data_); 
	void Execute();
};

}

#endif

