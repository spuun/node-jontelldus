#include "RemoveListenerWorker.h"

namespace JonTelldus {

  RemoveListenerWorker::RemoveListenerWorker(
      Nan::Callback *callback, int id)
  : WorkerBase(callback), listenerId(id) {
  }

  void RemoveListenerWorker::Execute() {
    int result = tdUnregisterCallback(listenerId);

    if (result != TELLSTICK_SUCCESS) {
      char *error = tdGetErrorString(result);
      SetErrorMessage(error);
      tdReleaseString(error);
    }
  }
}
