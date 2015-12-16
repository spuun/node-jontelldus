#include "ListenerRegister.h"

namespace JonTelldus {
  void ListenerRegister::Register(Nan::Callback *cb, const ListenerInfo& info) {
    this->Register(cb->GetFunction(), info);
  }
  ListenerInfo ListenerRegister::UnRegister(Nan::Callback *cb) {
    return this->UnRegister(cb->GetFunction());
  }
  void ListenerRegister::Register(v8::Local<v8::Function> func, const ListenerInfo& info) {
    listeners[func->GetIdentityHash()] = info;
  }
  ListenerInfo ListenerRegister::UnRegister(v8::Local<v8::Function> func) {
    std::map<int,ListenerInfo>::iterator it = listeners.find(func->GetIdentityHash());
    if (it == listeners.end()) {
      return ListenerInfo();
    }
    ListenerInfo info = it->second;
    listeners.erase(it);
    return info;
  }
}
