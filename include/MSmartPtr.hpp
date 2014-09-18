//!
//! @file				MSmartPtr.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-09-18
//! @last-modified		2014-09-18
//! @brief
//! @details
//!						See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MSMART_PTR_MSMART_PTR_H
#define MSMART_PTR_MSMART_PTR_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	template < typename ObjT >
	class MSmartPtr;
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// uint8_t, uint32_t, e.t.c
#include <iostream>

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{

	template < typename ObjT >
	class MSmartPtr
	{	
		
		public:

		ObjT * ptrToObj;
		uint32_t * count;

		//======================================================================================//
		//==================================== PUBLIC METHODS ==================================//
		//======================================================================================//
					
		//! @brief		Default constructor.
		//! @details	ptrToOj cannot be const as we will delete this object if reference becomes 0.
		MSmartPtr(ObjT * ptrToObj) :
			count(nullptr)
		{
			this->ptrToObj = ptrToObj;
			this->count = new uint32_t;
			(*this->count)++;
		}

		//! @brief		Simplified constructor
		MSmartPtr() :
			ptrToObj(nullptr),
			count(nullptr)
		{
			// Create a pointer to count
			this->count = new uint32_t;
		}

		//! @brief		Copy constructor.
		MSmartPtr(const MSmartPtr<ObjT> & mSmartPtr) :
			ptrToObj(mSmartPtr.ptrToObj),	// Copy the pointer to the object
			count(mSmartPtr.count)					// Copy the count pointer
		{
			std::cout << "Copy constructor called." << std::endl;

			// Increment the count
			(*count)++;
		}

		~MSmartPtr()
		{
			std::cout << "Destructor called." << std::endl;

			// One less thing is referencing the object, so decrement the count
			(*count)--;

			// Check if this was the last reference!
			if((*count) == 0)
			{
				// Have to check, because pointer could of been constructed
				// with default "()" constructor and no object provided.
				if(this->ptrToObj != nullptr)
				{
					// No more thing reference the object, so delete the object
					delete this->ptrToObj;

					// Set to nullptr to be safe
					this->ptrToObj = nullptr;
				}

				delete this->count;

				this->count = nullptr;
			}
		}


		//======================================================================================//
		//============================ PUBLIC OPERATOR OVERLOAD DECLARATIONS ===================//
		//======================================================================================//

		//! @brief		Assignment operator
		MSmartPtr & operator= (MSmartPtr<ObjT> & mySmartPtr)
		{
			// First need to decrease existing count and check if 0
			(*this->count)--;
			if((*this->count) == 0)
			{
				// Have to check, because pointer could of been constructed
				// with default "()" constructor and no object provided.
				if(this->ptrToObj != nullptr)
				{
					// No more thing reference the object, so delete the object
					delete this->ptrToObj;

					// Set to nullptr to be safe
					this->ptrToObj = nullptr;
				}

				delete this->count;
				this->count = nullptr;
			}

			// Now we can copy across
			this->ptrToObj = mySmartPtr.ptrToObj;
			this->count = mySmartPtr.count;
			(*this->count)++;

			// Return reference
			return *this;
		}

		ObjT & operator* ()
		{
			return *(this->ptrToObj);
		}

		ObjT * operator-> ()
		{
			return this->ptrToObj;
		}

		//======================================================================================//
		//================================= PUBLIC VARIABLES ===================================//
		//======================================================================================//
				

				
		private:
						
			//======================================================================================//
			//=================================== PRIVATE METHODS ==================================//
			//======================================================================================//
			
			// none
			
			//======================================================================================//
			//================================== PRIVATE VARIABLES =================================//
			//======================================================================================//



		protected:

			//======================================================================================//
			//=================================== PROTECTED METHODS ================================//
			//======================================================================================//
			
			// none
			
			//======================================================================================//
			//================================== PROTECTED VARIABLES ===============================//
			//======================================================================================//

			// none
		
	}; // class MSmartPtr


} // namespace MbeddedNinja

#endif	// #ifndef MSMART_PTR_MSMART_PTR_H

// EOF
