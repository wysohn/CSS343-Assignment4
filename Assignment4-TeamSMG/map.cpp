#include "Map.h"

int modulo(int value, int div)
{
	if (div == 0)
		throw;

	return ((value % div) + div) % div;
}
