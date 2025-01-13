#pragma once

#include "IEntity.h"
#include "Memory/ChunkAllocator.h"
#include "Facade.h"

namespace GECS {
	class IEntityContainer {
	public:
		virtual ~IEntityContainer()
		{}

		virtual void ReleaseEntity(IEntity* entity) = 0;
	};

	template<class T>
	class EntityContainer : public Memory::ChunkAllocator<T>, public IEntityContainer {
	public:
		EntityContainer() : ChunkAllocator(ENTITY_CONTAINER_CHUNK_MAX_OBJECTS)
		{}

		virtual ~EntityContainer()
		{}

		virtual void ReleaseEntity(IEntity* entity) override {
			entity->~IEntity();
			this->ReleaseObject(entity);
		}
	};

	template<class T>
	inline EntityContainer<T>* GetEntityContainer(std::unordered_map<type_id, IEntityContainer*> entityTypeContainers) {
		type_id entityTypeID = T::ENTITY_TYPE_ID;
		auto container = entityTypeContainers.find(entityTypeID);
		EntityContainer<T>* newContainer = nullptr;

		if (container == entityTypeContainers.end()) {
			newContainer = new EntityContainer<T>();
			entityTypeContainers[entityTypeID] = newContainer;
		}
		else
			newContainer = (EntityContainer<T>*)container->second;

		assert(newContainer != nullptr && "Entity container: failed to create new type container!");
		return newContainer;
	}
}