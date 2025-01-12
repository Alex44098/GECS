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
				PoolAllocator* allocator = new PoolAllocator(m_allocSize, m_globalMemManager->Allocate(m_allocSize), sizeof(T), alignof(T));
				this->m_chunks.push_back(new MemoryChunk(allocator));
			}

			~ChunkAllocator() {
				// free all chunks
				for (MemoryChunk chunk : this->m_chunks) {
					// release all objects
					for (T object : chunk->m_objects) {
						((T*)object)->~T();
					}

					chunk->m_objects.clear();

					// release memory, allocated for allocator in chunk
					m_globalMemManager->Free((void*)chunk->m_allocator->GetAddressBegining());
					delete chunk->m_allocator;

					delete chunk;
				}
				m_chunks.clear();
			}

			uptr CreateObject() {
				uptr slot = nullptr;

				for (MemoryChunk chunk : this->m_chunks) {
					if (chunk->m_objects.size() > m_maxObjects)
						continue;

					slot = chunk->m_allocator->Allocate(sizeof(T), alignof(T));
					assert(slot != nullptr && "Chunk allocator: new object not created");
					if (slot != nullptr) {
						chunk->m_objects.push_back((T*)slot);
						return slot;
					}
				}

				// creating new chunk
				PoolAllocator* allocator = new PoolAllocator(m_allocSize, m_globalMemManager->Allocate(m_allocSize), sizeof(T), alignof(T));
				MemoryChunk* newChunk = new MemoryChunk(allocator);

				this->m_chunks.push_front(newChunk);

				slot = newChunk->m_allocator->Allocate(sizeof(T), alignof(T));
				assert(slot != nullptr && "Chunk allocator: new object not created");
				newChunk->m_objects.clear();
				newChunk->m_objects.push_back((T*)slot);
			}

			void ReleaseObject(uptr address) {
				for (MemoryChunk chunk : this->m_chunks) {
					if (chunk->m_startAddress <= address && address < chunk->m_endAddress) {
						chunk->m_objects.remove((T*)address);
						chunk->m_allocator->Free(address);

						return;
					}
				}

				assert(false && "Chunk allocator: error while deleting object");
			}
		};
	}
}