//!
//! @file 			BasicTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-09-18
//! @last-modified 	2014-09-18
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <cstdint>	// uint32_t, e.t.c

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MSmartPtrApi.hpp"

using namespace MbeddedNinja;

namespace MSmartPtrTestsNs
{

	MTEST(BasicTest)
	{
		uint32_t * myInt = new uint32_t(42);

		MSmartPtr<uint32_t> mySmartPtr1(myInt);

		CHECK_EQUAL((*mySmartPtr1.count), 1);

		MSmartPtr<uint32_t> mySmartPtr2(mySmartPtr1);

		CHECK_EQUAL((*mySmartPtr2.count), 2);

	}

	MTEST(ScopeTest)
	{
		MSmartPtr<uint32_t> mySmartPtr2;

		{

			uint32_t * myInt = new uint32_t(42);

			MSmartPtr<uint32_t> mySmartPtr1(myInt);

			CHECK_EQUAL((*mySmartPtr1.count), 1);

			mySmartPtr2 = mySmartPtr1;

		}

		CHECK_EQUAL(*(mySmartPtr2.count), 1);

		CHECK_EQUAL(*mySmartPtr2, 42);

	}


} // namespace MSmartPtrTestsNs
