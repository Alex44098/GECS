#include "Utilities/EngineTimer.h"

namespace GECS {
	namespace Util {
		EngineTimer::EngineTimer() :
			m_elapsedTime(0)
		{}

		EngineTimer::~EngineTimer()
		{}

		void EngineTimer::Tick(f32 delta) {
			this->m_elapsedTime += std::chrono::duration<f32, std::ratio<1, 1000>>(delta);
		}

		void EngineTimer::Reset() {
			this->m_elapsedTime = std::chrono::duration<f32, std::milli>::zero();
		}
	}
}