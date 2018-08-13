#pragma once
// Final Project Milestone 2 - ErrorState Class
// ErrorState.h
// Date	2018-03-22
// Author	Weisi Kong
// Description: The ErrorState class manages the error state of client code and encapsulates the last error message.

#include <iostream>

// define namespace AMA
//
namespace AMA {
	// declare class ErrorState
	//
	class ErrorState {
		char* msg;

	public:
		// a constructor that receives a string as error message
		//
		explicit ErrorState(const char* errorMessage = nullptr);

		// prevents copying of any ErrorState object
		//
		ErrorState(const ErrorState& em) = delete;

		// prevents assignment of any ErrorState object to the current object
		//
		ErrorState& operator=(const ErrorState& em) = delete;

		// de-allocates any memory that has been dynamically allocated by the current object
		//
		virtual ~ErrorState();

		// clears any message stored by the current object and initializes the object to a safe empty state
		//
		void clear();

		// returns true if the current object is in a safe empty state
		//
		bool isClear() const;

		// stores a copy of the C-style string pointed to by str
		//
		void message(const char* str);

		//  returns the address of the message stored in the current object
		//
		const char* message() const;

		// copies an error string into the current object
		//
		void copyError(const char* str);

		// returns the error message stored in ErrorState
		//
		const char* get() const;

	};

	// sends an ErrorState message, if one exists, to an std::ostream
	// object and returns a reference to the std::ostream object
	//
	std::ostream& operator<<( std::ostream&, const ErrorState&);
}
