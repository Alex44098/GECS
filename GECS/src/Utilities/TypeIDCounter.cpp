#include "Utilities\TypeIDCounter.h"

namespace GECS {

	class IEntity;
	class IComponent;

	namespace Identifier {
		u64 TypeIDCounter<IEntity>::m_count = 0u;
		u64 TypeIDCounter<IComponent>::m_count = 0u;

		template class TypeIDCounter<IEntity>;
		template class TypeIDCounter<IComponent>;
	}
}