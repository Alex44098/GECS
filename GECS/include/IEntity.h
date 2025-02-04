#pragma once

#include "Facade.h"
#include "Handle/Handle.h"

#include "ComponentManager.h"

namespace GECS {
	class GECS_API IEntity {

		friend class EntityManager;
		friend class MemoryStressTest;

	protected:

		Handle m_handle;
		ComponentManager* m_componentManagerSingleton;

	public:

		IEntity();

		virtual ~IEntity();

		inline const Handle GetEntityHandle() {
			return this->m_handle;
		}

		virtual inline const type_id GetEntityTypeId() const = 0;

		template<class T>
		T* GetComponent() const {
			return this->m_componentManagerSingleton->GetComponent<T>(this->m_handle);
		}

		template<class T, class... Arguments>
		T* AddComponent(Arguments&&... args) {
			return this->m_componentManagerSingleton->AddComponent<T>(this->m_handle, std::forward<Arguments>(args)...);
		}

		template<class T>
		void RemoveComponent() {
			this->m_componentManagerSingleton->ReleaseComponent<T>(this->m_handle);
		}
	};
}