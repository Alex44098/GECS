#include "ISystem.h"

namespace GECS {
	ISystem::ISystem(u8 priority, f32 updateTime) :
		m_priority(priority),
		m_updateTime(updateTime),
		m_timeSinceLastUpdate(0.f),
		m_enabled(true)
	{}

	ISystem::~ISystem()
	{}
}