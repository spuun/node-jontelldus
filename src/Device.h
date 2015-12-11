#ifndef _Device_h_
#define _Device_h_

#include "JonTelldus.h"

#include <string>
#include <map>
#include <vector>

namespace JonTelldus {

  class Device 
  {
    public:
      int id;
      std::string name;
      std::string model;
      std::string protocol;
      std::map<std::string, std::string> parameters;
      jstrarray methods;
     
      static Device CreateFromObject(v8::Local<v8::Object> object);
      static void UpdateDevice(const Device& device);
  };

}

#endif
