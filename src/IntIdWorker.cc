#include "IntIdWorker.h"
namespace JonTelldus {

  IntIdWorker::IntIdWorker(Nan::Callback *callback, int (*fn_)(int), int id_)
    : Nan::AsyncWorker(callback), fn(fn_), id(id_) {}

  void IntIdWorker::Execute() {
    int result = fn(id);
    if (result == TELLSTICK_SUCCESS) {
      return;
    }
    char * error = tdGetErrorString(result);
    this->SetErrorMessage(error);
    tdReleaseString(error);
  }
}
