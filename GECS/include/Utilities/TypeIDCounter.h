#pragma once

#include "Facade.h"

namespace GECS {
	namespace Identifier {

		template<class InterfaceType>
		class TypeIDCounter {

			static type_id m_count;

		public:

			template<class ObjectType>
			static const type_id GetTypeId() {
				static const type_id newTypeId { m_count++; }
				return newTypeId;
			}

			static const type_id GetTypeId() {
				return m_count;
			}
		};

	}
}