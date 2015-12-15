#ifndef _SendRawCommandWorker_h_
#define _SendRawCommandWorker_h_

#include "JonTelldus.h"
#include "WorkerBase.h"

#include <string>
namespace JonTelldus {
  class SendRawCommandWorker: public WorkerBase
  {
    private:
      std::string rawCommand;
    public:
      SendRawCommandWorker(Nan::Callback *callback, char *rawCommand_);
      void Execute();
  };
}
#endif
