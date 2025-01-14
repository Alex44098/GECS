#pragma once

#include "Facade.h"
#include "Handle.h"

namespace GECS {
	namespace Identifier {
		template<class T, class handle_type>
		class HandleManager {
			
		private:
			/// <summary>
			/// <para> LookUp table </para>
			/// <para> Contains pairs of handles and object pointers </para>
			/// </summary>
			std::vector<std::pair<typename handle_type::value_type, T*>> m_table;
			size_t m_growSize;
			
			void GrowTable() {
				size_t oldSize = this->m_table.size();

				assert(oldSize < handle_type::MAX_INDICES &&
						"Handle manager: Max table capacity reached!");

				size_t newSize = std::min(oldSize + m_growSize, handle_type::MAX_INDICES);

				this->m_table.resize(newSize);

				typename handle_type::value_type i = oldSize;
				for (; i < newSize; ++i)
					this->m_table[i] = std::pair<typename handle_type::value_type, T*>();
			}

		public:

			HandleManager() : m_growSize(HANDLE_MANAGER_GROW_SIZE) {
				this->GrowTable();
			}

			handle_type GetHandle(T* p_object) {
				typename handle_type::value_type i = 0;

				for (; i < this->m_table.size(); ++i)
				{
					if (this->m_table[i].second == nullptr)
					{
						this->m_table[i].second = p_object;
						this->m_table[i].first =
							this->m_table[i].first + 1 > handle_type::MAX_VERSION
								? handle_type::MIN_VERSION
								: this->m_table[i].first + 1;

						return handle_type(i, this->m_table[i].first);
					}
				}

				GrowTable();

				this->m_table[i].first = 1;
				this->m_table[i].second = p_object;

				return handle_type(i, this->m_table[i].first);
			}

			void ReleaseHandle(handle_type handle) {
				assert((handle.index < this->m_table.size() &&
						handle.version == this->m_table[handle.index].first) &&
						"Handle manager: Releasing error. Invalid handle!");

				this->m_table[handle.index].second = nullptr;
			}

			inline handle_type operator[](typename handle_type::value_type index) const {
				assert(index < this->m_table.size() &&
						"Handle manager: Index out of range!");

				return handle_type(index, this->m_table[index].first);
			}

			inline T* operator[](handle_type handle) {
				assert((handle.index < this->m_table.size() &&
						handle.version == this->m_table[handle.index].first) &&
						"Handle manager: Invalid handle!");

				return this->m_table[handle.index].second;
			}
		};
	}
}