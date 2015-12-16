#include "RemoveListenerWorker.h"

namespace JonTelldus {

  RemoveListenerWorker::RemoveListenerWorker(
      Nan::Callback *callback, const ListenerInfo& info_)
  : WorkerBase(callback), info(info_) {
  }

  void RemoveListenerWorker::Execute() {
    int result = tdUnregisterCallback(info.tdid);

    if (info.callback != 0) {
      delete info.callback;
    }
    if (result != TELLSTICK_SUCCESS) {
      char *error = tdGetErrorString(result);
      SetErrorMessage(error);
      tdReleaseString(error);
    }
  }
}
