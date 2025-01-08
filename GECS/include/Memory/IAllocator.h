#pragma once

#include "API.h"

namespace GECS {
	namespace Memory {

		union MemoryAddress {
			void* asVoidPtr;
			uintptr_t asUintPtr;
		};

		class IAllocator {
		protected:
			const size_t m_memorySize;
			const MemoryAddress m_firstAddress;
			u64 m_numAllocations;

		public:
			IAllocator(const size_t memorySize, const MemoryAddress firstAddress);
			virtual ~IAllocator();

			virtual MemoryAddress Allocate(size_t size, u8 alignment);
			virtual void Free(MemoryAddress address);
			virtual void Clear();

			inline size_t GetMemorySize() const {
				return this->m_memorySize;
			}

			inline MemoryAddress GetAddressBegining() const {
				return this->m_firstAddress;
			}

			inline u64 GetAllocationsCount() const {
				return this->m_numAllocations;
			}
		};
	}
}