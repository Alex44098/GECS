#include "Memory/PoolAllocator.h"

namespace GECS {
	namespace Memory {
		PoolAllocator::PoolAllocator(size_t memorySize, const uptr firstAddress, size_t objectSize, u8 objectAlignment) :
			IAllocator(memorySize, firstAddress),
			m_objectSize(objectSize),
			m_objectAlignment(objectAlignment)
		{
			this->Clear();
		}

		PoolAllocator::~PoolAllocator() {
			this->m_pool = nullptr;
		}

		uptr PoolAllocator::Allocate(size_t size, u8 align) { // This is where "SOLID" leaves us
			assert(size > 0 && "Pool allocator: size cant be 0");
			assert(size == this->m_objectSize &&
				align == this->m_objectAlignment &&
				"Pool allocator: size and align should be standart");
			
			if (m_pool == nullptr) {
				L_(lwarning) << "Pool allocator: going beyond memory limits!";
				return 0;
			}

			void* freeSlot = this->m_pool;

			// move to the next free slot
			this->m_pool = (void**)(*this->m_pool);
			
			this->m_numAllocations++;

			return reinterpret_cast<uptr>(freeSlot);
		}

		void PoolAllocator::Free(uptr address) {
			*((void**)address) = this->m_pool;
			this->m_pool = (void**)address;
			this->m_numAllocations--;
		}

		void PoolAllocator::Clear() {
			u8 offset = GetOffset(this->m_firstAddress, this->m_objectAlignment);

			size_t numObjects = (this->m_memorySize - offset) / this->m_objectSize;

			this->m_pool = (void**)(this->m_firstAddress + offset);
			void** slot = this->m_pool;
			
			for (int i = 0; i < numObjects - 1; i++) {
				*slot = (void*)(reinterpret_cast<uptr>(slot) + this->m_objectSize);
				slot = (void**)*slot;
			}

			*slot = nullptr;
		}
	}
}