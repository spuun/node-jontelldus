#include "QueueInvoker.h"

#include <functional>

namespace JonTelldus {

  void CallbackDestroyFinal (uv_handle_t* req);

  CallbackInvoker::CallbackInvoker(Nan::Callback* callback_) : callback(callback_) {
    request.data = this;
  }
  void CallbackInvoker::Invoke() {
    Nan::HandleScope scope;
    this->Execute();
  }
  void CallbackInvoker::Destroy() {
    uv_close((uv_handle_t*) &request, reinterpret_cast<uv_close_cb>(CallbackDestroyFinal));
      //std::bind1st(std::mem_fun(&CallbackInvoker::DestroyFinal), this))
  }

  void CallbackInvoker::DestroyFinal() {
    delete this;
    // DeviceEventBaton *baton = static_cast<DeviceEventBaton *>(handle->data);

    // delete baton;
    // delete handle;
  }

  void QueueInvokeNop(uv_async_t *request) {}

  void CallbackDestroyFinal (uv_handle_t* req) {
    CallbackInvoker* worker = static_cast<CallbackInvoker*>(req->data);
    worker->DestroyFinal();
  }

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

