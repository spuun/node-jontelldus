#ifndef _IntIdWorker_h_
#define _IntIdWorker_h_

#include "JonTelldus.h"
namespace JonTelldus {
  class IntIdWorker : public Nan::AsyncWorker
  {
    private:
      int (*fn)(int);
      int id;
    public:
      IntIdWorker(Nan::Callback *callback, int (*fn_)(int), int id_);
      void Execute();
  };
}
#endif
