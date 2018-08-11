// Final Project Milestone 1
// Date.cpp
// Version 1.0
// March 10, 2018
// Weisi Kong 125400176 wkong10@myseneca.ca
// Description
// Implementation file for Date
// Defines member functions for Date class and helper functions << and >>
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include "Date.h"

namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	// sets error state
	//
	void Date::errCode(int errorCode) {
		errorState = errorCode;
	}

	// no-argument constructor
	//
	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		comparator = 0;
		errCode(NO_ERROR);
	}

	// three-argument constructor
	//
	Date::Date(int year_, int month_, int day_) {
		//validates the year
		if (year_ > max_year || year_ < min_year) {
			errCode(YEAR_ERROR);
		}

		//validates the month
		if (month_ < 1 || month_ > 12) {
			errCode(MON_ERROR);
		}

		//Validates the day
		if (day_ < 1 || day_ > mdays(month_, year_)) {
			errCode(DAY_ERROR);
		}

		if (errorState != YEAR_ERROR && errorState != MON_ERROR && errorState != DAY_ERROR) {
			year = year_;
			month = month_;
			day = day_;
			comparator = year * 372 + month * 13 + day;
			errCode(NO_ERROR);
		}
		else {
			*this = Date();
			comparator = 0;
			errCode(NO_ERROR);
		}
	}

	// determine if the current object is in empty state
	//
	bool Date::isEmpty() const {
		return (year == 0);
	}


	// operator == definition
	//
	bool Date::operator==(const Date& rhs) const {
		if (!isEmpty() && !rhs.isEmpty()) {
			return comparator == rhs.comparator;
		}
		else {
			return false;
		}
	}

	// operator !- definition
	//
	bool Date::operator!=(const Date& rhs) const {
		if (!isEmpty() && !rhs.isEmpty()) {
			return comparator != rhs.comparator;
		}
		else {
			return false;
		}
	}

	// operator < definition
	//
	bool Date::operator<(const Date& rhs) const {
		if (!isEmpty() && !rhs.isEmpty()) {
			return comparator < rhs.comparator;
		}
		else {
			return false;
		}
	}

	// operator > definition
	//
	bool Date::operator>(const Date& rhs) const {
		if (!isEmpty() && !rhs.isEmpty()) {
			return comparator > rhs.comparator;
		}
		else {
			return false;
		}
	}

	// operator <= definition
	//
	bool Date::operator<=(const Date& rhs) const {
		if (!isEmpty() && !rhs.isEmpty()) {
			return comparator <= rhs.comparator;
		}
		else {
			return false;
		}
	}

	// operator >= definition
	//
	bool Date::operator>=(const Date& rhs) const {
		if (!isEmpty() && !rhs.isEmpty()) {
			return comparator >= rhs.comparator;
		}
		else {
			return false;
		}
	}

	// returns the error state as an error code value
	//
	int Date::errCode() const {
		return errorState;
	}


	// returns true if the error state is not NO_ERROR
	//
	bool Date::bad() const {
		return (errorState != NO_ERROR);
	}

	// reads the date from the console
	//
	std::istream& Date::read(std::istream& istr) {
		int year_;
		int mon_;
		int day_;
		istr >> year_;
		if (istr.fail()) {
			errCode(CIN_FAILED);
			return istr;
		}
		istr.ignore();
		istr >> mon_;
		if (istr.fail()) {
			errCode(CIN_FAILED);
			return istr;
		}
		istr.ignore();
		istr >> day_;
		if (istr.fail()) {
			errCode(CIN_FAILED);
			return istr;
		}
		else {
			// validates the year
			if (year_ > max_year || year_ < min_year) {
				errCode(YEAR_ERROR);
				return istr;
			}

			//validates the month
			if (mon_ < 1 || mon_ > 12) {
				errCode(MON_ERROR);
				return istr;
			}

			//Validates the day
			if (day_ < 1 || day_ > mdays(mon_, year_)) {
				errCode(DAY_ERROR);
				return istr;
			}
			Date temp(year_, mon_, day_);
			if (temp.day != 0) {
				*this = temp;
			}
			return istr;
		}
	}

	// writes the date to and ostream object
	//
	std::ostream& Date::write(std::ostream& ostr) const {
		if (errCode() == NO_ERROR) {
			ostr << year << "/";
			ostr.setf(std::ios::fixed);
			ostr.setf(std::ios::right);
			ostr.fill('0');
			ostr.width(2);
			ostr << month << "/";
			ostr.width(2);
			ostr << day;
			ostr.unsetf(std::ios::fixed);
			ostr.unsetf(std::ios::right);
			ostr.fill(' ');
		}
		return ostr;
	}

	// works with an ostream object to print a date to the console
	//
	std::ostream& operator<<(std::ostream& os, const Date& date) {
		date.write(os);
		return os;
	}

	// works with an istream object to read a date from the console
	//
	std::istream& operator>>(std::istream& is, Date& date) {
		date.read(is);
		return is;
	}

}

