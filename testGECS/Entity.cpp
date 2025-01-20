#include "pch.h"
#include "CppUnitTest.h"

#include "EntityManager.h"
#include "IEntity.h"
#include "Entity.h"
#include "Facade.h"

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
	TEST_CLASS(EntityTest)
	{
	public:

		TEST_METHOD(EntityCreation) {
			class GameObject : public Entity<GameObject> {
			public:
				GameObject() { }
				virtual ~GameObject() {}
			};

			EntityManager em;
			Handle eh = em.CreateEntity<GameObject>();

			IEntity* en = em.GetEntity(eh);
			
			Assert::AreEqual(en->GetEntityHandle(), eh);

			em.ReleaseEntity(eh);
			em.DestroyReleasedEntities();
		}

		TEST_METHOD(EntityCreationWithParams) {
			class GameObjectFoo : public Entity<GameObjectFoo> {
				int foo1, foo2;
			public:
				GameObjectFoo(int foo1, int foo2) {
					this->foo1 = foo1;
					this->foo2 = foo2;
				}
				virtual ~GameObjectFoo() {}

				int GetFoo1() {
					return this->foo1;
				}

				int GetFoo2() {
					return this->foo2;
				}
			};

			EntityManager em;
			Handle eh = em.CreateEntity<GameObjectFoo>(5, 10);

			GameObjectFoo* en = (GameObjectFoo*)em.GetEntity(eh);

			Assert::AreEqual(en->GetEntityHandle(), eh);
			Assert::AreEqual(en->GetFoo1(), 5);
			Assert::AreEqual(en->GetFoo2(), 10);

			em.ReleaseEntity(eh);
			em.DestroyReleasedEntities();
		}

		TEST_METHOD(EntityTypeId) {
			class GameObject1 : public Entity<GameObject1> {
			public:
				GameObject1() { }
				virtual ~GameObject1() {}
			};

			class GameObject2 : public Entity<GameObject2> {
			public:
				GameObject2() { }
				virtual ~GameObject2() {}
			};

			EntityManager em;
			Handle eh1 = em.CreateEntity<GameObject1>();
			Handle eh2 = em.CreateEntity<GameObject2>();

			IEntity* en1 = em.GetEntity(eh1);
			IEntity* en2 = em.GetEntity(eh2);

			Assert::AreNotEqual(en1->GetEntityTypeId(), en2->GetEntityTypeId());
			Assert::AreEqual(2, (int)en1->GetEntityTypeId());
			Assert::AreEqual(3, (int)en2->GetEntityTypeId());

			em.ReleaseEntity(eh1);
			em.ReleaseEntity(eh2);
			em.DestroyReleasedEntities();
		}
	};
}