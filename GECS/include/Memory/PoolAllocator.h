#pragma once

#include "IAllocator.h"

namespace GECS {
	namespace Memory {
		class PoolAllocator : public IAllocator {
			const size_t objectSize;
			const u8 objectAlignment;
		public:
			PoolAllocator(size_t memorySize, const MemoryAddress firstAddress, size_t objectSize, u8 objectAlignment);

			virtual ~PoolAllocator();

			virtual MemoryAddress Allocate(size_t size, u8 alignment) override;
			virtual void Free(MemoryAddress ) override;
			virtual void Clear() override;
		};
	}
}