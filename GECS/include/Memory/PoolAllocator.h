#pragma once

#include "IAllocator.h"

namespace GECS {
	namespace Memory {
		class GECS_API PoolAllocator : public IAllocator {

		private:
			const size_t m_objectSize;
			const u8 m_objectAlignment;
			void** m_pool;

		public:

			PoolAllocator(size_t memorySize, const uptr firstAddress, size_t objectSize, u8 objectAlignment);

			virtual ~PoolAllocator();

			virtual uptr Allocate(size_t size, u8 align) override;
			virtual void Free(uptr address) override;
			virtual void Clear() override;
		};
	}
}