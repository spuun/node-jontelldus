#ifndef _GetDevicesWorker_h_
#define _GetDevicesWorker_h_

#include <node.h>
#include <nan.h>
#include <list>
#include <string>
struct Device {
	int id;
	std::string name;
	std::string protocol;
	std::string model;
};

class GetDevicesWorker : public Nan::AsyncWorker {
	private:		
		std::list<Device*> _devices;
	public:
		GetDevicesWorker(Nan::Callback *callback);
		void Execute();
		void HandleOKCallback();
};

#endif