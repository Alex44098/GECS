#pragma once

#include "Platform.h"

// Setting global memory size
#define GECS_GLOBAL_MEMORY_CAPACITY 134217728 // 128 MB

// Chunks settings
#define ENTITY_CONTAINER_CHUNK_MAX_OBJECTS 512
#define COMPONENT_CONTAINER_CHUNK_MAX_OBJECTS 512

// Handle settings
#define HANDLE_MANAGER_GROW_SIZE 1024

namespace GECS {
	class EntityManager;
	class ComponentManager;

	namespace Memory {
		class GlobalMemoryManager;
		extern GlobalMemoryManager* m_globalMemManager; // global manager
	}
}