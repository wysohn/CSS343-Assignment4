#include "DatabaseCustomer.h"

void DatabaseCustomer::read(std::istream & is)
{
	//string, int for reading words and numbers from file
	int customerID;
	std::string firstName;
	std::string lastName;

	while (is) {
		is >> customerID >> firstName >> lastName;

		CustomerKey key(customerID);
		CustomerInfo info(customerID, firstName, lastName);

		data.put(key, info);
	}
}
