#pragma once

#include "IClassMethod.h"
#include "ClassMethod.h"

namespace GECS {
	class Delegate {
		IClassMethod* m_classMethod;

	public:

		Delegate();

		virtual ~Delegate();

		template<class Class, class Method>
		void Connect(Class* c, Method method) {
			if (m_classMethod)
				delete m_classMethod;
			m_classMethod = new ClassMethod<Class, Method>(c, method); // that bad
		}

		void operator() () {
			m_classMethod->Call();
		}

		void operator() (const IEvent* const e) {
			m_classMethod->Call(e);
		}
	};
}