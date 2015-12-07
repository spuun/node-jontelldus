#include "TdResult.h"
#include <telldus-core.h>

namespace JonTelldus {

  TdResult::TdResult() {};
  TdResult::TdResult(int code_){
    this->SetResultCode(code_);
  } 
  void TdResult::SetResultCode(int code_) {
    code = code_;
    char * errStr = tdGetErrorString(code);
    message = std::string(errStr);
    delete errStr;
  }
  
  bool TdResult::IsError() {
    return code != TELLSTICK_SUCCESS;
  }
  v8::Local<v8::Object> TdResult::ToObject() {
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    Set(obj, "code", Nan::New<v8::Number>(code));
    Set(obj, "message", message.c_str());
    return obj;
  }

  TdResult& TdResult::operator=(int code) {
    this->SetResultCode(code);
    return *this;
  }
}
