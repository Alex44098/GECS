#pragma once

#pragma warning(disable: 4251)

#include "Facade.h"

#include "Containers/EntityContainer.h"
#include "Handle/HandleManager.h"

namespace GECS {
	class GECS_API EntityManager {

	private:
		std::unordered_map<type_id, IEntityContainer*> m_entityTypeContainers;
		Identifier::HandleManager<IEntity, Handle> m_entityHandleTable;

		std::vector<Handle> m_releasedEntities;
		size_t m_numReleasedEntities;

		// ComponentManager singleton for entities
		ComponentManager* m_componentManagerSingleton;

		Handle GetNewHandle(IEntity* entity);
		void ReleaseHandle(Handle handle);

	public:
		EntityManager(ComponentManager* componentManagerSingleton);
		~EntityManager();

		// using a variadic template to pass arguments to an entity
		template<class T, class... Arguments>
		Handle CreateEntity(Arguments&&... args) {
			uptr address = GetEntityContainer<T>(m_entityTypeContainers)->CreateObject();
			const Handle entityHandle = this->GetNewHandle((T*)address);

			// IMPORTANT TO FILL FIELDS BEFORE CREATING AN OBJECT
			// because components is created in entity constructor and
			// it needs an entity handle
			((T*)address)->m_handle = entityHandle;
			((T*)address)->m_componentManagerSingleton = m_componentManagerSingleton;

			// creating an object at a dedicated address
			IEntity* entity = new (reinterpret_cast<void*>(address)) T (std::forward<Arguments>(args)...);

			return entityHandle;
		}

		inline IEntity* GetEntity(Handle handle) {
			return this->m_entityHandleTable[handle];
		}

		inline Handle GetEntityHandle(Handle::value_type index) const {
			return this->m_entityHandleTable[index];
		}

		template<class T>
		inline typename EntityContainer<T>::iterator begin() {
			return GetEntityContainer<T>(m_entityTypeContainers)->begin();
		}

		template<class T>
		inline typename EntityContainer<T>::iterator end() {
			return GetEntityContainer<T>(m_entityTypeContainers)->end();
		}

		void ReleaseEntity(Handle handle);

		void DestroyReleasedEntities();
	};
}