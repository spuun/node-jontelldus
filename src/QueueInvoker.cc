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
    delete this;
  }

  void QueueInvokeNop(uv_work_t *request) {}

  void QueueCallbackInvoke (uv_work_t* req, int status) {
    CallbackInvoker* worker = static_cast<CallbackInvoker*>(req->data);
    worker->Invoke();
    worker->Destroy();
  }

  void QueueCallback(CallbackInvoker* invoker) {
    uv_queue_work(
        uv_default_loop(),
        &(invoker->request),
        QueueInvokeNop,
        reinterpret_cast<uv_after_work_cb>(QueueCallbackInvoke)
        );
  }

}

