#ifndef _Mutex_h_
#define _Mutex_h_
#include <uv.h>

namespace JonTelldus {

  class Mutex {
    private:
      uv_mutex_t mutex;
    public:
      Mutex();
      void Lock();
      void UnLock();
  };

}
#endif
