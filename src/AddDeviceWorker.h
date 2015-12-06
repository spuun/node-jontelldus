#ifndef _AddDeviceWorker_h_
#define _AddDeviceWorker_h_

#include "JonTelldus.h"

#include <string>

class AddDeviceWorker : public Nan::AsyncWorker {
  private:
    std::string name;
    std::string protocol;
    std::string model;
    int deviceId;
  public:
    AddDeviceWorker(
      Nan::Callback *callback, 
      const char *name_,
      const char *protocol_,
      const char *model_);

    void Execute();
    void HandleOKCallback();
};

#endif