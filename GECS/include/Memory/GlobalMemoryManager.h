#pragma once

#include "Facade.h"
#include "Memory/StackAllocator.h"

namespace GECS {
	namespace Memory {
		class GlobalMemoryManager {

		private:
			uptr m_globalMemory;

			StackAllocator* m_memoryAllocator;
			std::vector<uptr> m_pendingAddresses;
			std::list<uptr> m_releasedAddresses;

		public:
			static constexpr size_t MEMORY_CAPACITY = GECS_GLOBAL_MEMORY_CAPACITY;

			GlobalMemoryManager();
			~GlobalMemoryManager();

			inline uptr Allocate(size_t size) {
				uptr allocatedMemory = m_memoryAllocator->Allocate(size, alignof(u8));

				if (allocatedMemory == 0) {
					L_(lerror) << "Out of global memory!";
					L_(lerror) << "Size of GM: " << m_memoryAllocator->GetMemorySize();
					L_(lerror) << "Attempt to allocate memory with size " << size;
					assert(false && "Global memory: out of memory!");
				}

				L_(linfo) << "An address " << allocatedMemory << " with a size of " << size << " has been allocated in global memory";

				this->m_pendingAddresses.push_back(allocatedMemory);

				return allocatedMemory;
			}

			inline void Free(uptr address) {

				// checking whether the address is at the top of the stack
				if (address == this->m_pendingAddresses.back()) {

					// deallocate past memory allocation
					this->m_memoryAllocator->Free(address);
					this->m_pendingAddresses.pop_back();

					// let's see if we can release the addresses to be released
					bool b_freedAddressFound = true;
					while (b_freedAddressFound == true) {
						b_freedAddressFound = false;

						// viewing the list of released addresses
						for (uptr freedAddress : this->m_releasedAddresses) {

							// checking whether the address is at the top of the stack
							if (freedAddress == this->m_pendingAddresses.back()) {
								this->m_memoryAllocator->Free(freedAddress);
								this->m_releasedAddresses.remove(freedAddress);
								this->m_pendingAddresses.pop_back();

								b_freedAddressFound = true;
								break;
							}
						}
					}
				}
				else {
					// saving address for later deallocating (releasing)
					this->m_releasedAddresses.push_back(address);
				}
			}
		};
	}
}