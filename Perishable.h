#pragma once
// Final Project Milestone 5 - Perishable Class
// Perishable.h
// Date	2018-04-11
// Weisi Kong
// Description: Defines the Perishable class

#include <fstream>
#include "Date.h"
#include "Product.h"

namespace AMA {
	class Perishable : public Product {
		Date expiryDate;

	public:

		// no-argument constructor
		//
		Perishable();

		//  This function stores a single file record for the current object
		//
		std::fstream& store(std::fstream& file, bool newLine = true) const;

		//  This function extracts the data fields for a single file record from the fstream object.
		//
		std::fstream& load(std::fstream& file);

		//calls its base class version passing as arguments a reference to the ostream object and the bool flag
		//
		std::ostream& write(std::ostream& os, bool linear) const;

		//  This function populates the current object with the data extracted from the istream object
		//
		std::istream& read(std::istream& is);

		// This query returns the expiry date for the perishable product
		//
		const Date& expiry() const;
	};
}
