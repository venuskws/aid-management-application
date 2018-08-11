// Final Project Milestone 3 - Product Class
// Product.h
// Date	2018-04-04
// Weisi Kong 125400176 wkong10@myseneca.ca
// Description: Defines the product class

#pragma once
#include "iProduct.h"
#include "ErrorState.h"

namespace AMA {

	// declares constant variables
	//
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	// declares class Product
	//
	class Product : public iProduct {
		// instance variables
		char productType;
		char prdSku[max_sku_length + 1];
		char prdUnit[max_unit_length + 1];
		char* prdName;
		int qtyOnHand;
		int qttyNeeded;
		double unitPrice;
		bool taxable;
		ErrorState errorState;

	protected:
		// receives the address of a C-style null-terminated string that holds the name of the product
		//
		void name(const char*);

		// returns the address of the C-style string that holds the name of the product.
		//
		const char* name() const;

		// returns the price of a single item of the product plus any tax that applies to the product
		//
		double cost() const;

		// This function receives the address of a C - style null - terminated string holding an error
		// message and stores that message in the ErrorState object
		//
		void message(const char*);

		//  returns true if the ErrorState object is clear; false otherwise
		//
		bool isClear() const;

		// clears a Product
		//
		void clear();

	public:

		// zero-one argument constructor
		//
		Product(char productType_ = 'N');

		// seven-argument constructor
		// order: prdSku, prdName, prdUnit, qtyOnHand, taxable, unitPrice, qttyNeeded,
		//
		Product(const char*, const char*, const char*, 
			int = 0, bool = true, double = 0, int = 0);

		// receives an unmodifiable reference to a Product object and copies the
		// object referenced to the current object.
		//
		Product(const Product&);

		// receives an unmodifiable reference to a Product object and replaces the
		// current object with a copy of the object reference
		//
		Product& operator=(const Product&);

		// destructor deallocates any memory that has been dynamically allocated
		// 
		~Product();

		// inserts into the fstream object the character that identifies the product type as the first field in the record
		//
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const;

		// receives a reference to an fstream object and returns a reference to that fstream object.
		//
		virtual std::fstream& load(std::fstream& file);

		// inserts the data fields for the current object into the ostream object
		//
		virtual std::ostream& write(std::ostream& os, bool linear) const;

		// extracts the data fields for the current object line by line
		//
		virtual std::istream& read(std::istream& is);

		//  receives the address of an unmodifiable C-style null-terminated string and
		// returns true if the string is identical to the sku of the current object; false otherwise
		//
		bool operator==(const char*) const;

		// returns the total cost of all items of the product on hand, taxes included
		//
		double total_cost() const;

		// receives an integer holding the number of units of the Product that
		// are on hand.This function resets the number of units that are on hand to the number received
		//
		void quantity(int);

		// returns true if the object is in a safe empty state; false otherwise
		//
		bool isEmpty() const;

		// returns the number of units of the product that are needed
		//
		int qtyNeeded() const;

		//  returns the number of units of the product that are on hand
		//
		int quantity() const;

		// receives the address of a C - style null - terminated string holding a product sku
		//	and returns true if the sku of the current object is greater than the string stored at the
		//	received address; false otherwise
		//
		bool operator>(const char*) const;

		// returns true if the name of the current object is greater than the 
		// name of the referenced Product object
		//
		virtual bool operator>(const iProduct&) const;

		//  returns the updated number of units on hand
		//
		int operator+=(int);

		// not in the instructions but appeared in MyProduct.cpp
		//
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;

		// introduced by Weisi
		// set product type
		void setType(const char);
	};

	// insert a Product record into the ostream
	//
	std::ostream& operator<<(std::ostream&, const iProduct&);
	
	// extracts the Product record from the istream
	//
	std::istream& operator>>(std::istream&, iProduct&);

	//  adds the total cost of the Product object to the double received and returns the updated double
	//
	double operator+=(double&, const iProduct&);

	/* introduced by Weisi*/

	// determines if an input string is acceptable
	//
	bool stringValid(const char*);



}