#include "Memory/StackAllocator.h"

namespace GECS {
	namespace Memory {
		StackAllocator::StackAllocator(size_t memorySize, const uptr firstAddress) :
			IAllocator(memorySize, firstAddress)
		{
			this->Clear();
		}

		StackAllocator::~StackAllocator() {
			this->m_currentPosition = (uptr)nullptr;
		}

		uptr StackAllocator::Allocate(size_t size, u8 align) {
			assert(size > 0 && "Stack allocator: size cant be 0");
			
			u8 offsetWithHeader = GetOffsetWithHeader(m_firstAddress, align, sizeof(StackAllocatorHeader));
			uptr alignedAddress = this->m_currentPosition + offsetWithHeader;

			StackAllocatorHeader* header = (StackAllocatorHeader*)(alignedAddress - sizeof(StackAllocatorHeader));
			header->offset = offsetWithHeader;

			this->m_currentPosition += size + offsetWithHeader;
			this->m_numAllocations++;

			return alignedAddress;
		}

		void StackAllocator::Free(uptr address) {
			StackAllocatorHeader* header = (StackAllocatorHeader*)(address - sizeof(StackAllocatorHeader));
			this->m_currentPosition = address - header->offset;
			this->m_numAllocations--;
		}

		void StackAllocator::Clear() {
			this->m_numAllocations = 0;
		}
	}
}