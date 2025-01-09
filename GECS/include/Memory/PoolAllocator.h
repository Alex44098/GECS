#pragma once

#include "IAllocator.h"

namespace GECS {
	namespace Memory {
		class PoolAllocator : public IAllocator {

			const size_t m_objectSize;
			const u8 m_objectAlignment;
			uptr* m_pool;

		public:

			PoolAllocator(size_t memorySize, const uptr firstAddress, size_t objectSize, u8 objectAlignment);

			virtual ~PoolAllocator();

			virtual uptr Allocate(size_t size, u8 alignment) override;
			virtual void Free(uptr address) override;
			virtual void Clear() override;
		};
	}
}