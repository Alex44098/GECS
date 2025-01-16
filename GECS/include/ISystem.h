#pragma once

#include "Facade.h"

#define LOWEST_SYSTEM_PRIORITY 0

#define LOW_SYSTEM_PRIORITY 3

#define MEDIUM_SYSTEM_PRIORITY 5

#define HIGH_SYSTEM_PRIORITY 7

#define HIGHEST_SYSTEM_PRIORITY 10

namespace GECS {
	class ISystem {
	private:
		u8 m_enabled;
		u8 m_priority;
		f32 m_updateTime;

		u8 m_expired;
		f32 m_timeSinceLastUpdate;

	protected:

		ISystem(u8 priority = MEDIUM_SYSTEM_PRIORITY, f32 updateTime = -1.0f);
		virtual ~ISystem();

		virtual inline const type_id GetSystemTypeId() const = 0;

		virtual void Update(f32 elapsedTime) = 0;
	};
}