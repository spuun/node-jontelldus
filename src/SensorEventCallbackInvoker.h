#ifndef _SensorEventCallbackCaller_h_
#define _SensorEventCallbackCaller_h_

#include "JonTelldus.h"
#include "QueueInvoker.h" 

#include <string>

namespace JonTelldus {

  class SensorEventCallbackInvoker
    : public CallbackInvoker {
      private:
        std::string protocol;
        std::string model;
        int id;
        int dataType;
        std::string value;
        int timestamp;
      public:
        SensorEventCallbackInvoker(
          Nan::Callback *callback,
          const char *protocol_,
          const char *model_,
          int id_,
          int dataType_,
          const char *value_,
          int timestamp_); 
        void Execute();
    };

}

#endif

