#ifndef _QueueCallback_h_
#define _QueueCallback_h_

#include "JonTelldus.h"

namespace JonTelldus {

  class CallbackInvoker {
    protected:
      Nan::Callback* callback;
    public:
      CallbackInvoker(Nan::Callback* callback_);
      virtual ~CallbackInvoker() {}
      void Invoke(); 
      virtual void Execute() = 0;
      void Destroy();
      void DestroyFinal();

      uv_async_t request;
  };

  void QueueCallback(CallbackInvoker* invoker);

}
#endif
