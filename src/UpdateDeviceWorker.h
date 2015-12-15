#ifndef _UpdateDeviceWorker_h_
#define _UpdateDeviceWorker_h_

#include "JonTelldus.h"
#include "WorkerBase.h"
#include "Device.h"

#include <string>
#include <map>

namespace JonTelldus {

class UpdateDeviceWorker : public WorkerBase {
  protected:
    Device device;
  public:
    UpdateDeviceWorker(
      Nan::Callback *callback, 
      const Device &device);
    void Execute();
    void HandleOKCallback();

    static UpdateDeviceWorker * CreateFromArguments(Nan::NAN_METHOD_ARGS_TYPE info);
};

}
#endif
