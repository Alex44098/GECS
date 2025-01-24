#include "Delegate/Delegate.h"

namespace GECS {
	Delegate::Delegate() :
		m_classMethod(0)
	{}

	Delegate::~Delegate() {
		if (m_classMethod)
			delete m_classMethod;
	}
}