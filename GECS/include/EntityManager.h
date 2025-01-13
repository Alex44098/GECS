#pragma once

#include "Facade.h"

#include "Containers/EntityContainer.h"
#include "Memory/ChunkAllocator.h"
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
			uptr address = GetEntityContainer<T>()->CreateObject();

			Handle entityHandle = this->GetNewHandle((T*)address);
			((T*)address)->m_handle = entityHandle;

			// creating an object at a dedicated address
			IEntity* entity = new (address)T(std::forward<Arguments>(args)...);
			return entityHandle;
		}

		inline IEntity* GetEntity(Handle handle) {
			return this->m_entityHandleTable[handle];
		}

		inline Handle GetEntityHandle(Handle::value_type index) {
			return this->m_entityHandleTable[index];
		}

		void ReleaseEntity(Handle handle);

		void DestroyReleasedEntities();
	};
}