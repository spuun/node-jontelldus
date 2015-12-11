#ifndef _GetDevicesWorker_h_
#define _GetDevicesWorker_h_

#include <node.h>
#include <nan.h>
#include <list>
#include <map>
#include <string>
#include "JonTelldus.h"
#include "Device.h"

namespace JonTelldus {

  class GetDevicesWorker : public Nan::AsyncWorker {
    private:		
      std::vector<Device*> _devices;
    public:
      GetDevicesWorker(Nan::Callback *callback);
      void Execute();
      void HandleOKCallback();
  };

}
#endif
