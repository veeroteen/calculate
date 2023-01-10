#pragma once
#include <exception>
#include <iostream>
#include <cstdlib>
#include "utils.h"
using namespace std;
struct prioritet
{
	size_t position;
	size_t priority = 0;
	
	void operator ++()
	{
		this->priority++;
	}
	prioritet(size_t position)
	{
		this->position = position;
	}
	prioritet() = default;

};


class Calculator {
	size_t size;

	size_t findOperation(size_t& start, size_t& end, const char* str)const;//looking for operator with hight priority	
	void removeBrecketsAll(char*& str)const;//remove all breackets"()" in Cstring
	void removeBrecketsSmart(char*& str)const;//remove breckets"()" that don't make sense
	double calculate(char* str)const throw(runtime_error);// calculate Cstring view operation
	void validation(char* str)const;

public:
	double calc(const char* str) throw(runtime_error);

};
