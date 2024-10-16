#pragma once

#include "API.h"

namespace GECS {
	namespace Identifier {
		/// <summary>
		/// Struct: Handle
		/// 
		/// <para> Created for safe objects identification. </para>
		/// <para> Contains params:</para>
		/// <para>- Index: used to store the index of an object in collections. </para>
		/// <para>- Version: It is used to prevent the appearance of dangling pointers. </para>
		/// </summary>
		/// <typeparam name="handle_type">Type of internal parameters</typeparam>
		/// <typeparam name="version_bits">Amount of bits used for indexes</typeparam>
		/// <typeparam name="index_bits">Amount of bits used for versions</typeparam>
		template<typename value_type, size_t index_bits, size_t version_bits>
		struct UniversalHandle {

			static constexpr value_type	MIN_VERSION{ 0 };
			static constexpr value_type	MAX_VERSION{ (1U << version_bits) - 2U };
			static constexpr value_type	MAX_INDICES{ (1U << index_bits) - 2U };

			static constexpr value_type	INVALID_HANDLE{ std::numeric_limits<value_type>::max() };

		public:

			value_type index;
			value_type version;

			UniversalHandle() {}

			UniversalHandle(value_type index, value_type version) :
				index(index),
				version(version)
			{}

			inline operator value_type() const { return value; }
		};
	}

	//---------------------------------------------------------------
	// Installing a descriptors for systems with different bit rates.
	// 
	// 64 bit:
	// - Value type: unsigned 64 bit int, max value: 18,446,744,073,709,551,616
	// - Max posible indices: 1,099,511,627,776 (40 bits)
	// - Max posible versions: 16,777,216 (24 bits)
	// - 1,099,511,627,776 * 16,777,216 = 18,446,744,073,709,551,616
	// 
	// 32 bit:
	// - Value type: unsigned 32 bit int, max value: 4,294,967,296
	// - Max posible indices: 1,048,576 (20 bits)
	// - Max posible versions: 4,096 (12 bits)
	// - 1,048,576 * 4,096 = 4,294,967,296
	//---------------------------------------------------------------
#ifdef GECS_64
	using Handle = Identifier::UniversalHandle<u64, 40, 24>;
#else
	using Handle = Identifier::UniversalHandle<u32, 20, 12>;
#endif
}