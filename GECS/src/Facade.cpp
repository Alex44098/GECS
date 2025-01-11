#include "Facade.h"

#include "Memory/GlobalMemoryManager.h"

namespace GECS {
	namespace Memory {
		GlobalMemoryManager* m_globalMemManager = new GlobalMemoryManager();
	}
}