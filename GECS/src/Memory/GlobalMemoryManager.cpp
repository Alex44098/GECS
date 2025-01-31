#include "Memory/GlobalMemoryManager.h"

namespace GECS{
	namespace Memory {
		GlobalMemoryManager::GlobalMemoryManager() {
			this->m_globalMemory = reinterpret_cast<uptr>(malloc(MEMORY_CAPACITY));
			assert(this->m_globalMemory != 0 && "Global memory: failed to allocate global memory");
			
			this->m_memoryAllocator = new StackAllocator(MEMORY_CAPACITY, this->m_globalMemory);
			assert(this->m_memoryAllocator != nullptr && "Global memory: failed to create allocator");

			this->m_releasedAddresses.clear();
			this->m_pendingAddresses.clear();
		}

		GlobalMemoryManager::~GlobalMemoryManager() {
			this->m_memoryAllocator->Clear();

			delete this->m_memoryAllocator;
			this->m_memoryAllocator = nullptr;

			free((void*)this->m_globalMemory);
			this->m_globalMemory = 0;
		}
	}
}