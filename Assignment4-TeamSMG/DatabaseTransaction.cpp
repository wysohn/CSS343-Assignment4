#include "DatabaseTransaction.h"

bool DatabaseTransaction::showTransactions(std::ostream & os, CustomerKey& key)
{
	std::queue<std::string>* queue = this->get(key);
	if (queue == NULL)
		return false;

	int size = queue->size();
	for (int i = 0; i < size; i++) {
		std::string value = queue->front();
		os << value << std::endl;
		queue->pop();
		queue->push(value);
	}

	return true;
}
