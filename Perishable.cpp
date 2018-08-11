// Final Project Milestone 5 - Perishable Class
// Perishable.cpp
// Date	2018-04-11
// Weisi Kong 125400176 wkong10@myseneca.ca
// Description: Implementation for the Perishable class

#include "Perishable.h"

namespace AMA {
	// no-argument constructor
	//
	Perishable::Perishable() : Product('P') {
		expiryDate = Date();
	}

	//  This function stores a single file record for the current object
	//
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Product::store(file, false);
		file << ",";
		file << expiryDate;
		if (newLine) {
			file << '\n';
		}
		return file;
	}

	//  This function extracts the data fields for a single file record from the fstream object.
	//
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		file >> expiryDate;
		file.get();
		return file;
	}

	//calls its base class version passing as arguments a reference to the ostream object and the bool flag
	//
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		if (isClear()) {
			if (linear) {
				os << expiryDate;
			}
			else {
				os << std::endl;
				os << " Expiry date: ";
				os << expiryDate;
			}

		}
		return os;
	}

	//  This function populates the current object with the data extracted from the istream object
	//
	std::istream& Perishable::read(std::istream& is) {
		Product::read(is);
		Date tempDate;
		if (!is.fail()) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			is >> tempDate;
		}

		switch (tempDate.errCode()) {
		case CIN_FAILED:
			message("Invalid Date Entry");
			is.std::ios::setstate(std::ios::failbit);
			break;
		case YEAR_ERROR:
			message("Invalid Year in Date Entry");
			is.std::ios::setstate(std::ios::failbit);
			break;
		case MON_ERROR:
			message("Invalid Month in Date Entry");
			is.std::ios::setstate(std::ios::failbit);
			break;
		case DAY_ERROR:
			message("Invalid Day in Date Entry");
			is.std::ios::setstate(std::ios::failbit);
			break;
		default:
			expiryDate = tempDate; 
			setType('P');
		}

	return is;
	}

	// This query returns the expiry date for the perishable product
	//
	const Date& Perishable::expiry() const {
		return expiryDate;
	}





}