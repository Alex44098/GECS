#pragma once
#include "Facade.h"
#include "Handle/Handle.h"

namespace GECS {
	static const object_id INVALID_COMPONENT_ID = INVALID_OBJECT_ID;

	class IComponent {
	
	protected:

		object_id m_componentID;
		Handle m_entityOwner;

	public:

		IComponent();

		virtual ~IComponent();

		inline const object_id GetComponentID() const {
			return this->m_componentID;
		}

		inline const Handle GetEntityOwner() const {
			return this->m_entityOwner;
		}
	};
}