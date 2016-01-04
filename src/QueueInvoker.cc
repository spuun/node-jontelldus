#include "QueueInvoker.h"

namespace JonTelldus {

  CallbackInvoker::CallbackInvoker(Nan::Callback* callback_) : callback(callback_) {
    request.data = this;
  }
  void CallbackInvoker::Invoke() {
    Nan::HandleScope scope;
    this->Execute();
  }
  void CallbackInvoker::Destroy() {
    uv_close((uv_handle_t*) &request, 0);
    delete this;
  }

  void QueueInvokeNop(uv_async_t *request) {}

  void QueueCallbackInvoke (uv_async_t* req) {
    CallbackInvoker* worker = static_cast<CallbackInvoker*>(req->data);
    worker->Invoke();
    worker->Destroy();
  }

  void QueueCallback(CallbackInvoker* invoker) {
    uv_async_init(uv_default_loop(), &(invoker->request), reinterpret_cast<uv_async_cb>(QueueCallbackInvoke));
    uv_async_send(&(invoker->request));
  }

}

