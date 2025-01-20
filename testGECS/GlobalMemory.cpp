#include "pch.h"
#include "CppUnitTest.h"

#include "Facade.h"
#include "Memory/GlobalMemoryManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS {
	TEST_CLASS(GlobalMemoryTest)
	{
		TEST_METHOD(MemoryAllocation) {
			uptr address = Memory::m_globalMemManager->Allocate(sizeof(u8));

			f32* f = (f32*)address;
			*f = 5.0f;
			Assert::AreEqual(*f, 5.0f);

			Memory::m_globalMemManager->Free(address);

			address = Memory::m_globalMemManager->Allocate(sizeof(f32));
			Assert::AreEqual(*f, 5.0f);

			f = (f32*)address;
			*f = 10.0f;
			Assert::AreEqual(*f, 10.0f);

			Memory::m_globalMemManager->Free(address);
		}

		TEST_METHOD(MemoryMultipleAllocation) {
			uptr addr1 = Memory::m_globalMemManager->Allocate(sizeof(u8));
			uptr addr2 = Memory::m_globalMemManager->Allocate(sizeof(f32));

			u8* uint8 = (u8*)addr1;
			f32* f = (f32*)addr2;

			*uint8 = 100;
			*f = 36.6f;

			Assert::AreEqual(*uint8, (u8)100);
			Assert::AreEqual(*f, 36.6f);

			Memory::m_globalMemManager->Free(addr1);

			uptr addr3 = Memory::m_globalMemManager->Allocate(sizeof(u64));
			Assert::AreNotEqual(addr1, addr3);

			u64* uint64 = (u64*)addr3;

			*uint64 = 1000;

			Assert::AreEqual(*uint8, (u8)100);
			Assert::AreEqual(*f, 36.6f);
			Assert::AreEqual(*uint64, (u64)1000);

			Memory::m_globalMemManager->Free(addr2);
			Memory::m_globalMemManager->Free(addr3);

			uptr addr4 = Memory::m_globalMemManager->Allocate(sizeof(u8));
			Assert::AreEqual(addr1, addr4);

			Memory::m_globalMemManager->Free(addr4);
		}
	};
}