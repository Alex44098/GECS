#pragma once

#include "Facade.h"
#include "IEventCollection.h"

namespace GECS {
	namespace Event {
		template<class T>
		class EventCollection : public IEventCollection {
			std::list<IClassMethod*> m_eventMethodsList;

		public:

			EventCollection()
			{}

			virtual ~EventCollection()
			{
				this->m_eventMethodsList.clear();
			}

			void Call(const IEvent* event) override {
				for (IClassMethod* method : this->m_eventMethodsList) {
					method->Call(event);
				}
			}

			virtual void AddMethod(IClassMethod* method) {
				for (IClassMethod* eventMethod : this->m_eventMethodsList)
					if (eventMethod == method)
						return;

				this->m_eventMethodsList.push_back(method);
			}

			virtual void RemoveMethod(IClassMethod* method) {
				for (IClassMethod* eventMethod : this->m_eventMethodsList) {
					if (method->operator==(eventMethod)) {
						this->m_eventMethodsList.remove(eventMethod);
						delete eventMethod;

						return;
					}
				}
			}
		};
	}
}