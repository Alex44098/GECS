#pragma once

#include "ISystem.h"
#include "Utilities/TypeIDCounter.h"

namespace GECS {
	template<class T>
	class System : public ISystem {
	public:
		static const type_id SYSTEM_TYPE_ID;

	protected:
		System()
		{}

	public:
		virtual ~System()
		{}

		virtual inline const type_id GetSystemTypeId() const {
			return SYSTEM_TYPE_ID;
		}

		virtual void Update(f32 update)
		{}
	};

	template<class T>
	const type_id System<T>::SYSTEM_TYPE_ID = Identifier::TypeIDCounter<ISystem>::GetTypeId<T>();
}