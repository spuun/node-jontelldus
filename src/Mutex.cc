#include "Mutex.h"
namespace JonTelldus {
  void Mutex::Lock() {
    uv_mutex_lock(&mutex);
  };
  void Mutex::UnLock() {
    uv_mutex_unlock(&mutex);
  };
}