#pragma once

#include "IEntity.h"
#include "Utilities/TypeIDCounter.h"

namespace GECS {
	template <class T>
	class Entity : public IEntity {
	public:
		static const type_id ENTITY_TYPE_ID;

		Entity() {}

		virtual ~Entity() {}

		virtual inline const type_id GetEntityTypeId() override const {
			return ENTITY_TYPE_ID;
		}
	};
	
	template <class T>
	const type_id Entity<T>::ENTITY_TYPE_ID = Identifier::TypeIDCounter<IEntity>::GetTypeId<T>();
}