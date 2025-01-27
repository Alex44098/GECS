#include "Facade.h"

#include "Memory/GlobalMemoryManager.h"
#include "Event/EventQueue.h"

namespace GECS {
	namespace Memory {
		GlobalMemoryManager* g_globalMemManager = new GlobalMemoryManager();
	}

	namespace Event {
		EventQueue* g_eventQueue = new EventQueue();
	}
}