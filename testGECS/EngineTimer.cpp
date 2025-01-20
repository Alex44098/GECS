#include "pch.h"
#include "CppUnitTest.h"

#include "Utilities/EngineTimer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GECS
{
	using namespace Util;

	TEST_CLASS(EngineTimerTest)
	{
	public:
		
		TEST_METHOD(TimerTick)
		{
			EngineTimer t;

			Assert::AreEqual(t.GetTime(), 0.f);

			t.Tick(50.f);
			Assert::AreEqual(t.GetTime(), 50.f);

			t.Tick(100.f);
			t.Tick(1.f);
			Assert::AreEqual(t.GetTime(), 151.f);
		}
	};
}
