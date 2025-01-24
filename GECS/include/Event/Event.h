#pragma once

#include "IEvent.h"
#include "Utilities/TypeIDCounter.h"

namespace GECS {
	namespace Event {
		template<class T>
		class Event : public IEvent {

		public:

			static const type_id EVENT_TYPE_ID;

			Event() {}

			virtual ~Event() {}

			virtual inline const type_id GetEventTypeId() const override {
				return EVENT_TYPE_ID;
			}
		};

		template <class T>
		const type_id Event<T>::EVENT_TYPE_ID = Identifier::TypeIDCounter<IEvent>::GetTypeId<T>();
	}
}