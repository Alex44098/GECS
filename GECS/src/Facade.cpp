#include "Facade.h"

#include "Memory/GlobalMemoryManager.h"
#include "GECSMain.h"

namespace GECS {
	namespace Memory {
		GlobalMemoryManager* g_globalMemManager = new GlobalMemoryManager();
	}

	GECSMain* GECSInstance = nullptr;

	void Init() {
		if (GECSInstance == nullptr)
			GECSInstance = new GECSMain();
	}

	void Destroy() {
		if (GECSInstance != nullptr)
			delete GECSInstance;
	}
}