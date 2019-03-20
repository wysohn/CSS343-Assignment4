#include "Comparable.h"

bool Comparable::operator==(const Comparable & other) const
{
	return compareTo(&other) == 0;
}
