#pragma once

#include "Facade.h"
#include "IEventCollection.h"

namespace GECS {
	namespace Event {
		template<class T>
		class EventCollection : public IEventCollection {
			std::list<Delegate*> m_eventDelegateList;

		public:

			EventCollection()
			{}

			virtual ~EventCollection()
			{
				this->m_eventDelegateList.clear();
			}

			void Call(const IEvent* event) override {
				for (Delegate* delegate : this->m_eventDelegateList) {
					delegate(event);
				}
			}

			virtual void AddDelegate(const Delegate* delegate) {
				for (Delegate* eventDelegate : this->m_eventDelegateList)
					if (eventDelegate == delegate)
						return;

				this->m_eventDelegateList.push_back(delegate);
			}

			virtual void RemoveDelegate(Delegate* delegate) {
				for (Delegate* eventDelegate : this->m_eventDelegateList) {
					if (eventDelegate == delegate) {
						this->m_eventDelegateList.remove(delegate);

						delete delegate;
					}
				}
			}
		};
	}
}