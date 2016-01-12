#include "IntIdWorker.h"
namespace JonTelldus {

  IntIdWorker::IntIdWorker(Nan::Callback *callback, int (*fn_)(int), int id_)
    : WorkerBase(callback), fn(fn_), id(id_) {}

  void IntIdWorker::Execute() {
    mutex.Lock();
    int result = fn(id);
    if (result == TELLSTICK_SUCCESS) {
      mutex.UnLock();
      return;
    }
    char * error = tdGetErrorString(result);
    this->SetErrorMessage(error);
    tdReleaseString(error);
    mutex.UnLock();
  }
}
