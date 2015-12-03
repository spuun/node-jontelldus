#include "SendRawCommandWorker.h"
#include <telldus-core.h>
namespace JonTelldus {

  SendRawCommandWorker::SendRawCommandWorker(Nan::Callback *callback, char* rawCommand_)
    : Nan::AsyncWorker(callback), rawCommand(rawCommand_) {}

  void SendRawCommandWorker::Execute() {
    ret = tdSendRawCommand(rawCommand.c_str(), 0);
  }

  void SendRawCommandWorker::HandleOKCallback() {
    v8::Handle<v8::Value> argv[] = {
      Nan::New<v8::Number>(ret)
    };
    if (callback)
      callback->Call(1, argv);
  }

}
