#pragma once

#include "API.h"
#include "Handle/Handle.h"

namespace GECS {
	class IEntity {
		Handle m_handle;
		
		ComponentManager* mp_ComponentManager;

		IEntity() {}

		virtual ~IEntity();

		inline const Handle GetEntityHandle() {
			return this->m_handle;
		}

		virtual inline const type_id GetEntityTypeId() const = 0;
	};
}