#include "ListenerRegister.h"

namespace JonTelldus {
  void ListenerRegister::Register(Nan::Callback *cb, int tdid) {
    this->Register(cb->GetFunction(), tdid);
  }
  int ListenerRegister::UnRegister(Nan::Callback *cb) {
    return this->UnRegister(cb->GetFunction());
  }
  void ListenerRegister::Register(v8::Local<v8::Function> func, int tdid) {
    listeners[func->GetIdentityHash()] = tdid;
  }
  int ListenerRegister::UnRegister(v8::Local<v8::Function> func) {
    std::map<int,int>::iterator it = listeners.find(func->GetIdentityHash());
    if (it == listeners.end()) {
      return 0;
    }
    int tdid = it->second;
    listeners.erase(it);
    return tdid;
  }

}
