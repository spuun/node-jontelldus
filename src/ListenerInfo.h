#ifndef _ListenerInfo_h_
#define _ListenerInfo_h_

#include "JonTelldus.h"

namespace JonTelldus {

  class ListenerInfo {
    public:
      ListenerInfo() {}
      ListenerInfo(int tdid_, Nan::Callback* callback_) : tdid(tdid_), callback(callback_) {}
      int tdid;
      Nan::Callback* callback;
  };

}

#endif
