#include "pch.h"
#include <iostream>
#include "StringPtr.h"


int main()
{
	// empty string
	StringPtr empty;

	// also empty string
	StringPtr empty2 = ""; 

	// Pointer to EUR/USD
	StringPtr symbol = "EUR/USD";

	// Also pointer to the same EUR/USD
	StringPtr symbol2 = std::string("EUR/USD");
}