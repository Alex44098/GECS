#pragma once

// Declare includes
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <limits>
#include <assert.h>

#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <functional>

#include <chrono>

// Creating ".dll" setting
#ifdef GECS_EXPORT
	#define GECS_API __declspec(dllexport)
#else  
	#define GECS_API __declspec(dllimport)
#endif

// Check for 64-bit system
#if (defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(_M_AMD64) || defined(_M_ARM64) || defined(_M_X64))
	#define GECS_64 1
#endif

namespace GECS {
	// Integer
	using i8			= int8_t;
	using i16			= int16_t;
	using i32			= int32_t;
#ifdef GECS_64
	using i64			= int64_t;
#else
	using i64			= int32_t;
#endif

	// Unsigned integer
	using u8			= uint8_t;
	using u16			= uint16_t;
	using u32			= uint32_t;
#ifdef GECS_64
	using u64			= uint64_t;
#else
	using u64			= uint32_t;
#endif

	// Unsigned pointer
	using uptr			= uintptr_t;

	// Float
	using f32			= float_t;
	using f64			= double_t;

	// Identificator types
	using object_id		= size_t;
	using type_id		= size_t;

	// Invalid ID values
	static const object_id	INVALID_OBJECT_ID = std::numeric_limits<object_id>::max();
	static const type_id	INVALID_TYPE_ID = std::numeric_limits<type_id>::max();
}