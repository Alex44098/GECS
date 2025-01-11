#include "Memory/IAllocator.h"

namespace GECS {
	namespace Memory {
		IAllocator::IAllocator(const size_t memorySize, const uptr firstAddress) :
			m_memorySize(memorySize),
			m_firstAddress(firstAddress),
			m_numAllocations(0)
		{}

		IAllocator::~IAllocator()
		{}
	}
}