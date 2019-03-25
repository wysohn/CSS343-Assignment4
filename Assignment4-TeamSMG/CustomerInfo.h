#pragma once

#include <string>
#include <iostream>

#include "Map.h"
#include "Comparable.h"

class CustomerInfo{
    
	friend std::ostream& operator>>(std::ostream& os, CustomerInfo& info) {
		os << info.customerID;
		if (info.firstName.size() > 0) {
			os << " " << info.firstName;
		}
		if (info.lastName.size() > 0) {
			os << " " << info.lastName;
		}
		return os;
	}

protected:
    int customerID;
    std::string firstName;
    std::string lastName; 
    
public:
    CustomerInfo(int customerID, std::string firstName, std::string lastName);
};