#include "EntityManager.h"

namespace GECS {
	EntityManager::EntityManager(ComponentManager* componentManagerSingleton) :
		m_releasedEntities(1024),
		m_numReleasedEntities(0),
		m_componentManagerSingleton(componentManagerSingleton)
	{
		L_(ldebug) << "Entity manager has been initialized";
	}

	EntityManager::~EntityManager() {
		L_(ldebug) << "Start of the entity manager's destruction";
		for (auto container : this->m_entityTypeContainers) {
			delete container.second;
		}
		L_(ldebug) << "Entity manager has been destroyed";
	}

	void EntityManager::ReleaseEntity(Handle handle) {
		if (this->m_numReleasedEntities < this->m_releasedEntities.size()) {
			this->m_releasedEntities[this->m_numReleasedEntities++] = handle;
		}
		else {
			this->m_releasedEntities.push_back(handle);
			this->m_numReleasedEntities++;
		}

		L_(ldebug) << "Released an entity with index" << handle.index;
	}

	Handle EntityManager::GetNewHandle(IEntity* entity) {
		return this->m_entityHandleTable.GetHandle(entity);
	}

	void EntityManager::ReleaseHandle(Handle handle) {
		this->m_entityHandleTable.ReleaseHandle(handle);
	}

	void EntityManager::DestroyReleasedEntities() {
		for (size_t i = 0; i < this->m_numReleasedEntities; i++) {
			Handle entityHandle = this->m_releasedEntities[i];
			IEntity* entity = this->m_entityHandleTable[entityHandle];

			type_id entityTypeId = entity->GetEntityTypeId();
			auto container = this->m_entityTypeContainers.find(entityTypeId);
			if (container != this->m_entityTypeContainers.end()) {
				container->second->ReleaseEntity(entity);
			}

			this->ReleaseHandle(entityHandle);
		}

		this->m_numReleasedEntities = 0;
	}
}