#pragma once

#include "Facade.h"
#include "Memory/ChunkAllocator.h"
#include "IComponent.h"

namespace GECS {
	class ChunkAllocator;

	class IComponentContainer {
	public:
		virtual ~IComponentContainer()
		{}

		virtual void ReleaseComponent(IComponent* component) = 0;
	};

	template<class T>
	class ComponentContainer : public Memory::ChunkAllocator<T, COMPONENT_CONTAINER_CHUNK_MAX_OBJECTS>, public IComponentContainer {
	public:
		ComponentContainer() : ChunkAllocator()
		{}

		virtual ~ComponentContainer()
		{}

		virtual void ReleaseComponent(IComponent* component) override {
			component->~IComponent();
			this->ReleaseObject(reinterpret_cast<uptr>(component));
		}
	};

	template<class T>
	inline ComponentContainer<T>* GetComponentContainer(std::unordered_map<type_id, IComponentContainer*>& componentTypeContainers) {
		type_id componentTypeID = T::COMPONENT_TYPE_ID;
		auto container = componentTypeContainers.find(componentTypeID);
		ComponentContainer<T>* newContainer = nullptr;

		if (container == componentTypeContainers.end()) {
			newContainer = new ComponentContainer<T>();
			componentTypeContainers[componentTypeID] = newContainer;
		}
		else
			newContainer = static_cast<ComponentContainer<T>*>(container->second);

		assert(newContainer != nullptr && "Component container: failed to create new type container!");
		return newContainer;
	}

}