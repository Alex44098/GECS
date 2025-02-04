#pragma once

#pragma warning(disable: 4251)

#include "Facade.h"
#include "Handle/Handle.h"

namespace GECS {
	static const object_id INVALID_COMPONENT_ID = INVALID_OBJECT_ID;

	class GECS_API IComponent {

		friend class ComponentManager;
	
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