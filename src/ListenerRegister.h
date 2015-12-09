#ifndef _ListenersRegister_h_
#define _ListenersRegister_h_

#include "JonTelldus.h"
#include "Singleton.h"
#include <map>

namespace JonTelldus {
  enum ListenerType {
    Raw, Sensor, Device
  };

  class ListenerRegister
  {
    private:
      std::map<int, int> listeners;
    public:
      void Register(Nan::Callback*, int);
      void Register(v8::Local<v8::Function>, int);
      int UnRegister(Nan::Callback*);
      int UnRegister(v8::Local<v8::Function>);
  };
}
#endif
