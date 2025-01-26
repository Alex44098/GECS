#include "pch.h"
#include "CppUnitTest.h"

#include "Event/Event.h"
#include "Event/EventQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS
{
	TEST_CLASS(EventTest)
	{	
		struct FooEvent : public Event<FooEvent> {
			int x;

			FooEvent(int x) {
				this->x = x;
			}
		};

		struct FooEvent1 : public Event<FooEvent1> {
			int x;

			FooEvent1(int x) {
				this->x = x;
			}
		};

		class GameObject {
			int x;
		public:
			GameObject(EventQueue* m_eventQueue) {
				m_eventQueue->AddEventHandler<FooEvent>(this, &GameObject::Foo);
			}
			~GameObject() {}

			void Foo(const IEvent* e) {
				const FooEvent* event = reinterpret_cast<const FooEvent*>(e);

				this->x = event->x;
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
			EventQueue* eq = new EventQueue();

			GameObject go(eq);

			eq->Send<FooEvent>(5);

			eq->ProcessEvents();

			Assert::AreEqual(5, go.GetX());

			delete eq;
		}
	};
}