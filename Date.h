// Final Project Milestone 1
// Date.h
// Version 1.0
// March 10, 2018
// Weisi Kong 125400176 wkong10@myseneca.ca
// Description
// Header file for Date.cpp 
// Defines AMA namespace, Date class, helper operators << and >>
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H

#define NO_ERROR 0 //No error - the date is valid
#define CIN_FAILED 1 //istream failed on information entry
#define YEAR_ERROR 2 //Year value is invalid
#define MON_ERROR 3 //Month value is invalid
#define DAY_ERROR 4 //Day value is invalid

#include <iostream>

namespace AMA {
	// limits on the years to be considered acceptable
	const int min_year = 2000;
	const int max_year = 2030;

	// declares the Date class
	//
	class Date {
		int year;
		int month;
		int day;
		int comparator;
		int mdays(int, int)const;
		void errCode(int errorCode);
		int errorState;
		bool isEmpty() const;

	public:
		// no-argument constructor declaration
		//
		Date();

		// three-argument constructor declaration
		//
		Date(int, int, int);

		// operator == declaration
		//
		bool operator==(const Date& rhs) const;

		// operator != declaration
		//
		bool operator!=(const Date& rhs) const;

		// operator < declaration
		//
		bool operator<(const Date& rhs) const;

		// operator > declaration
		//
		bool operator>(const Date& rhs) const;

		// operator <= declaration
		//
		bool operator<=(const Date& rhs) const;

		// operator >= declaration
		//
		bool operator>=(const Date& rhs) const;

		// returns the error state as an error code value
		//
		int errCode() const;

		// returns true if the error state is not NO_ERROR
		//
		bool bad() const;

		// reads the date from the console
		//
		std::istream& read(std::istream& istr);

		// writes the date to and ostream object
		//
		std::ostream& write(std::ostream& ostr) const;
	};

	// works with an ostream object to print a date to the console
	//
	std::ostream& operator<<(std::ostream&, const Date&);

	// works with an istream object to read a date from the console
	//
	std::istream& operator>>(std::istream& is, Date& date);

}
#endif