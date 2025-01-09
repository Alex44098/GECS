#pragma once

#include "IAllocator.h"

namespace GECS {
	namespace Memory {
		struct StackAllocatorHeader {
			u8 offset;
		};

		class StackAllocator : public IAllocator {
		public:
			StackAllocator(size_t memorySize, const uptr firstSize);
			virtual ~StackAllocator();

			virtual uptr Allocate(size_t size, u8 align) override;
			virtual void Free(uptr address) override;
			virtual void Clear() override;
		};
	}
}