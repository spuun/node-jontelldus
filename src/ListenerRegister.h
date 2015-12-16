#ifndef _ListenersRegister_h_
#define _ListenersRegister_h_

#include "JonTelldus.h"
#include "Singleton.h"
#include "ListenerInfo.h"
#include <map>

namespace JonTelldus {
  enum ListenerType {
    Raw, Sensor, Device
  };

  class ListenerRegister
  {
    private:
      std::map<int, ListenerInfo> listeners;
    public:
      void Register(Nan::Callback*, const ListenerInfo&);
      void Register(v8::Local<v8::Function>, const ListenerInfo&);
      ListenerInfo UnRegister(Nan::Callback*);
      ListenerInfo UnRegister(v8::Local<v8::Function>);
  };
}
#endif
