#pragma once

#include "Event/IEvent.h"

namespace GECS {
	class GECS_API IClassMethod {
	public:

		IClassMethod();

		virtual ~IClassMethod();

		virtual inline void Call() = 0;

		virtual inline void Call(const Event::IEvent* const e) = 0;

		virtual bool operator==(const IClassMethod* other) const = 0;
	};
}