#pragma once

#include "Event/IEvent.h"

namespace GECS {
	class IClassMethod {
	public:

		IClassMethod()
		{}

		virtual ~IClassMethod()
		{}

		virtual inline void Call() = 0;

		virtual inline void Call(const IEvent* const e) = 0;
	};
}