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

	inline extern Nan::Maybe<bool> Set(v8::Local<v8::Object> target,
				const char *propertyName,
				int numberValue,
				v8::PropertyAttribute attribs);

	inline extern Nan::Maybe<bool> Set(v8::Local<v8::Object> target,
				const char *propertyName,
				v8::Local<v8::Value> value, 
				v8::PropertyAttribute attribs);
	
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
		const char *stringValue) {
		return Nan::Set(target, 
			Nan::New<v8::String>(propertyName).ToLocalChecked(), 
			Nan::New<v8::String>(stringValue).ToLocalChecked());
	}

	Nan::Maybe<bool> Set(
		v8::Local<v8::Object> target,
		const char *propertyName,
		int numberValue) {
		return Nan::Set(target, 
			Nan::New<v8::String>(propertyName).ToLocalChecked(), 
			Nan::New<v8::Number>(numberValue));
	}

	Nan::Maybe<bool> Set(v8::Local<v8::Object> target,
		const char *propertyName,
		int numberValue,
		v8::PropertyAttribute attribs) {
		return Nan::ForceSet(target,
				Nan::New<v8::String>(propertyName).ToLocalChecked(),
				Nan::New<v8::Number>(numberValue),
				attribs);
	}
	Nan::Maybe<bool> Set(v8::Local<v8::Object> target,
		const char *propertyName,
		v8::Local<v8::Value> value, 
		v8::PropertyAttribute attribs) {
		return Nan::ForceSet(target,
				Nan::New<v8::String>(propertyName).ToLocalChecked(),
				value,
				attribs);
	}
}

#endif
