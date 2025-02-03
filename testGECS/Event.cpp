#include "pch.h"
#include "CppUnitTest.h"

#include "Facade.h"
#include "Event/Event.h"
#include "Event/EventQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS
{
	TEST_CLASS(EventTest)
	{
		Event::EventQueue* m_eventQueue;

		struct FooEvent : public Event::Event<FooEvent> {
			int x;

			FooEvent(int x) {
				this->x = x;
			}
		};

		struct FooEvent1 : public Event::Event<FooEvent1> {
			int x;

			FooEvent1(int x) {
				this->x = x;
			}
		};

		class GameObject {
			int x;

			void Foo(const Event::IEvent* e) {
				const FooEvent* event = reinterpret_cast<const FooEvent*>(e);

				this->x = event->x;
			}

		public:
			GameObject(Event::EventQueue* m_eventQueue) {
				m_eventQueue->AddEventHandler<FooEvent>(this, &GameObject::Foo);
				this->x = 0;
			}
			~GameObject() {
				
			}

			void RemoveEvent(Event::EventQueue* m_eventQueue) {
				m_eventQueue->RemoveEventHandler<FooEvent>(this, &GameObject::Foo);
			}

			int GetX() {
				return this->x;
			}
		};

		class GameObject1 {
			int x;
			Event::EventQueue* m_eventQueue;

			void Foo(const Event::IEvent* e) {
				const FooEvent1* event = reinterpret_cast<const FooEvent1*>(e);

				this->x = event->x;
			}

		public:
			GameObject1(Event::EventQueue* m_eventQueue) {
				this->m_eventQueue = m_eventQueue;
				m_eventQueue->AddEventHandler<FooEvent1>(this, &GameObject1::Foo);
				this->x = 0;
			}
			~GameObject1() {
				m_eventQueue->RemoveEventHandler<FooEvent1>(this, &GameObject1::Foo);
			}

			int GetX() {
				return this->x;
			}
		};

		TEST_METHOD(EventCreation) {
			Assert::AreEqual(0, (int)FooEvent::EVENT_TYPE_ID);
			Assert::AreEqual(1, (int)FooEvent1::EVENT_TYPE_ID);

			FooEvent ev(0);

			Assert::AreEqual(FooEvent::EVENT_TYPE_ID, ev.GetEventTypeId());
		}

		TEST_METHOD(EventCalling) {
			m_eventQueue = new Event::EventQueue();

			GameObject* go1 = new GameObject(m_eventQueue);
			GameObject* go2 = new GameObject(m_eventQueue);
			GameObject1* go3 = new GameObject1(m_eventQueue);

			m_eventQueue->Send<FooEvent>(5);
			m_eventQueue->Send<FooEvent1>(10);
			m_eventQueue->ProcessEvents();

			Assert::AreEqual(5, go1->GetX());
			Assert::AreEqual(5, go2->GetX());
			Assert::AreEqual(10, go3->GetX());

			go2->RemoveEvent(m_eventQueue);

			m_eventQueue->Send<FooEvent>(100);
			m_eventQueue->ProcessEvents();

			Assert::AreEqual(100, go1->GetX());
			
			Assert::AreEqual(5, go2->GetX());

			delete go1;
			delete go2;
			delete go3;

			delete m_eventQueue;
		}
	};
}