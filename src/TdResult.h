#ifndef _TdResult_h_
#define _TdResult_h_

#include "JonTelldus.h"
#include <string>

namespace JonTelldus
{
  class TdResult
  {
    private:
      int code;
      std::string message;
    public:
      TdResult();
      TdResult(int code);
      void SetResultCode(int code);
      bool IsError();
      v8::Local<v8::Object> ToObject();

      TdResult& operator=(int code);
  };
}
#endif
