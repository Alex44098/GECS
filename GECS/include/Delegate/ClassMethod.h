#pragma once

#include "Event/IEvent.h"
#include "Delegate/IClassMethod.h"

namespace GECS {
	template<class Class, class Method>
	class ClassMethod : public IClassMethod {};

	// specialization - without arguments
	template<class Class>
	class ClassMethod<Class, void(Class::*)(void)> : public IClassMethod {

		typedef void(Class::* Method)(void);

		Class* m_class;
		Method m_method;

	public:

		ClassMethod(Class* c, Method method) :
			m_class(c),
			m_method(method)
		{}

		virtual inline void Call() override {
			(m_class->*m_method)();
		}
	};

	// specialization - with IEvent argument
	template<class Class>
	class ClassMethod<Class, void(Class::*)(const Event::IEvent* const)> : public IClassMethod {
		
		typedef void(Class::* Method)(const Event::IEvent* const);

		Class* m_class;
		Method m_method;

	public:

		ClassMethod(Class* c, Method method) :
			m_class(c),
			m_method(method)
		{}
		
		virtual inline void Call(const Event::IEvent* const e) override {
			(m_class->*m_method)(e);
		}
	};
}