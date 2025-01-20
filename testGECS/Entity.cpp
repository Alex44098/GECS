#include "pch.h"
#include "CppUnitTest.h"

#include "EntityManager.h"
#include "IEntity.h"
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
			Assert::AreEqual(1, (int)en1->GetEntityTypeId());
			Assert::AreEqual(2, (int)en2->GetEntityTypeId());

			em.ReleaseEntity(eh1);
			em.ReleaseEntity(eh2);
			em.DestroyReleasedEntities();
		}
	};
}