#pragma once

#include "Facade.h"

namespace GECS {
	namespace Event {
		class IEvent {
		public:

			IEvent();

			virtual ~IEvent();

			virtual inline const type_id GetEventTypeId() const = 0;
		};
	}
}