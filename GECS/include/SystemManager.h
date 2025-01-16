#pragma once

#include "Facade.h"
#include "ISystem.h"

#include "Memory/LinearAllocator.h"

namespace GECS {
	class SystemManager {
	private:
		Memory::LinearAllocator m_allocator;
		std::unordered_map<u64, ISystem*> m_systemsTable;

	};
}