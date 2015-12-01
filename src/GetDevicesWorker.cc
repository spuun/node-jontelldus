#include "GetDevicesWorker.h"

#include <telldus-core.h>

GetDevicesWorker::GetDevicesWorker(Nan::Callback *callback)
	: Nan::AsyncWorker(callback) {};

void GetDevicesWorker::Execute() {
    for (int i = 0; i < tdGetNumberOfDevices(); i++)
    {
    	Device * device = new Device();
    	device->id = tdGetDeviceId(i);

    	char *name = tdGetName(device->id);
    	char *protocol = tdGetProtocol(device->id);
    	char *model = tdGetModel(device->id);

    	device->name = name;
    	device->protocol = protocol;
    	device->model = model;

    	tdReleaseString(name);
    	tdReleaseString(protocol);
    	tdReleaseString(model);

    	_devices.push_back(device);
    }
}

void GetDevicesWorker::HandleOKCallback() {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>();

    std::list<Device*>::iterator it;
    int i = 0;
    for (it = _devices.begin(); it != _devices.end(); ++it) {
    	v8::Local<v8::Object> deviceObj = Nan::New<v8::Object>();
    	Nan::Set(deviceObj, Nan::New<v8::String>("id").ToLocalChecked(),
    		Nan::New<v8::Number>((*it)->id));
    	Nan::Set(deviceObj, Nan::New<v8::String>("name").ToLocalChecked(),
    		Nan::New<v8::String>((*it)->name).ToLocalChecked());
    	Nan::Set(deviceObj, Nan::New<v8::String>("protocol").ToLocalChecked(),
    		Nan::New<v8::String>((*it)->protocol).ToLocalChecked());
    	Nan::Set(deviceObj, Nan::New<v8::String>("model").ToLocalChecked(),
    		Nan::New<v8::String>((*it)->model).ToLocalChecked());
    	Nan::Set(ret, i++, deviceObj);
    	delete *it;
    }
    v8::Handle<v8::Value> argv[] = {
      ret
    };
    callback->Call(1, argv);
}