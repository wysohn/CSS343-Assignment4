#pragma once

#include <iostream>

#include "AbstractDatabase.h"
#include "CustomerKey.h"
#include "CustomerInfo.h"

class DatabaseCustomer : public AbstractDatabase<CustomerKey, CustomerInfo>
{
public:
	void read(std::istream& is);
};