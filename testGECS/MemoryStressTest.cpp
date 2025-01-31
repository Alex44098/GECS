#include "pch.h"
#include "CppUnitTest.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"

#include "Memory/PoolAllocator.h"

#include "Facade.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS {
	TEST_CLASS(MemoryStressTest)
	{
		struct GameComponent : public Component<GameComponent> {
			int foo;
		public:
			GameComponent(int foo) {
				this->foo = foo;
			}
			~GameComponent() {}

			int GetFoo() {
				return foo;
			}
		};

		struct GameStruct1MB : public Entity<GameStruct1MB> {
			char arr[1048552]; // for sizeof 1MB
		};

		struct GameStruct1KB : public Entity<GameStruct1MB> {
			char arr[2024]; // for sizeof 2KB
		};

		struct GameStructWithComp : public Entity<GameStructWithComp> {
			GameStructWithComp() {
				AddComponent<GameComponent>(10);
			}

			~GameStructWithComp()
			{
				RemoveComponent<GameComponent>();
			}
		};

		struct GameStruct : public Entity<GameStruct> {
			int x;

			GameStruct() {
				this->x = 10;
			}

			~GameStruct()
			{}
		};

		TEST_METHOD(PoolAllocator) {
			const size_t allocSize = sizeof(GameStructWithComp) * 2048 + alignof(GameStructWithComp);

			Memory::PoolAllocator* poolAll = new Memory::PoolAllocator(allocSize, Memory::g_globalMemManager->Allocate(allocSize), sizeof(GameStructWithComp), alignof(GameStructWithComp));
			ComponentManager* cm = new ComponentManager();

			const size_t numEntities = 2048;
			GameStructWithComp* gsArr[numEntities];

			for (int i = 0; i < numEntities; i++) {
				uptr address = poolAll->Allocate(sizeof(GameStructWithComp), alignof(GameStructWithComp));
				Assert::IsTrue(0 != address);
				((GameStructWithComp*)address)->m_componentManagerSingleton = cm;
				((GameStructWithComp*)address)->m_handle = Handle(i, 1);
				gsArr[i] = new(reinterpret_cast<void*>(address))GameStructWithComp();
			}

			for (int i = 0; i < numEntities; i++)
				Assert::AreEqual(10, cm->GetComponent<GameComponent>(gsArr[i]->GetEntityHandle())->foo);
			
			for (int i = 0; i < numEntities; i++) {
				((IEntity*)gsArr[i])->~IEntity();
				poolAll->Free(reinterpret_cast<uptr>(gsArr[i]));
			}

			Memory::g_globalMemManager->Free(poolAll->GetAddressBegining());

			delete cm;
			delete poolAll;
		}

		TEST_METHOD(EntityAllocation) {
			GameStruct1MB gs1mb;
			GameStruct1KB gs1kb;

			Assert::AreEqual((size_t)1048576, sizeof(gs1mb));
			Assert::AreEqual((size_t)2048, sizeof(gs1kb));

			ComponentManager* cm = new ComponentManager();
			EntityManager* em = new EntityManager(cm);
			
			//Handle eh1mb = em->CreateEntity<GameStruct1MB>(); // attempt of allocating 1 GB memory (pool allocator for 1024 objects (1MB))
			// ^^^^^^^^^^^^^^^^^^^^
			// AN ASSERT IS RAISED HERE

			const size_t numEntities = 1024;
			Handle eh[numEntities];

			// create entities
			for (int i = 0; i < numEntities; i++)
				eh[i] = em->CreateEntity<GameStructWithComp>();

			// check all entities
			for (int i = 0; i < numEntities; i++)
				Assert::AreEqual(cm->GetComponent<GameComponent>(eh[i])->GetFoo(), 10);

			// release 25% of entities
			for (int i = numEntities / 4; i < numEntities / 2; i++)
				em->ReleaseEntity(eh[i]);
			em->DestroyReleasedEntities();

			// create 25% of entities
			for (int i = numEntities / 4; i < numEntities / 2; i++)
				eh[i] = em->CreateEntity<GameStructWithComp>();

			// check all entities
			for (int i = 0; i < numEntities; i++)
				Assert::AreEqual(cm->GetComponent<GameComponent>(eh[i])->GetFoo(), 10);

			// release all entities
			for (int i = 0; i < numEntities; i++)
				em->ReleaseEntity(eh[i]);

			em->DestroyReleasedEntities();

			delete em;
			delete cm;
		}
	};
}