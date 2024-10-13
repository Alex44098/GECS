#pragma once

#include "../API.h"

namespace GECS {
	namespace Handle {
		/// <summary>
		/// Struct: Handle
		/// 
		/// </summary>
		/// <typeparam name="handle_type">Type of internal parameters</typeparam>
		/// <typeparam name="version_bits">Amount of bits used for indexes</typeparam>
		/// <typeparam name="index_bits">Amount of bits used for versions</typeparam>
		template<typename handle_type, size_t index_bits, size_t version_bits>
		struct Handle {
			static constexpr handle_type	MIN_VERSION{ 0 };
			static constexpr handle_type	MAX_VERSION{ (1U << version_bits) - 2U };
			static constexpr handle_type	MAX_INDICES{ (1U << index_bits) - 2U };

			static constexpr handle_type	INVALID_HANDLE{ std::numeric_limits<handle_type>::max() };

		public:
			handle_type index;
			handle_type version;

			Handle() {}

			Handle(handle_type index, handle_type version) :
				index(index),
				version(version)
			{}
		};
	}
}