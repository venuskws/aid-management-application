// Final Project Milestone 2 - ErrorState Class
// ErrorState.cpp
// Date	2018-03-22
// Author	Weisi Kong 125400176 wkong10@myseneca.ca
// Description: The ErrorState class manages the error state of client code and encapsulates the last error message.


#include <iostream>
#include <cstring>
#include "ErrorState.h"

// define namespace AMA
//
namespace AMA {

	// a constructor that receives a string as error message
	//
	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr) {
			msg = nullptr;
		}
		else if (errorMessage[0] != '\0') {
			copyError(errorMessage);
		}
		else {
			clear();
		}
	}

	// This function de-allocates any memory that has been dynamically allocated by the current object
	//
	ErrorState::~ErrorState() {
		clear();
	}

	// clears any message stored by the current object and initializes the object to a safe empty state
	//
	void ErrorState::clear() {
		delete msg;
		msg = nullptr;
	}

	// returns true if the current object is in a safe empty state
	//
	bool ErrorState::isClear() const {
		return msg == nullptr;
	}

	// stores a copy of the C-style string pointed to by str
	//
	void ErrorState::message(const char* str) {
		if (msg != nullptr) {
			clear();
		}
		copyError(str);
	}

	// copies an error string into the current object
	//
	void ErrorState::copyError(const char* str) {
		if (str != nullptr) {
			int nc = strlen(str) + 1;
			if (nc > 0) {
				msg = new char[nc];
				for (int i = 0; i < nc; i++) {
					msg[i] = str[i];
				}
			}
			else {
				clear();
			}
		}
		else {
			clear();
		}
	}

	//  returns the address of the message stored in the current object
	//
	const char* ErrorState::message() const {
		return msg;
	}

	// sends an ErrorState message, if one exists, to an std::ostream
	// object and returns a reference to the std::ostream object
	//
	std::ostream& operator<<(std::ostream& os, const ErrorState& err) {
		if (!err.isClear()) {
			os << err.get();
		}
		return os;
	}

	// returns the error message stored in ErrorState
	//
	const char* ErrorState::get() const {
		return msg;
	}

}