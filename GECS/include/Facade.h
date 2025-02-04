#pragma once

#include "Platform.h"

// Setting global memory size
#define GECS_GLOBAL_MEMORY_CAPACITY 134217728 // 128 MB

// Setting system manager memory size
#define GECS_SYSTEM_MANAGER_MEMORY_CAPACITY 8388608 // 8 MB

// Setting event buffer memory size
#define GECS_EVENT_BUFFER_MEMORY_SIZE 4194304 // 4 MB

// Chunks settings
#define ENTITY_CONTAINER_CHUNK_MAX_OBJECTS 512
#define COMPONENT_CONTAINER_CHUNK_MAX_OBJECTS 512

// Managers tables settings
#define ENTITY_COMPONENT_TABLE_GROW_SIZE 1024
#define COMPONENT_TABLE_GROW_SIZE 1024

// Handle settings
#define HANDLE_MANAGER_GROW_SIZE 1024

namespace GECS {
	class EntityManager;
	class ComponentManager;
	class SystemManager;
	
	namespace Event {
		class EventQueue;
	}

	namespace Util {
		class EngineTimer;
	}

	namespace Memory {
		class GlobalMemoryManager;
		extern GlobalMemoryManager* g_globalMemManager; // global manager
	}

	class GECSMain;
	GECS_API extern GECSMain* GECSInstance;

	GECS_API void Init();
	GECS_API void Destroy();
}