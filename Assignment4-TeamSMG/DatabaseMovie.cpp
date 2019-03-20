#include "DatabaseMovie.h"

void DatabaseMovie::sort()
{

	std::sort(vec.begin(), vec.end(), sortHelper);
}

bool DatabaseMovie::sortHelper(MovieKey *first, MovieKey *second)
{

	//MovieKeys share same subclass instance -- same genre
	if (typeid(first) == typeid(second))
	{

		// first < second
		if (first->compareTo(second) == -1)
		{
			return true;
		}

		// first > second
		else
			return false;
	}

	//MovieKeys are objects of different subclasses -- different genres
	//Compare two movies of different genres according to this order:
	//	Comedies, Dramas, then Classics

	else
	{

	}
}

void DatabaseMovie::write(std::ostream& os)
{

}