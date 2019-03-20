#include "DatabaseMovie.h"

void DatabaseMovie::sort()
{

	std::sort(vec.begin(), vec.end(), sortHelper);
}

//Method to be passed as third parameter to overloaded std::sort() function.
//This clarifies to the function how objects are compared, and which is
//greater or less in value. In this case, it is in comparing two MovieKey
//objects. The movies will be sorted by genre as follows: Comedies, Dramas,
//and then Classics. Then each genre will be sorted based on the overloaded
//compareTo methods in the MovieKey subclasses.
bool DatabaseMovie::sortHelper(MovieKey *first, MovieKey *second)
{

	//MovieKeys share same subclass instance -- same genre
	if (typeid(*first) == typeid(*second))
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
		//first is Comedy, and Comedy < [any other genre]
		if (first->name() == "Comedy")
		{
			return true;
		}

		//first is Drama
		else if (first->name() == "Drama")
		{
			//second is Comedy, and Drama > Comedy
			if (second->name() == "Comedy")
			{
				return false;
			}

			//second is Classic, and Drama < Classic
			else
			{
				return true;
			}
		}

		//first is Classic, and Classic > [any other genre]
		else
		{
			return false;
		}
	}
}

void DatabaseMovie::write(std::ostream& os)
{

}