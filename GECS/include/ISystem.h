#pragma once

#include "Facade.h"

#define LOWEST_SYSTEM_PRIORITY 0

#define LOW_SYSTEM_PRIORITY 3

#define MEDIUM_SYSTEM_PRIORITY 5

#define HIGH_SYSTEM_PRIORITY 7

#define HIGHEST_SYSTEM_PRIORITY 10

namespace GECS {
	class GECS_API ISystem {

		friend class SystemManager;

	private:
		f32 m_updateTime;

		f32 m_timeSinceLastUpdate;

	protected:

		ISystem(u8 priority = MEDIUM_SYSTEM_PRIORITY, f32 updateTime = -1.0f);

	public:

		bool m_enabled;

		u8 m_priority;

		virtual ~ISystem();

		virtual inline const type_id GetSystemTypeId() const = 0;

		virtual void Update(f32 delta) = 0;

		inline void ResetTimeSinceUpdate() {
			this->m_timeSinceLastUpdate = 0;
		}

		inline bool IsExpired() {
			return this->m_updateTime < 0.0f || (this->m_updateTime > 0.0f && this->m_timeSinceLastUpdate > this->m_updateTime);
		}
	};
}