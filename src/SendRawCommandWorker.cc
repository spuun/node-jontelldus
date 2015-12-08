#include "SendRawCommandWorker.h"
#include <telldus-core.h>
namespace JonTelldus {

  SendRawCommandWorker::SendRawCommandWorker(Nan::Callback *callback, char* rawCommand_)
    : Nan::AsyncWorker(callback), rawCommand(rawCommand_) {}

  void SendRawCommandWorker::Execute() {
    int result = tdSendRawCommand(rawCommand.c_str(), 0);
    if (result == TELLSTICK_SUCCESS) {
      return;
    }
    char * error = tdGetErrorString(result);
    this->SetErrorMessage(error);
    tdReleaseString(error);
  }
}
