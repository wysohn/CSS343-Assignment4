#pragma once

#include <iostream>
#include <queue>
#include <string>

#include "AbstractDatabase.h"
#include "CustomerKey.h"

class DatabaseTransaction :
	public AbstractDatabase<CustomerKey, std::queue<std::string>>
{
public:
	bool showTransactions(std::ostream& os, CustomerKey& key);
};

