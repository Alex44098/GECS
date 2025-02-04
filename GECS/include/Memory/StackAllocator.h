#pragma once

#include "IAllocator.h"

namespace GECS {
	namespace Memory {
		class GECS_API StackAllocator : public IAllocator {

		private:
			uptr m_currentPosition;

			struct StackAllocatorHeader {
				u8 offset;
			};

		public:
			StackAllocator(size_t memorySize, const uptr firstAddress);
			virtual ~StackAllocator();

			virtual uptr Allocate(size_t size, u8 align) override;
			virtual void Free(uptr address) override;
			virtual void Clear() override;
		};
	}
}