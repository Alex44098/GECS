#pragma once

#include "Facade.h"

namespace GECS {
	namespace Memory {

		union MemoryAddress {
			void* asVoidPtr;
			uptr asUintPtr;
		};

		inline u8 GetOffset(uptr addr, u8 align) {
			const u8 mask = align - 1;
			assert((align & mask) == 0 && "Allocator: not power of 2");
			const u8 offset = align - (addr & mask);
			return offset == align ? 0 : offset;
		}

		inline u8 GetOffsetWithHeader(uptr addr, u8 align, u8 headerSize) {
			u8 offset = GetOffset(addr, align);
			if (offset < headerSize) {
				headerSize -= offset;
				offset += align * (headerSize / align);
				if (headerSize % align > 0)
					offset += align;
			}
			return offset;
		}

		class GECS_API IAllocator {

		protected:
			const size_t m_memorySize;
			const uptr m_firstAddress;
			u64 m_numAllocations;

		public:
			IAllocator(const size_t memorySize, const uptr firstAddress);
			virtual ~IAllocator();

			virtual uptr Allocate(size_t size, u8 align) = 0;
			virtual void Free(uptr address) = 0;
			virtual void Clear() = 0;

			inline size_t GetMemorySize() const {
				return this->m_memorySize;
			}

			inline uptr GetAddressBegining() const {
				return this->m_firstAddress;
			}

			inline u64 GetAllocationsCount() const {
				return this->m_numAllocations;
			}
		};
	}
}