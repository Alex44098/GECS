#pragma once

#include "Facade.h"

namespace GECS {
	namespace Event {
		class GECS_API IEvent {
		public:

			IEvent();

			virtual ~IEvent();

			virtual inline const type_id GetEventTypeId() const = 0;
		};
	}
}