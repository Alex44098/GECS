#include <memory>

#include "pch.h"
#include "CppUnitTest.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"

#include "Memory/PoolAllocator.h"

#include "Facade.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS {
	TEST_CLASS(MemoryPerformance)
	{
		struct GameStruct1KB {
			char arr[1024]; // for sizeof 1KB
		};

		const size_t count = 51200;
		const size_t allocSize = sizeof(GameStruct1KB) * count + alignof(GameStruct1KB);
		//Memory::PoolAllocator* poolAll = new Memory::PoolAllocator(allocSize, Memory::g_globalMemManager->Allocate(allocSize), sizeof(GameStruct1KB), alignof(GameStruct1KB));
		TEST_METHOD(GECSPoolAllocator) {
			Memory::PoolAllocator* poolAll = new Memory::PoolAllocator(allocSize, Memory::g_globalMemManager->Allocate(allocSize), sizeof(GameStruct1KB), alignof(GameStruct1KB));
			std::vector<GECS::uptr> arr;
			for (int i = 0; i < count; i++)
				arr.push_back(poolAll->Allocate(sizeof(GameStruct1KB), alignof(GameStruct1KB)));
			for (int i = 0; i < count; i++)
				poolAll->Free(arr[i]);

			delete poolAll;
		}

		TEST_METHOD(StandardAllocator) {
			std::vector<GameStruct1KB*> arr;
			for (int i = 0; i < count; i++) 
				arr.push_back(new GameStruct1KB());
			for (int i = 0; i < count; i++) 
				delete arr[i];
		}

		TEST_METHOD(STLAllocator) {
			std::allocator<GameStruct1KB> alloc;

			std::vector<GameStruct1KB*> arr;
			for (int i = 0; i < count; i++)
				arr.push_back(alloc.allocate(1));
			for (int i = 0; i < count; i++)
				alloc.deallocate(arr[i], 1);
		}
	};
}