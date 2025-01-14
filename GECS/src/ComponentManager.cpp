#include "ComponentManager.h"

namespace GECS {
	ComponentManager::ComponentManager() {
		static const size_t numComponents = Identifier::TypeIDCounter<IComponent>::GetNumTypes();

		this->m_entityComponentsIdByTypes.resize(ENTITY_COMPONENT_TABLE_GROW_SIZE);
		for (size_t i = 0; i < ENTITY_COMPONENT_TABLE_GROW_SIZE; i++) {
			this->m_entityComponentsIdByTypes[i].resize(numComponents, INVALID_OBJECT_ID);
		}
	}

	ComponentManager::~ComponentManager() {
		for (auto container : this->m_componentTypeContainers) {
			delete container.second;
		}
	}

	object_id ComponentManager::GetNewId(IComponent* component) {
		object_id i = 0;
		for (; i < this->m_componentTableById.size(); i++) {
			if (this->m_componentTableById[i] == nullptr) {
				this->m_componentTableById[i] = component;
				return i;
			}
		}

		this->m_componentTableById.resize(this->m_componentTableById.size() + COMPONENT_TABLE_GROW_SIZE, nullptr);
		this->m_componentTableById[i] = component;
		return i;
	}

	void ComponentManager::ReleaseId(object_id id) {
		this->m_componentTableById[id] = nullptr;
	}

	void ComponentManager::AttachComponentToEntity(Handle entityHandle, object_id componentId, type_id componentTypeId) {
		if ((this->m_entityComponentsIdByTypes.size() - 1) < entityHandle.index) {

			// grow entity-component table for new entity
			static const size_t numComponents = Identifier::TypeIDCounter<IComponent>::GetNumTypes();
			size_t i = this->m_entityComponentsIdByTypes.size();
			size_t newSize = i + ENTITY_COMPONENT_TABLE_GROW_SIZE;

			for (; i < newSize; i++) {
				this->m_entityComponentsIdByTypes[i].resize(numComponents, INVALID_OBJECT_ID);
			}
		}

		this->m_entityComponentsIdByTypes[entityHandle.index][componentTypeId] = componentId;
	}

	void ComponentManager::DetachComponentToEntity(Handle entityHandle, object_id componentId, type_id componentTypeId) {
		this->m_entityComponentsIdByTypes[entityHandle.index][componentTypeId] = INVALID_OBJECT_ID;

		this->ReleaseId(componentId);
	}

	void ComponentManager::ReleaseAllComponents(const Handle entityHandle) {
		static const size_t numComponents = Identifier::TypeIDCounter<IComponent>::GetNumTypes();

		for (type_id typeId = 0; typeId < numComponents; typeId++) {
			const object_id componentId = this->m_entityComponentsIdByTypes[entityHandle.index][typeId];
			if (componentId == INVALID_TYPE_ID)
				continue;

			IComponent* component = this->m_componentTableById[componentId];
			if (component != nullptr) {
				auto container = this->m_componentTypeContainers.find(typeId);
				if (container != this->m_componentTypeContainers.end()) {
					container->second->ReleaseComponent(component);
				}

				DetachComponentToEntity(entityHandle, componentId, typeId);
			}
		}
	}
}