#include "pch.h"
#include "CppUnitTest.h"

#include "Facade.h"

#include "Handle/Handle.h"

#include "Entity.h"
#include "EntityManager.h"

#include "Component.h"

#include "Event/Event.h"
#include "Event/EventQueue.h"

#include "GECSMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS
{
	TEST_CLASS(GECSInstanceTest)
	{
		struct FooEvent : public Event::Event<FooEvent> {
			int x;

			FooEvent(int x) {
				this->x = x;
			}
		};

		class GameComponent : public Component<GameComponent> {
			int foo;
		public:
			GameComponent(int foo) {
				this->foo = foo;
			}
			virtual ~GameComponent() {}

			int GetFoo() {
				return foo;
			}
		};

		class GameObject : public Entity<GameObject> {
			int x;
			Event::EventQueue* m_eventQueue;

			void Foo(const Event::IEvent* e) {
				const FooEvent* event = reinterpret_cast<const FooEvent*>(e);

				this->x = event->x;
			}

		public:
			GameObject(Event::EventQueue* m_eventQueue) {
				this->m_eventQueue = m_eventQueue;
				this->m_eventQueue->AddEventHandler<FooEvent>(this, &GameObject::Foo);
				this->x = 0;

				AddComponent<GameComponent>(10);
			}
			~GameObject() {
				this->m_eventQueue->RemoveEventHandler<FooEvent>(this, &GameObject::Foo);
			}

			int GetX() {
				return this->x;
			}
		};

		TEST_METHOD(MainTest) {
			Assert::IsTrue(GECSInstance == nullptr);

			L_(linfo) << "Engine init.";

			Init();

			L_(linfo) << "Engine init.";

			Assert::IsTrue(GECSInstance != nullptr);

			Handle eh = GECSInstance->GetEntityManager()->CreateEntity<GameObject>(GECSInstance->GetEventQueue());

			Assert::AreEqual(10, GECSInstance->GetComponentManager()->GetComponent<GameComponent>(eh)->GetFoo());

			GECSInstance->GetEventQueue()->Send<FooEvent>(5);

			GECSInstance->Update(5.f);

			IEntity* en = GECSInstance->GetEntityManager()->GetEntity(eh);

			Assert::AreEqual(5, static_cast<GameObject*>(en)->GetX());

			Destroy();
		}
	};
}