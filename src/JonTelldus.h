#ifndef _JonTelldus_h_
#define _JonTelldus_h_

#include <node.h>
#include <nan.h>
#include <telldus-core.h>

namespace JonTelldus {

	inline extern Nan::Maybe<bool> Set(
				v8::Local<v8::Array> target,
				unsigned int index,
				v8::Local<v8::Value> value);

	inline extern Nan::Maybe<bool> Set(
				v8::Local<v8::Object> target,
				const char *propertyName,
				v8::Local<v8::Value> value);
	
	inline extern Nan::Maybe<bool> Set(
				v8::Local<v8::Object> target,
				const char *propertyName,
				const char *stringValue);

	inline extern Nan::Maybe<bool> Set(
				v8::Local<v8::Object> target,
				const char *propertyName,
				int numberValue);

	Nan::Maybe<bool> Set(
		v8::Local<v8::Array> target,
		unsigned int index,
		v8::Local<v8::Value> value) {
		return Nan::Set(target, Nan::New<v8::Number>(index), value);
	}

	Nan::Maybe<bool> Set(
		v8::Local<v8::Object> target,
		const char *propertyName,
		v8::Local<v8::Value> value) {
		return Nan::Set(target, 
			Nan::New<v8::String>(propertyName).ToLocalChecked(),
			value);
	}

	Nan::Maybe<bool> Set(
		v8::Local<v8::Object> target,
		const char *propertyName,
		int numberValue) {
		return Nan::Set(target, 
			Nan::New<v8::String>(propertyName).ToLocalChecked(), 
			Nan::New<v8::Number>(numberValue));
	}

	Nan::Maybe<bool> Set(
		v8::Local<v8::Object> target,
		const char *propertyName,
		const char *stringValue) {
		return Nan::Set(target, 
			Nan::New<v8::String>(propertyName).ToLocalChecked(), 
			Nan::New<v8::String>(stringValue).ToLocalChecked());
	}

}

#endif
