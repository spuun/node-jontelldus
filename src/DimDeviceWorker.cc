#include "DimDeviceWorker.h"

#include <telldus-core.h>

namespace JonTelldus {

  DimDeviceWorker::DimDeviceWorker(Nan::Callback* callback, int deviceId_, int level_)
    : WorkerBase(callback), deviceId(deviceId_), level(level_) {}

  void DimDeviceWorker::Execute() {
    unsigned char dimLevel = level > 255 ? 255 : ((level < 0) ? 0 : level);
    int ret = tdDim(deviceId, dimLevel);
    if (ret != TELLSTICK_SUCCESS) {
      char *error = tdGetErrorString(ret);
      SetErrorMessage(error);
      tdReleaseString(error);
    }
  }

}
