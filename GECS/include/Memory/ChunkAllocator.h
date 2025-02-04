#pragma once

#include "Facade.h"
#include "Memory/GlobalMemoryManager.h"
#include "Memory/PoolAllocator.h"

namespace GECS {
	namespace Memory {
		template<class T, size_t MAX_OBJECTS>
		class ChunkAllocator {

		private:
			static const size_t m_maxObjects = MAX_OBJECTS;
			static const size_t m_allocSize = sizeof(T) * m_maxObjects + alignof(T);

			class MemoryChunk {
			public:
				PoolAllocator* m_allocator;
				std::list<T*> m_objects;
				uptr m_startAddress;
				uptr m_endAddress;

				MemoryChunk(PoolAllocator* allocator) : m_allocator(allocator) {
					this->m_startAddress = allocator->GetAddressBegining();
					this->m_endAddress = this->m_startAddress + m_allocSize;
					this->m_objects.clear();
				}
			};

			std::list<MemoryChunk*> m_chunks;

		public:
			class iterator : public std::iterator<std::forward_iterator_tag, T>
			{
				typename std::list<MemoryChunk*>::iterator curChunk;
				typename std::list<MemoryChunk*>::iterator lastChunk;
				typename std::list<T*>::iterator curObject;

			public:

				iterator(typename std::list<MemoryChunk*>::iterator begin, typename std::list<MemoryChunk*>::iterator end) :
				curChunk(begin),
				lastChunk(end)
				{
					if (begin != end) {
						assert(*curChunk != nullptr && "Chunk allocator: iterator's init");
						curObject = (*curChunk)->m_objects.begin();
					}
					else
						curObject = (*std::prev(lastChunk))->m_objects.end();
				}

				inline iterator& operator++() {
					curObject++;

					if (curObject == (*curChunk)->m_objects.end()) {
						curChunk++;
						if (curChunk != lastChunk) {
							curObject = (*curChunk)->m_objects.begin();
						}
					}

					return *this;
				}

				inline T& operator*() const { return *curObject; }
				inline T* operator->() const { return *curObject; }

				inline bool operator==(iterator& other) {
					return (this->curChunk == other.curChunk) && (this->curObject == other.curObject);
				}
				inline bool operator!=(iterator& other) {
					return (this->curChunk != other.curChunk) && (this->curObject != other.curObject);
				}
			};

			ChunkAllocator() {
				PoolAllocator* allocator = new PoolAllocator(m_allocSize, g_globalMemManager->Allocate(m_allocSize), sizeof(T), alignof(T));
				this->m_chunks.push_back(new MemoryChunk(allocator));
			}

			~ChunkAllocator() {
				// free all chunks
				for (MemoryChunk* chunk : this->m_chunks) {
					// release all objects
					for (T* object : chunk->m_objects) {
						object->~T();
					}

					chunk->m_objects.clear();

					// release memory, allocated for allocator in chunk
					g_globalMemManager->Free(chunk->m_startAddress);

					// don't forget free allocator in chunk!!!
					delete chunk->m_allocator;

					delete chunk;
				}
				m_chunks.clear();
			}

			uptr CreateObject() {
				uptr slot = 0;

				for (MemoryChunk* chunk : this->m_chunks) {
					if (chunk->m_objects.size() >= m_maxObjects)
						continue;

					slot = chunk->m_allocator->Allocate(sizeof(T), alignof(T));
					if (slot != 0) {
						chunk->m_objects.push_back((T*)slot);
						return slot;
					}
					else
						assert(false && "Chunk allocator: new object not created");
				}

				// creating new chunk
				PoolAllocator* allocator = new PoolAllocator(m_allocSize, g_globalMemManager->Allocate(m_allocSize), sizeof(T), alignof(T));
				MemoryChunk* newChunk = new MemoryChunk(allocator);

				this->m_chunks.push_front(newChunk);

				slot = newChunk->m_allocator->Allocate(sizeof(T), alignof(T));
				assert(slot != 0 && "Chunk allocator: new object not created");
				newChunk->m_objects.clear();
				newChunk->m_objects.push_back((T*)slot);

				return slot;
			}

			void ReleaseObject(uptr address) {
				for (MemoryChunk* chunk : this->m_chunks) {
					if (chunk->m_startAddress <= address && address < chunk->m_endAddress) {
						chunk->m_objects.remove((T*)address);
						chunk->m_allocator->Free(address);

						return;
					}
				}

				assert(false && "Chunk allocator: error while deleting object");
			}

			inline iterator begin() {
				return iterator(this->m_chunks.begin(), this->m_chunks.end());
			}

			inline iterator end() {
				return iterator(this->m_chunks.end(), this->m_chunks.end());
			}
		};
	}
}