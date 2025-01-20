#pragma once

#include "Facade.h"
#include "Handle/Handle.h"

namespace GECS {
	class IEntity {

	protected:

		Handle m_handle;
		ComponentManager* mp_componentManager;

	public:

		IEntity();

		virtual ~IEntity();

		inline const Handle GetEntityHandle() {
			return this->m_handle;
		}

		inline void SetEntityHandle(Handle handle) {
			this->m_handle = handle;
		}

		virtual inline const type_id GetEntityTypeId() const = 0;
	};
}