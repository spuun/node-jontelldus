#ifndef _AddDeviceWorker_h_
#define _AddDeviceWorker_h_

#include "JonTelldus.h"

#include <string>
#include <map>

namespace JonTelldus {

class AddDeviceWorker : public Nan::AsyncWorker {
  private:
    std::string name;
    std::string protocol;
    std::string model;
    int deviceId;
    std::map<std::string, std::string> parameters;
  public:
    AddDeviceWorker(
      Nan::Callback *callback, 
      const char *name_,
      const char *protocol_,
      const char *model_,
      const std::map<std::string, std::string>& parameters_);

    void Execute();
    void HandleOKCallback();

    static AddDeviceWorker * CreateFromArguments(Nan::NAN_METHOD_ARGS_TYPE info);
};

}
#endif