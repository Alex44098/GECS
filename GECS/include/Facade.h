#pragma once

#include "Platform.h"

namespace GECS {
	class EntityManager;
	class ComponentManager;

	namespace Memory {
		class GlobalMemoryManager;
		extern GlobalMemoryManager* m_globalMemManager; // global manager
	}
}