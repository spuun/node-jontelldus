#include "WorkerBase.h"

namespace JonTelldus {

WorkerBase::WorkerBase(Nan::Callback *callback) 
  : Nan::AsyncWorker(callback) {}

void WorkerBase::HandleOKCallback() {
  if (callback != 0) {
    callback->Call(0, NULL);
  }
}

}