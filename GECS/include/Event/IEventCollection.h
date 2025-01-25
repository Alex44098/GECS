#pragma once

#include "Delegate/IClassMethod.h"

namespace GECS {
	namespace Event {
		class IEventCollection {

		public:

			IEventCollection();

			~IEventCollection();

			virtual void Call(const IEvent* event) = 0;

			virtual void AddMethod(const IClassMethod* method) = 0;

			virtual void RemoveMethod(IClassMethod* method) = 0;
		};
	}
}