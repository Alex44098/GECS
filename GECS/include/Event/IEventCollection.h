#pragma once

#include "Delegate/Delegate.h"

namespace GECS {
	namespace Event {
		class IEventCollection {

		public:

			IEventCollection();

			~IEventCollection();

			virtual void Call(const IEvent* event) = 0;

			virtual void AddDelegate(const Delegate* delegate) = 0;

			virtual void RemoveDelegate(Delegate* delegate) = 0;
		};
	}
}