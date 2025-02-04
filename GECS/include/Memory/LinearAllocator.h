#pragma once

#include "IAllocator.h"

namespace GECS {
	namespace Memory {
		class GECS_API LinearAllocator : public IAllocator {
		private:
			uptr m_currentPosition;

		public:
			LinearAllocator(size_t memorySize, const uptr firstAddress);

			virtual ~LinearAllocator();

			virtual uptr Allocate(size_t size, u8 align) override;
			virtual void Free(uptr address) override;
			virtual void Clear() override;
		};
	}
}