#ifndef _SendRawCommandWorker_h_
#define _SendRawCommandWorker_h_

#include "JonTelldus.h"
#include <string>
namespace JonTelldus {
  class SendRawCommandWorker: public Nan::AsyncWorker
  {
    private:
      std::string rawCommand;
      int ret;
    public:
      SendRawCommandWorker(Nan::Callback *callback, char *rawCommand_);
      void Execute();
      void HandleOKCallback();
  };
}
#endif
