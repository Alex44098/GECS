#pragma once

#include "Delegate/IClassMethod.h"

namespace GECS {
	namespace Event {
		class IEventCollection {

		public:

			IEventCollection();

			virtual ~IEventCollection();

			virtual void Call(const IEvent* event) = 0;

			virtual void AddMethod(IClassMethod* method) = 0;

			virtual void RemoveMethod(IClassMethod* method) = 0;
		};
	}
}