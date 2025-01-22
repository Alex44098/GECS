#pragma once

#include "ISystem.h"
#include "Utilities/TypeIDCounter.h"

#include "SystemManager.h"

namespace GECS {
	template<class T>
	class System : public ISystem {

		friend class SystemManager;

	public:
		static const type_id SYSTEM_TYPE_ID;

	protected:

		SystemManager* m_systemManagerSingleton;

		System()
		{}

	public:
		virtual ~System()
		{}

		virtual inline const type_id GetSystemTypeId() const {
			return SYSTEM_TYPE_ID;
		}

		template<class Dependency>
		void AddDependency(Dependency depend) {
			this->m_systemManagerSingleton->AddSystemDependency(this, depend);
		}

		virtual void Update(f32 delta)
		{}
	};

	template<class T>
	const type_id System<T>::SYSTEM_TYPE_ID = Identifier::TypeIDCounter<ISystem>::GetTypeId<T>();
}