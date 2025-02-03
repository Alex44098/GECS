#include "GECSMain.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

#include "Event/EventQueue.h"
#include "Utilities/EngineTimer.h"

namespace GECS {
	GECSMain::GECSMain() {
		SM = new SystemManager();
		CM = new ComponentManager();
		EM = new EntityManager(this->CM);
		EQ = new Event::EventQueue();

		ET = new Util::EngineTimer;
	}

	GECSMain::~GECSMain() {
		delete this->CM;
		delete this->EM;
		delete this->SM;
		delete this->EQ;
		delete this->ET;
	}

	void GECSMain::Update(f32 delta) {
		ET->Tick(delta);

		SM->Update(delta);

		EM->DestroyReleasedEntities();
		EQ->ProcessEvents();
	}
}