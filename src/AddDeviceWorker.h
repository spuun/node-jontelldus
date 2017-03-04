#ifndef _AddDeviceWorker_h_
#define _AddDeviceWorker_h_

#include "JonTelldus.h"
#include "UpdateDeviceWorker.h"
#include "Device.h"

#include <string>
#include <map>

namespace JonTelldus {

class AddDeviceWorker : public UpdateDeviceWorker {
  public:
    AddDeviceWorker(Nan::Callback *callback, const Device& device);
      
    void Execute();

    static AddDeviceWorker * CreateFromArguments(Nan::NAN_METHOD_ARGS_TYPE info);
};

}
#endif
