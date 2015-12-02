#include "IntIdWorker.h"
namespace JonTelldus {

  IntIdWorker::IntIdWorker(Nan::Callback *callback, int (*fn_)(int), int id_)
    : Nan::AsyncWorker(callback), fn(fn_), id(id_) {}

  void IntIdWorker::Execute() {
    printf("Execute\n");
    ret = fn(id);
    printf("/Execute %d\n", ret);
  }

  void IntIdWorker::HandleOKCallback() {
    v8::Handle<v8::Value> argv[] = {
      Nan::New<v8::Number>(ret)
    };
    callback->Call(1, argv);
  }

}
