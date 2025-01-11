#pragma once

#include "Facade.h"
#include "Memory/PoolAllocator.h"

namespace GECS {
	namespace Memory {
		template<class T>
		class ChunkAllocator
		{

		private:
			static const size_t m_maxObjects;
			static const size_t m_allocSize;

			class MemoryChunk {
			public:
				PoolAllocator* m_allocator;
				std::list<T*> m_objects;
				uptr m_startAddress;
				uptr m_endAddress;

				MemoryChunk(PoolAllocator* allocator) : m_allocator(allocator) {
					this->m_startAddress = allocator->GetAddressBegining());
					this->m_endAddress = this->m_startAddress + m_allocSize;
					this->m_objects.clear();
				}
			};

			std::list<MemoryChunk*> m_chunks;

		public:
			ChunkAllocator() {
				PoolAllocator* allocator = new PoolAllocator(m_allocSize, );
			}

			~ChunkAllocator() {
				
			}

		private:

		};
	}
}