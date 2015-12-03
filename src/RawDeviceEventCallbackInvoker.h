#ifndef _RawDeviceEventCallbackCaller_h_
#define _RawDeviceEventCallbackCaller_h_

#include "JonTelldus.h"
#include "QueueInvoker.h" 

namespace JonTelldus {

  class RawDeviceEventCallbackInvoker
    : public CallbackInvoker {
      private:
        std::string data;
      public:
        RawDeviceEventCallbackInvoker(Nan::Callback *callback, const char *data_); 
        void Execute();
    };

}

#endif

