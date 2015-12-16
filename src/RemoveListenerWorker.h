#ifndef _RemoveListenerWorker_h_
#define _RemoveListenerWorker_h_

#include "JonTelldus.h"
#include "WorkerBase.h"
#include "ListenerInfo.h"

namespace JonTelldus {

  class RemoveListenerWorker : public WorkerBase {
    private:
      ListenerInfo info;
    public:
      RemoveListenerWorker(Nan::Callback *callback, const ListenerInfo& info);
      void Execute();
  };

}

#endif
