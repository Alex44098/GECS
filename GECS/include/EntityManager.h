#pragma once

#include "Facade.h"

#include "Containers/EntityContainer.h"
#include "Handle/HandleManager.h"

namespace GECS {
	class EntityManager {

	private:
		std::unordered_map<type_id, IEntityContainer*> m_entityTypeContainers;
		Identifier::HandleManager<IEntity, Handle> m_entityHandleTable;

		std::vector<Handle> m_releasedEntities;
		size_t m_numReleasedEntities;

		Handle GetNewHandle(IEntity* entity);
		void ReleaseHandle(Handle handle);

	public:
		EntityManager();
		~EntityManager();

		// using a variadic template to pass arguments to an entity
		template<class T, class... Arguments>
		Handle CreateEntity(Arguments&&... args) {
			uptr address = GetEntityContainer<T>(m_entityTypeContainers)->CreateObject();
			const Handle entityHandle = this->GetNewHandle((T*)address);

			// creating an object at a dedicated address
			IEntity* entity = new (reinterpret_cast<void*>(address))T(std::forward<Arguments>(args)...);
			entity->SetEntityHandle(entityHandle);

			return entityHandle;
		}

		inline IEntity* GetEntity(Handle handle) {
			return this->m_entityHandleTable[handle];
		}

		inline Handle GetEntityHandle(Handle::value_type index) const {
			return this->m_entityHandleTable[index];
		}

		void ReleaseEntity(Handle handle);

		void DestroyReleasedEntities();
	};
}