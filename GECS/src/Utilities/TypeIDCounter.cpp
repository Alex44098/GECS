#include "Utilities\TypeIDCounter.h"

namespace GECS {

	class IEntity;
	class IComponent;
	class ISystem;

	namespace Event {
		class IEvent;
	}

	namespace Identifier {
		u64 TypeIDCounter<IEntity>::m_count = 0u;
		u64 TypeIDCounter<IComponent>::m_count = 0u;
		u64 TypeIDCounter<ISystem>::m_count = 0u;
		u64 TypeIDCounter<Event::IEvent>::m_count = 0u;


		template class TypeIDCounter<IEntity>;
		template class TypeIDCounter<IComponent>;
		template class TypeIDCounter<ISystem>;
		template class TypeIDCounter<Event::IEvent>;
	}
}