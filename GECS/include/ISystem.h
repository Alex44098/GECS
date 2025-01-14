#pragma once

#include "Facade.h"

#define LOW_SYSTEM_PRIORITY 0

#define MEDIUM_SYSTEM_PRIORITY 5

#define HIGH_SYSTEM_PRIORITY 10

namespace GECS {
	class ISystem {
	private:
		u8 m_priority;
		f32 m_updateTime;
		f32 m_timeSinceLastUpdate;

	protected:

		ISystem(u8 priority = MEDIUM_SYSTEM_PRIORITY, f32 updateTime);
		virtual ~ISystem();

		virtual inline const type_id GetSystemTypeId() const = 0;

		virtual void Update(f32 elapsedTime) = 0;
	};
}