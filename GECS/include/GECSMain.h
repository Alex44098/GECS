#pragma once

#include "Facade.h"

namespace GECS {
	class GECS_API GECSMain {
		EntityManager* EM;
		ComponentManager* CM;
		SystemManager* SM;
		Event::EventQueue* EQ;
		Util::EngineTimer* ET;

	public:
		GECSMain();
		~GECSMain();

		inline EntityManager* GetEntityManager() { return EM; }
		inline ComponentManager* GetComponentManager() { return CM; }
		inline SystemManager* GetSystemManager() { return SM; }
		inline Event::EventQueue* GetEventQueue() { return EQ; }

		void Update(f32 delta);
	};
}