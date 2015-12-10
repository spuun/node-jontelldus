#ifndef _DimDeviceWorker_h_
#define _DimDeviceWorker_h_

#include "JonTelldus.h"
#include "WorkerBase.h"

namespace JonTelldus {

  class DimDeviceWorker : public WorkerBase {
    private:
      int deviceId;
      int level;
    public:
      DimDeviceWorker(Nan::Callback*, int, int);
      void Execute();
  };
}

#endif
