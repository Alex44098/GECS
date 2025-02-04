#pragma once

#pragma warning(disable: 4251)

#include "Facade.h"
#include "Delegate/ClassMethod.h"
#include "Event/EventCollection.h"

#include "Memory/LinearAllocator.h"

namespace GECS {
	namespace Event {
		class GECS_API EventQueue {
			Memory::LinearAllocator* m_eventAllocator;

			std::unordered_map<type_id, IEventCollection*> m_eventsById;

			std::vector<IEvent*> m_eventsQueue;

			inline void ClearEventBuffer() {
				this->m_eventAllocator->Clear();
				this->m_eventsQueue.clear();
			}

		public:

			EventQueue();
			~EventQueue();

			template<class Event, class Class>
			inline void AddEventHandler(Class* c, void(Class::* Method)(const IEvent* const)) {
				IClassMethod* classMethod = new ClassMethod<Class, void(Class::*)(const IEvent* const)>(c, Method);

				type_id eventTypeId = Event::EVENT_TYPE_ID;

				auto eventCollection = this->m_eventsById.find(eventTypeId);

				if (eventCollection == this->m_eventsById.end()) {
					EventCollection<Event>* newEventCollection = new EventCollection<Event>();
					newEventCollection->AddMethod(classMethod);

					std::pair<type_id, IEventCollection*> eventTypeCollectionPair;
					eventTypeCollectionPair.first = eventTypeId;
					eventTypeCollectionPair.second = newEventCollection;

					this->m_eventsById.insert(eventTypeCollectionPair);
				}
				else {
					this->m_eventsById[eventTypeId]->AddMethod(classMethod);
				}
			}

			template<class Event, class Class>
			inline void RemoveEventHandler(Class* c, void(Class::* Method)(const IEvent* const)) {
				ClassMethod<Class, void(Class::*)(const IEvent* const)> classMethod(c, Method);

				type_id eventTypeId = Event::EVENT_TYPE_ID;

				auto eventCollection = this->m_eventsById.find(eventTypeId);
				if (eventCollection != this->m_eventsById.end())
					this->m_eventsById[eventTypeId]->RemoveMethod(&classMethod);
			}

			template<class Event, class... Arguments>
			void Send(Arguments&&... args) {
				uptr address = m_eventAllocator->Allocate(sizeof(Event), alignof(Event));

				assert(address != 0 && "EventHandler: address not allocated");

				this->m_eventsQueue.push_back(new (reinterpret_cast<void*>(address))Event(std::forward<Arguments>(args)...));
			}

			void ProcessEvents();
		};
	}
}