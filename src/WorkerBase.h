#ifndef _Worker_h_
#define _Worker_h_

#include "JonTelldus.h"

namespace JonTelldus {
	class WorkerBase : public Nan::AsyncWorker {
		public:
      WorkerBase(Nan::Callback *callback);
			virtual void HandleOKCallback();
	};
}

#endif