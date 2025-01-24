#pragma once

#include "IComponent.h"

namespace GECS {

	template<class T>
	class Component : public IComponent {

	public:

		static const type_id COMPONENT_TYPE_ID;

		// Component manager responsible for deleting
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;

		Component() {}

		virtual ~Component() {}

		inline type_id GetComponentTypeId() const
		{
			return COMPONENT_TYPE_ID;
		}
	};

	template<class T>
	const type_id Component<T>::COMPONENT_TYPE_ID = Identifier::TypeIDCounter<IComponent>::GetTypeId<T>();
}