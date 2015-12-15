#ifndef _RemoveDeviceWorker_h_
#define _RemoveDeviceWorker_h_

#include "JonTelldus.h"
#include "WorkerBase.h"

namespace JonTelldus {

class RemoveDeviceWorker : public WorkerBase {
  private:
    int deviceId;
  public:
    RemoveDeviceWorker(Nan::Callback *callback, int deviceId);
    void Execute();
};

}

#endif