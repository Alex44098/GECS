#include "SystemManager.h"
#include "Memory/GlobalMemoryManager.h"
#include "Utilities/SystemOrderBuilder.h"

namespace GECS {
	SystemManager::SystemManager() {
		this->m_allocator = new Memory::LinearAllocator(GECS_SYSTEM_MANAGER_MEMORY_CAPACITY, Memory::g_globalMemManager->Allocate(GECS_SYSTEM_MANAGER_MEMORY_CAPACITY));
		L_(ldebug) << "System manager has been initialized";
	}

	SystemManager::~SystemManager() {
		L_(ldebug) << "Start of the system manager's destruction";
		for (auto it = this->m_systemsTable.begin(); it != m_systemsTable.end(); it++) {
			it->second->~ISystem();
		}

		Memory::g_globalMemManager->Free(this->m_allocator->GetAddressBegining());
		delete this->m_allocator;
		this->m_allocator = nullptr;
		L_(ldebug) << "System manager has been destroyed";
	}

	void SystemManager::Update(f32 delta) {
		for (type_id systemId : this->m_systemsOrder) {
			ISystem* system = this->m_systemsTable[systemId];
			
			system->m_timeSinceLastUpdate += delta;
			bool isExpired = system->IsExpired();

			if (system->m_enabled && isExpired) {
				system->Update(delta);
				system->ResetTimeSinceUpdate();
			}
		}
	}

	void SystemManager::RebuildSystemsOrder() {
		Util::BuildSystemOrder(this->m_systemsOrder, this->m_systemsTable, this->m_systemDependencies);
		
		L_(ldebug) << "Systems order";
		#ifndef NDEBUG
			for (type_id i : this->m_systemsOrder) {
				L_(ldebug) << i;
			}
		#endif
	}

	std::vector<type_id> SystemManager::GetSystemsOrder() {
		return this->m_systemsOrder;
	}
}