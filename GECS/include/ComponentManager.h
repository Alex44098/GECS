#pragma once

#pragma warning(disable: 4251)

#include "Facade.h"

#include "Handle/Handle.h"
#include "Utilities/TypeIDCounter.h"
#include "Containers/ComponentContainer.h"

namespace GECS{
	class GECS_API ComponentManager {
	private:

		std::unordered_map<type_id, IComponentContainer*> m_componentTypeContainers;
		std::vector<IComponent*> m_componentTableById;

		// Contains components' id. 
		// Access by the index of the entity descriptor (Handle)
		// and the component type ID.
		std::vector<std::vector<object_id>> m_entityComponentsIdByTypes;

		object_id GetNewId(IComponent* component);
		void ReleaseId(object_id id);

		void AttachComponentToEntity(Handle entityHandle, object_id componentId, type_id componentTypeId);
		void DetachComponentToEntity(Handle entityHandle, object_id componentId, type_id componentTypeId);

	public:

		ComponentManager();
		~ComponentManager();

		template<class T, class... Arguments>
		T* AddComponent(const Handle entityHandle, Arguments&&... args) {
			uptr address = GetComponentContainer<T>(m_componentTypeContainers)->CreateObject();
			const object_id componentId = this->GetNewId((T*)address);
			
			// creating an object at a dedicated address
			IComponent* component = new (reinterpret_cast<void*>(address)) T (std::forward<Arguments>(args)...);
			component->m_componentID = componentId;
			component->m_entityOwner = entityHandle;

			AttachComponentToEntity(entityHandle, componentId, T::COMPONENT_TYPE_ID);

			return static_cast<T*>(component);
		}

		template<class T>
		void ReleaseComponent(const Handle entityHandle) {
			const object_id componentId = this->m_entityComponentsIdByTypes[entityHandle.index][T::COMPONENT_TYPE_ID];
			IComponent* component = this->m_componentTableById[componentId];

			GetComponentContainer<T>(m_componentTypeContainers)->ReleaseComponent(component);
			DetachComponentToEntity(entityHandle, componentId, T::COMPONENT_TYPE_ID);
		}

		template<class T>
		T* GetComponent(const Handle entityHandle) {
			const object_id componentId = this->m_entityComponentsIdByTypes[entityHandle.index][T::COMPONENT_TYPE_ID];

			if (componentId == INVALID_OBJECT_ID) {
				return nullptr;
			}

			return static_cast<T*>(this->m_componentTableById[componentId]);
		}

		template<class T>
		inline typename ComponentContainer<T>::iterator begin() {
			return GetComponentContainer<T>(m_componentTypeContainers)->begin();
		}

		template<class T>
		inline typename ComponentContainer<T>::iterator end() {
			return GetComponentContainer<T>(m_componentTypeContainers)->end();
		}

		void ReleaseAllComponents(const Handle entityHandle);
	};
}