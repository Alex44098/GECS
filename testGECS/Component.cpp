#include "pch.h"
#include "CppUnitTest.h"

#include "ComponentManager.h"
#include "EntityManager.h"

#include "Component.h"
#include "Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<GECS::Handle>(const GECS::Handle& h) { RETURN_WIDE_STRING(h); }
		}
	}
}

namespace GECS
{
	TEST_CLASS(ComponentTest)
	{
		class GameComponent : public Component<GameComponent> {
		public:
			int foo;
			GameComponent(int foo) {
				this->foo = foo;
			}
			virtual ~GameComponent() {}

			int GetFoo() {
				return foo;
			}
		};

		class GameObject : public Entity<GameObject> {
		public:
			GameObject() {
				AddComponent<GameComponent>(10);
			}
			virtual ~GameObject() {}
		};

		TEST_METHOD(ComponentCreation) {
			Assert::AreEqual(0, (int)GameComponent::COMPONENT_TYPE_ID);
			
			ComponentManager* cm = new ComponentManager();
			EntityManager* em = new EntityManager(cm);

			Handle eh = em->CreateEntity<GameObject>();

			IEntity* en = em->GetEntity(eh);

			Assert::AreEqual(en->GetEntityHandle(), eh);

			Assert::AreEqual(cm->GetComponent<GameComponent>(eh)->GetFoo(), 10);

			cm->GetComponent<GameComponent>(eh)->foo = 100;

			Assert::AreEqual(cm->GetComponent<GameComponent>(eh)->GetFoo(), 100);

			em->ReleaseEntity(eh);
			em->DestroyReleasedEntities();

			delete em;
			delete cm;
		}

		TEST_METHOD(ComponentRemoving) {
			ComponentManager* cm = new ComponentManager();
			EntityManager* em = new EntityManager(cm);

			Handle eh = em->CreateEntity<GameObject>();

			IEntity* en = em->GetEntity(eh);

			en->RemoveComponent<GameComponent>();

			Assert::AreEqual((void*)cm->GetComponent<GameComponent>(eh), (void*)nullptr);

			en->AddComponent<GameComponent>(5);

			Assert::AreNotEqual((void*)cm->GetComponent<GameComponent>(eh), (void*)nullptr);
			Assert::AreEqual(cm->GetComponent<GameComponent>(eh)->GetFoo(), 5);

			for (auto it = cm->begin<GameComponent>(); it != cm->end<GameComponent>(); ++it) {
				Assert::AreEqual(it->GetFoo(), 5);
			}

			em->ReleaseEntity(eh);
			em->DestroyReleasedEntities();

			delete em;
			delete cm;
		}

		TEST_METHOD(ComponentTypeId) {
			class GameComponent1 : public Component<GameComponent1> {
			public:
				GameComponent1() {}
				virtual ~GameComponent1() {}
			};

			class GameComponent2 : public Component<GameComponent2> {
			public:
				GameComponent2() {}
				virtual ~GameComponent2() {}
			};

			Assert::AreEqual(5, (int)Identifier::TypeIDCounter<IComponent>::GetNumTypes());

			Assert::AreEqual(1, (int)GameComponent1::COMPONENT_TYPE_ID);
			Assert::AreEqual(2, (int)GameComponent2::COMPONENT_TYPE_ID);
		}
	};
}