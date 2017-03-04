#include "Mutex.h"
namespace JonTelldus {
  Mutex::Mutex() {
    uv_mutex_init(&mutex);
  }
  void Mutex::Lock() {
    uv_mutex_lock(&mutex);
  };
  void Mutex::UnLock() {
    uv_mutex_unlock(&mutex);
  };
}
