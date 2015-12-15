#ifndef _DeviceEventCallbackCaller_h_
#define _DeviceEventCallbackCaller_h_

#include "JonTelldus.h"
#include "QueueInvoker.h" 

#include <string>

namespace JonTelldus {

  class DeviceEventCallbackInvoker
    : public CallbackInvoker {
      private:
        int deviceId;
        int method;
        std::string data;
      public:
        DeviceEventCallbackInvoker(
          Nan::Callback *callback,
          int deviceId_,
          int method_,
          const char* data_);
          
        void Execute();
    };

}

#endif

