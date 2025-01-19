#include "ISystem.h"

namespace GECS {
	ISystem::ISystem(u8 priority, f32 updateTime) :
		m_priority(priority),
		m_updateTime(updateTime),
		m_enabled(true)
	{}

	ISystem::~ISystem()
	{}

	void ISystem::IncreaseTimeSinceUpdate(f32 delta) {
		this->m_timeSinceLastUpdate += delta;
	}

	void ISystem::ResetTimeSinceUpdate() {
		this->m_timeSinceLastUpdate = 0;
	}

	bool ISystem::IsExpired() {
		return this->m_updateTime < 0.0f || (this->m_updateTime > 0.0f && this->m_timeSinceLastUpdate > this->m_updateTime);
	}
}