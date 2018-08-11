#define _CRT_SECURE_NO_WARNINGS
// Final Project Milestone 3 - Product Class
// Product.cpp
// Date	2018-04-04 Updated 2018-04-16
// Weisi Kong 125400176 wkong10@myseneca.ca
// Description: Implementation for the product class

#include <fstream>
#include <cstring>
#include <iomanip>
#include "Product.h"

namespace AMA {

	/*****************************/
	/* protected member functions*/
	/*****************************/

	// stores the name in dynamically allocated memory
	//
	void Product::name(const char* name_) {
		if (name_ != nullptr) {
			int count = strlen(name_);
			prdName = new char[count + 1];
			for (int i = 0; i < count; i++) {
				prdName[i] = name_[i];
			}
			prdName[count] = '\0';

		}
		else {
			prdName = nullptr;
		}
	}


	// returns the address of the C-style string that holds the name of the product.
	//
	const char* Product::name() const {
		if (stringValid(prdName)) {
			return prdName;
		}
		else {
			return nullptr;
		}
	}

	// returns the price of a single item of the product plus any tax that applies to the product
	//
	double Product::cost() const {
		if (taxable) {
			return (unitPrice * (1 + tax_rate));
		}
		else {
			return unitPrice;
		}
	}

	// This function receives an error message and stores that message in the ErrorState object
	//
	void Product::message(const char* msg) {
		errorState.ErrorState::message(msg);
	}

	//  returns true if the ErrorState object is clear; false otherwise
	//
	bool Product::isClear() const {
		return errorState.ErrorState::isClear();
	}

	/***************************/
	/* public member functions */
	/***************************/

	// zero-one argument constructor
	//
	Product::Product(char productType_) {
		if (productType_ != '\0') {
			productType = productType_;
		}
		else {
			productType = 'N';

		}
		prdSku[0] = '\0';
		prdUnit[0] = '\0';
		name(nullptr);
		qtyOnHand = 0;
		qttyNeeded = 0;
		unitPrice = 0;
		taxable = false;
		errorState.ErrorState::clear();


	}

	// seven-argument constructor
	// order: sku, prdName, prdUnit, qtyOnHand, taxable, unitPrice, qttyNeeded,
	//
	Product::Product(const char* prdSku_, const char* prdName_,
		const char* prdUnit_, int qtyOnHand_,
		bool taxable_, double unitPrice_, int qttyNeeded_) {
		if (stringValid(prdSku_) && stringValid(prdName_)) {
			strncpy(prdSku, prdSku_, max_sku_length);
			prdSku[max_sku_length] = '\0';
			name(prdName_);
			strncpy(prdUnit, prdUnit_, max_unit_length);
			prdUnit[max_unit_length] = '\0';
			qtyOnHand = qtyOnHand_;
			taxable = taxable_;
			unitPrice = unitPrice_;
			qttyNeeded = qttyNeeded_;
			productType = 'N';
			errorState.ErrorState::clear(); // not specified in instructions
		}
		else {
			*this = Product();
		}
	}

	// This constructor receives an unmodifiable reference to a Product object and copies the
	// object referenced to the current object.
	//
	Product::Product(const Product& src) {
		*this = src;
	}


	// This operator receives an unmodifiable reference to a Product object and replaces the
	// current object with a copy of the object referenced
	//
	Product& Product::operator=(const Product& src) {
		if (this != &src) {
			productType = src.productType; // 1
			strncpy(prdSku, src.prdSku, max_sku_length); // 2
			prdSku[max_sku_length] = '\0';
			strncpy(prdUnit, src.prdUnit, max_unit_length); // 3
			prdUnit[max_unit_length] = '\0';
			qtyOnHand = src.qtyOnHand; // 4
			taxable = src.taxable; // 5
			unitPrice = src.unitPrice; // 6
			qttyNeeded = src.qttyNeeded; // 7
			errorState.message(src.errorState.message()); // 8
			name(src.prdName); // 9
		}
		return *this;
	}

	// destructor deallocates any memory that has been dynamically allocated.
	// 
	Product::~Product() {
		clear();
	}

	// inserts into the fstream object the character that identifies the product type as the first field in the record.
	//
	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		file << productType
			<< "," << prdSku
			<< "," << prdName
			<< "," << prdUnit
			<< "," << taxable
			<< "," << unitPrice
			<< "," << qtyOnHand
			<< "," << qttyNeeded;
		if (newLine) {
			file << std::endl;
		}
		return file;
	}

	// receives a reference to an fstream object and returns a reference to that fstream object.
	//
	std::fstream& Product::load(std::fstream& file) {
		char tempPrdType;
		char tempSku[max_sku_length + 1];
		char tempUnit[max_unit_length + 1];
		char tempPrdName[max_name_length];
		int tempQtyOnHand;
		int tempqttyNeeded;
		double tempUnitPrice;
		bool tempTaxable;
		ErrorState tempErrorState;
		char* errorMsg = nullptr;
		if (file.is_open()) {
			file.seekg(0);
			file >> tempPrdType;
			file.ignore(1, ',');
			file.getline(tempSku, max_sku_length + 1, ',');
			file.getline(tempPrdName, max_name_length + 1, ',');
			file.getline(tempUnit, max_unit_length + 1, ',');
			file >> tempTaxable;
			file.ignore(1, ',');
			file >> tempUnitPrice;
			file.ignore(1, ',');
			file >> tempQtyOnHand;
			file.ignore(1, ',');
			file >> tempqttyNeeded;
			file.ignore();
			Product temp = Product(tempSku, tempPrdName, tempUnit, tempQtyOnHand, tempTaxable, tempUnitPrice, tempqttyNeeded);
			temp.productType = tempPrdType; 
			if (errorMsg != nullptr) {
				temp.errorState.message(errorMsg);
			}
			*this = temp;
		}
		return file;
	}

	// inserts the data fields for the current object into the ostream object
	//
	std::ostream& Product::write(std::ostream& os, bool linear) const {
		if (isClear()) {
			if (linear) {
				if (!isEmpty()) {
					os << std::left;
				}
				os << std::setw(max_sku_length);
				os << prdSku << "|";
				os << std::setw(20);
				if (prdName == nullptr) {
					os.width(20);
					os << "";
					os << "|";
				}
				else {
					os.width(20);
					os << prdName << "|";
				}
				os << std::setw(7) << std::fixed << std::right << std::setprecision(2);
				os << cost() << "|";
				os << std::setw(4);
				os << qtyOnHand << "|";
				os << std::setw(10);
				os.width(10);
				os << std::left;
				os << prdUnit << "|";
				os << std::setw(4);
				os << std::right;
				os << qttyNeeded << "|";
				os << std::left;
			}
			else {
				os << " Sku: " << prdSku << std::endl;
				os << " Name (no spaces): " << prdName << std::endl;
				os << std::fixed << std::setprecision(2);
				os << " Price: " << unitPrice << std::endl;
				if (taxable) {
					os << " Price after tax: " << unitPrice * (1 + tax_rate) << std::endl;
				}
				else {
					os << " Price after tax: N/A" << std::endl;
				}
				os << " Quantity on Hand: " << qtyOnHand << " " << prdUnit << std::endl;
				os << " Quantity needed: " << qttyNeeded;
			}

		}
		else {
			os << errorState;
		}
		return os;
	}

	// extracts the data fields for the current object line by line
	//
	std::istream& Product::read(std::istream& is) {
		char tempSku[max_sku_length + 1];
		char tempUnit[max_unit_length + 1];
		char* tempPrdName;
		tempPrdName = new char[max_name_length];
		int tempQtyOnHand;
		int tempqttyNeeded;
		double tempUnitPrice;
		bool tempTaxable;
		bool go = true;
		while (go) {

			std::cout << " Sku: ";
			is.getline(tempSku, max_sku_length, '\n');
			if (is.fail()) {
				break;
			}

			std::cout << " Name (no spaces): ";
			is.getline(tempPrdName, max_name_length, '\n');
			if (is.fail()) {
				break;
			}

			std::cout << " Unit: ";
			is.getline(tempUnit, max_unit_length, '\n');
			if (is.fail()) {
				break;
			}

			std::cout << " Taxed? (y/n): ";
			char answer;
			is.get(answer);
			if (answer == 'Y' || answer == 'y') {
				tempTaxable = true;
			}
			else if (answer == 'N' || answer == 'n') {
				tempTaxable = false;
			}
			else {
				is.setstate(std::ios::failbit);
				errorState.message("Only (Y)es or (N)o are acceptable");
				break;
			}


			std::cout << " Price: ";
			is >> tempUnitPrice;
			if (is.fail()) {
				errorState.message("Invalid Price Entry");
				break;
			}

			std::cout << " Quantity on hand: ";
			is >> tempQtyOnHand;
			if (is.fail()) {
				errorState.message("Invalid Quantity Entry");
				break;
			}

			std::cout << " Quantity needed: ";
			is >> tempqttyNeeded;
			if (is.fail()) {
				errorState.message("Invalid Quantity Needed Entry");
				break;
			}

			go = false;
		}
		if (!is.fail()) {
			*this = Product(tempSku, tempPrdName, tempUnit,
				tempQtyOnHand, tempTaxable, tempUnitPrice, tempqttyNeeded);
		}
		delete[] tempPrdName;
		is.ignore(2000, '\n');  
		return is;
	}

	//  receives the address of an unmodifiable C-style null-terminated string and
	// returns true if the string is identical to the sku of the current object; false otherwise
	//
	bool Product::operator==(const char* str) const {
		return strcmp(prdSku, str) == 0;
	}

	// returns the total cost of all items of the product on hand, taxes included
	//
	double Product::total_cost() const {
		double result = unitPrice * qtyOnHand;
		if (taxable) {
			result = result * (1 + tax_rate);
		}
		return result;
	}

	// receives an integer holding the number of units of the Product that
	// are on hand.This function resets the number of units that are on hand to the number received
	//
	void Product::quantity(int update) {
		if (update > 0) {
			qtyOnHand = update;
		}
	}

	// returns true if the object is in a safe empty state; false otherwise
	//
	bool Product::isEmpty() const {
		return prdSku[0] == '\0';
	}

	// returns the number of units of the product that are needed
	//
	int Product::qtyNeeded() const {
		return qttyNeeded;
	}

	//  returns the number of units of the product that are on hand
	//
	int Product::quantity() const {
		return qtyOnHand;
	}

	// receives the address of a C - style null - terminated string holding a product sku
	//	and returns true if the sku of the current object is greater than the string stored at the
	//	received address; false otherwise
	//
	bool Product::operator>(const char* prdSku_) const {
		return strcmp(prdSku, prdSku_) > 0;
	}

	// returns true if the name of the current object is greater than the 
	// name of the referenced Product object
	//
	bool Product::operator>(const iProduct& prd) const {
		return strcmp(prdName, prd.name()) > 0;
	}

	//  returns the updated number of units on hand
	//
	int Product::operator+=(int add) {
		if (add > 0) {
			qtyOnHand += add;
		}
		return qtyOnHand;
	}

	// insert a Product record into the ostream

	std::ostream& operator<<(std::ostream& os, const iProduct& prd) {
		prd.write(os, true); // should linear be false?
		return os;
	}

	// extracts the Product record from the istream
	//
	std::istream& operator>>(std::istream& is, iProduct& prd) {
		prd.read(is);
		return is;
	}

	//  adds the total cost of the Product object to the double received and returns the updated double
	//
	double operator+=(double& cost, const iProduct& prd) {
		cost += prd.total_cost();
		return cost;
	}

	/*******************************/
	// introduced by Weisi: not specified in instructions/
	/*******************************/

	// determines if an input string is acceptable
	//
	bool stringValid(const char* str) {
		return (str != nullptr && str[0] != '\0');
	}


	// clears a product
	//
	void Product::clear() {
		delete[] prdName;
		prdName = nullptr;
	}

	// returns sku
	//
	const char* Product::sku() const {
		return prdSku;
	}

	// returns unit
	//
	const char* Product::unit() const {
		return prdUnit;
	}

	// returns tax status
	//
	bool Product::taxed() const {
		return taxable;
	}

	// returns unit price
	//
	double Product::price() const {
		return unitPrice;
	}

	// set product type
	//
	void Product::setType(const char t) {
		productType = t;
	}

}