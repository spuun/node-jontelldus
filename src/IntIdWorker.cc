#include "IntIdWorker.h"
namespace JonTelldus {

  IntIdWorker::IntIdWorker(Nan::Callback *callback, int (*fn_)(int), int id_)
    : Nan::AsyncWorker(callback), fn(fn_), id(id_) {}

  void IntIdWorker::Execute() {
    result = fn(id);
  }

  void IntIdWorker::HandleOKCallback() {
    v8::Handle<v8::Value> argv[] = {
      result.ToObject()
    };
    if (callback) {
      callback->Call(1, argv);
    }
  }

}
