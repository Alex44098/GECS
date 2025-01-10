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

		uptr PoolAllocator::Allocate(size_t size, u8 align) {
			assert(size > 0 && "Pool allocator: size cant be 0");
			assert(size == this->m_objectSize && align == this->m_objectAlignment && "Pool allocator: size and align should be standart");
			assert(m_pool != nullptr && "Pool allocator: allocator not init");

			uptr freeSlot = (uptr)this->m_pool;

			// move to the next free slot
			this->m_pool = (uptr*)(*this->m_pool);
			
			this->m_numAllocations++;

			return freeSlot;
		}

		void PoolAllocator::Free(uptr address) {
			*((uptr**)address) = this->m_pool;

			this->m_pool = (uptr*)address;

			this->m_numAllocations--;
		}

		void PoolAllocator::Clear() {
			u8 offset = GetOffset(this->m_firstAddress, this->m_objectAlignment);

			size_t numObjects = (size_t)floor((this->m_memorySize - offset) / this->m_objectSize);

			this->m_pool = (uptr*)(this->m_firstAddress + offset);

			uptr* slot = this->m_pool;
			for (int i = 0; i < (numObjects - 1); i++) {
				*slot = (uptr)(slot + this->m_objectSize);
				slot = (uptr*)*slot;
			}

			*slot = (uptr)nullptr;
		}
	}
}