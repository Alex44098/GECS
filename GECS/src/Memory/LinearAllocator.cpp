#include "Memory/LinearAllocator.h"

namespace GECS {
	namespace Memory {
		LinearAllocator::LinearAllocator(size_t memorySize, const uptr firstAddress) :
			IAllocator(memorySize, firstAddress),
			m_currentPosition(firstAddress)
		{}

		LinearAllocator::~LinearAllocator() {
			this->Clear();
		}

		uptr LinearAllocator::Allocate(size_t size, u8 align) {
			assert(size > 0 && "Linear allocator: size cant be 0");

			uptr offset = GetOffset(m_currentPosition, align);
			uptr alignedAddress = this->m_currentPosition + offset;

			if (alignedAddress - m_firstAddress + size > m_memorySize)
				return 0;

			m_currentPosition = alignedAddress + size;
			m_numAllocations++;

			return alignedAddress;
		}

		void LinearAllocator::Free(uptr address) {
			assert(false && "Linear allocator: this allocator only for systems!");
		}

		void LinearAllocator::Clear() {
			this->m_currentPosition = this->m_firstAddress;
			this->m_numAllocations = 0;
		}
	}
}