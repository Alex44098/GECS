#include "pch.h"
#include "CppUnitTest.h"

#include "SystemManager.h"
#include "System.h"
#include "ISystem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS
{
	TEST_CLASS(SystemTest)
	{
		class GameSystem1 : public System<GameSystem1> {
		public:
			GameSystem1() {
			};
			virtual ~GameSystem1() {};
		};

		class GameSystem2 : public System<GameSystem2> {
		public:
			GameSystem2() {
			};
			virtual ~GameSystem2() {};
		};

		class GameSystem3 : public System<GameSystem3> {
		public:
			GameSystem3() {
			};
			virtual ~GameSystem3() {};
		};

		class GameSystem4 : public System<GameSystem4> {
		public:
			GameSystem4() {
			};
			virtual ~GameSystem4() {};
		};

		class GameSystem5 : public System<GameSystem5> {
		public:
			GameSystem5() {
			};
			virtual ~GameSystem5() {};
		};

		class GameSystem6 : public System<GameSystem6> {
		public:
			GameSystem6() {
			};
			virtual ~GameSystem6() {};
		};

		class GameSystem7 : public System<GameSystem7> {
			int foo;
		public:
			GameSystem7() {
				this->foo = 0;
			};
			virtual ~GameSystem7() {};

			virtual void Update(f32 delta) {
				this->foo++;
			}

			int GetFoo() {
				return this->foo;
			}
		};

		class GameSystem8 : public System<GameSystem8> {
		public:
			GameSystem8() {
			};
			virtual ~GameSystem8() {};
		};

		class GameSystem9 : public System<GameSystem9> {
		public:
			GameSystem9() {
			};
			virtual ~GameSystem9() {};
		};

		class GameSystem10 : public System<GameSystem10> {
		public:
			GameSystem10() {
			};
			virtual ~GameSystem10() {};
		};
		TEST_METHOD(SystemCreation) {
			SystemManager* sm = new SystemManager();

			GameSystem7* gs = sm->AddSystem<GameSystem7>();

			gs->Update(0.f);

			sm->Update(0.f);

			gs->Update(0.f);

			Assert::AreEqual(3, gs->GetFoo());

			sm->SetSystemPriority<GameSystem7>(HIGH_SYSTEM_PRIORITY);

			Assert::AreEqual(HIGH_SYSTEM_PRIORITY, (int)gs->m_priority);

			sm->DisableSystem<GameSystem7>();

			Assert::AreEqual(false, gs->m_enabled);

			delete sm;
		}

		TEST_METHOD(SystemOrder) {
			SystemManager* sm = new SystemManager();

			GameSystem1* gs1 = sm->AddSystem<GameSystem1>();
			GameSystem2* gs2 = sm->AddSystem<GameSystem2>();
			GameSystem3* gs3 = sm->AddSystem<GameSystem3>();
			GameSystem4* gs4 = sm->AddSystem<GameSystem4>();
			GameSystem5* gs5 = sm->AddSystem<GameSystem5>();
			GameSystem6* gs6 = sm->AddSystem<GameSystem6>();
			GameSystem7* gs7 = sm->AddSystem<GameSystem7>();
			GameSystem8* gs8 = sm->AddSystem<GameSystem8>();
			GameSystem9* gs9 = sm->AddSystem<GameSystem9>();
			GameSystem10* gs10 = sm->AddSystem<GameSystem10>();

			sm->SetSystemPriority<GameSystem7>(HIGHEST_SYSTEM_PRIORITY);
			
			Assert::AreEqual(1, (int)gs2->GetSystemTypeId());
			Assert::AreEqual(5, (int)gs6->GetSystemTypeId());

			gs9->AddDependency(gs2);
			gs6->AddDependency(gs2);

			gs5->AddDependency(gs2);
			gs5->AddDependency(gs6);

			gs4->AddDependency(gs5);
			gs8->AddDependency(gs7);

			sm->RebuildSystemsOrder();

			sm->Update(0.f);
			sm->Update(0.f);
			sm->Update(0.f);

			Assert::AreEqual(gs7->GetFoo(), 3);

			delete sm;
		}
	};
}