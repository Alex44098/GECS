#include "IComponent.h"

namespace GECS {
	IComponent::IComponent() :
		m_entityOwner(Handle::INVALID_HANDLE)
	{}

	IComponent::~IComponent()
	{}
}