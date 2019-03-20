#pragma once
#include "CustomerInfo.h"

CustomerInfo::CustomerInfo(int customerID, std::string firstName = "", std::string lastName = "")
	: customerID(customerID), firstName(firstName), lastName(lastName)
{
}
