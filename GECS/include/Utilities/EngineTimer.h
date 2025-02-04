#pragma once

#include "Facade.h"

namespace GECS {
	namespace Util {
		class GECS_API EngineTimer {
		private:

			std::chrono::duration<f32, std::milli> m_elapsedTime;

		public:

			EngineTimer();
			~EngineTimer();

			void Tick(f32 delta);
			void Reset();

			inline f32 GetTime() const {
				return this->m_elapsedTime.count();
			}
		};
	}
}