#ifndef _RemoveListenerWorker_h_
#define _RemoveListenerWorker_h_

#include "JonTelldus.h"
#include "WorkerBase.h"

namespace JonTelldus {

  class RemoveListenerWorker : public WorkerBase {
    private:
      int listenerId;
    public:
      RemoveListenerWorker(Nan::Callback *callback, int listenerId);
      void Execute();
  };

}

#endif
