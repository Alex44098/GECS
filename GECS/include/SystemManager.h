#pragma once

#pragma warning(disable: 4251)

#include "Facade.h"
#include "ISystem.h"

#include "Memory/LinearAllocator.h"

namespace GECS {
	class GECS_API SystemManager {
	private:
		Memory::LinearAllocator* m_allocator;
		std::unordered_map<type_id, ISystem*> m_systemsTable;
		std::vector<type_id> m_systemsOrder;
		std::vector<std::vector<bool>> m_systemDependencies;

	public:

		SystemManager();
		~SystemManager();

		void Update(f32 delta);

		template<class T, class... Arguments>
		T* AddSystem(Arguments&&... args) {
			const type_id systemId = T::SYSTEM_TYPE_ID;

			auto systemWithId = this->m_systemsTable.find(systemId);

			// trying to find a system that has already been added
			if (systemWithId != this->m_systemsTable.end() && systemWithId->second != nullptr)
				return static_cast<T*>(systemWithId->second);

			uptr address = this->m_allocator->Allocate(sizeof(T), alignof(T));

			T* newSystem = new (reinterpret_cast<void*>(address))T(std::forward<Arguments>(args)...);
			newSystem->m_systemManagerSingleton = this;

			this->m_systemsTable[systemId] = newSystem;

			this->m_systemsOrder.push_back(systemId);

			// growing a dependency table
			this->m_systemDependencies.resize(systemId + 1);
			for (int i = 0; i < this->m_systemDependencies.size(); i++) {
				this->m_systemDependencies[i].resize(systemId + 1);
			}

			return newSystem;
		}

		template<class Sys, class Depend>
		void AddSystemDependency(Sys system, Depend dependency)
		{
			const type_id systemId = system->GetSystemTypeId();
			const type_id dependencyId = dependency->GetSystemTypeId();

			this->m_systemDependencies[systemId][dependencyId] = true;
		}

		template<class T>
		void EnableSystem() {
			const type_id systemId = T::SYSTEM_TYPE_ID;

			auto systemWithId = this->m_systemsTable.find(systemId);
			if (systemWithId != this->m_systemsTable.end())
			{
				systemWithId->second->m_enabled = true;
			}
		}


		template<class T>
		void DisableSystem() {
			const type_id systemId = T::SYSTEM_TYPE_ID;

			auto systemWithId = this->m_systemsTable.find(systemId);
			if (systemWithId != this->m_systemsTable.end())
			{
				systemWithId->second->m_enabled = false;
			}
		}

		template<class T>
		void SetSystemPriority(u8 newPriority) {
			const type_id systemId = T::SYSTEM_TYPE_ID;

			auto systemWithId = this->m_systemsTable.find(systemId);
			if (systemWithId != this->m_systemsTable.end())
			{
				systemWithId->second->m_priority = newPriority;
			}
		}

		void RebuildSystemsOrder();

		std::vector<type_id> GetSystemsOrder();
	};
}