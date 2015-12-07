#ifndef _IntIdWorker_h_
#define _IntIdWorker_h_

#include "JonTelldus.h"
#include "TdResult.h"
namespace JonTelldus {
  class IntIdWorker : public Nan::AsyncWorker
  {
    private:
      int (*fn)(int);
      int id;
      TdResult result;
    public:
      IntIdWorker(Nan::Callback *callback, int (*fn_)(int), int id_);
      void Execute();
      void HandleOKCallback();
  };
}
#endif
