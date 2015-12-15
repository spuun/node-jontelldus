#include "RemoveDeviceWorker.h"
#include <telldus-core.h>

namespace JonTelldus {

RemoveDeviceWorker::RemoveDeviceWorker(Nan::Callback *callback, int deviceId_) 
 : WorkerBase(callback), deviceId(deviceId_) {

}
void RemoveDeviceWorker::Execute() {
  if (!tdRemoveDevice(deviceId)) {
    SetErrorMessage("Failed to remove device");
  }
}

}