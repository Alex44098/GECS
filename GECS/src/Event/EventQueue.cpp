#include "Event/EventQueue.h"

#include "Memory/GlobalMemoryManager.h"

namespace GECS {
	namespace Event {
		EventQueue::EventQueue() {
			this->m_eventAllocator = new Memory::LinearAllocator(GECS_EVENT_BUFFER_MEMORY_SIZE, Memory::g_globalMemManager->Allocate(GECS_EVENT_BUFFER_MEMORY_SIZE));
			this->m_eventsQueue.reserve(512);
		}

		EventQueue::~EventQueue() {
			for (auto p : this->m_eventsById) {
				delete p.second;
				p.second = nullptr;
			}

			this->m_eventsById.clear();

			Memory::g_globalMemManager->Free(this->m_eventAllocator->GetAddressBegining());

			delete this->m_eventAllocator;
			this->m_eventAllocator = nullptr;
		}

		void EventQueue::ProcessEvents() {
			// It is important to understand that after processing an event, new events may appear.
			// Therefore, it is important to keep in mind that the event buffer may change.

			size_t currentIndex = 0;
			size_t endIndex = this->m_eventsQueue.size();

			while (currentIndex < endIndex) {
				IEvent* event = this->m_eventsQueue[currentIndex++];

				auto eventCollection = this->m_eventsById.find(event->GetEventTypeId());
				if (eventCollection == this->m_eventsById.end())
					continue;

				eventCollection->second->Call(event);
				endIndex = this->m_eventsQueue.size();
			}
			this->ClearEventBuffer();
		}
	}
}