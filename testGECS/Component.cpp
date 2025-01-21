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
		TEST_METHOD(ComponentCreation) {
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
			public:
				GameObject() {
					AddComponent<GameComponent>(10);
				}
				virtual ~GameObject() {}
			};

			Assert::AreEqual(0, (int)GameComponent::COMPONENT_TYPE_ID);

			ComponentManager* cm = new ComponentManager();
			EntityManager* em = new EntityManager(cm);

			Handle eh = em->CreateEntity<GameObject>();

			IEntity* en = em->GetEntity(eh);

			Assert::AreEqual(en->GetEntityHandle(), eh);

			Assert::AreEqual(cm->GetComponent<GameComponent>(eh)->GetFoo(), 10);

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

			Assert::AreEqual((int)Identifier::TypeIDCounter<IComponent>::GetNumTypes(), 3);

			Assert::AreEqual(1, (int)GameComponent1::COMPONENT_TYPE_ID);
			Assert::AreEqual(2, (int)GameComponent2::COMPONENT_TYPE_ID);
		}
	};
}