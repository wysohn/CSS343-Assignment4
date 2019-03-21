#include "DatabaseMovie.h"

#include <sstream>

	//bool DatabaseMovie::comp(MovieKey first, MovieKey second) const
	//{
	//	//MovieKeys share same subclass instance -- same genre
	//	if (typeid(first) == typeid(second))
	//	{

	//		// first < second
	//		if (first.compareTo(&second) == -1)
	//		{
	//			return true;
	//		}

	//		// first > second
	//		else
	//			return false;
	//	}

	//	//MovieKeys are objects of different subclasses -- different genres
	//	//Compare two movies of different genres according to this order:
	//	//	Comedies, Dramas, then Classics
	//	else
	//	{
	//		//first is Comedy, and Comedy < [any other genre]
	//		if (first.name() == "Comedy")
	//		{
	//			return true;
	//		}

	//		//first is Drama
	//		else if (first.name() == "Drama")
	//		{
	//			//second is Comedy, and Drama > Comedy
	//			if (second.name() == "Comedy")
	//			{
	//				return false;
	//			}

	//			//second is Classic, and Drama < Classic
	//			else
	//			{
	//				return true;
	//			}
	//		}

	//		//first is Classic, and Classic > [any other genre]
	//		else
	//		{
	//			return false;
	//		}
	//	}
	//}

void DatabaseMovie::sort()
{

	std::sort(vec.begin(), vec.end(),
		[](std::shared_ptr<MovieKey> ptr_first, std::shared_ptr<MovieKey> ptr_second)
	{
		MovieKey* first = ptr_first.get();
		MovieKey* second = ptr_second.get();

		//MovieKeys share same subclass instance -- same genre
		if (first->name() == second->name())
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
	});//end of function
}

//Method to be passed as third parameter to overloaded std::sort() function.
//This clarifies to the function how objects are compared, and which is
//greater or less in value. In this case, it is in comparing two MovieKey
//objects. The movies will be sorted by genre as follows: Comedies, Dramas,
//and then Classics. Then each genre will be sorted based on the overloaded
//compareTo methods in the MovieKey subclasses.
//bool DatabaseMovie::sortHelper(const MovieKey *first, const MovieKey *second)
//{
//
//	//MovieKeys share same subclass instance -- same genre
//	if (typeid(*first) == typeid(*second))
//	{
//
//		// first < second
//		if (first->compareTo(second) == -1)
//		{
//			return true;
//		}
//
//		// first > second
//		else
//			return false;
//	}
//
//	//MovieKeys are objects of different subclasses -- different genres
//	//Compare two movies of different genres according to this order:
//	//	Comedies, Dramas, then Classics
//	else
//	{
//		//first is Comedy, and Comedy < [any other genre]
//		if (first->name() == "Comedy")
//		{
//			return true;
//		}
//
//		//first is Drama
//		else if (first->name() == "Drama")
//		{
//			//second is Comedy, and Drama > Comedy
//			if (second->name() == "Comedy")
//			{
//				return false;
//			}
//
//			//second is Classic, and Drama < Classic
//			else
//			{
//				return true;
//			}
//		}
//
//		//first is Classic, and Classic > [any other genre]
//		else
//		{
//			return false;
//		}
//	}
//}
//

void DatabaseMovie::read(std::istream & is)
{
	/*
	Comedy
	Stock, Director, Title, Year of release

	F, 10, Nora Ephron, You've Got Mail, 1998

	Drama
	Stock, Director, Title, Year of release

	D, 10, Steven Spielberg, Schindler's List, 1993

	Classic
	Stock, Director, Title, Major actor and Release date

	C, 10, George Cukor, Holiday, Cary Grant 9 1938
	*/

	char buffer[256];

	while (is) {
		is.getline(buffer, 256);
		std::string tokens[5];
		
		int i = 0;
		char* nextToken;
		char* pch = strtok_s(buffer, ",", &nextToken);
		while (pch != NULL)
		{
			tokens[i++] = std::string(pch);
			pch = strtok_s(NULL, ",", &nextToken);
		}

		if (tokens[0] == "F" || tokens[0]== "D") {
			int stock = stoi(tokens[1]);
			std::string director = tokens[2];
			std::string title = tokens[3];
			int year = stoi(tokens[4]);

			if (tokens[0] == "F") {
				ComedyMovieKey key(title, year, director);
				int* previous = this->get(key);
				int newStock = (previous == NULL ? 0 : *previous) + stock;

				this->put(key, newStock);
				if (previous == NULL)
					this->vec.push_back(std::shared_ptr<ComedyMovieKey>(new ComedyMovieKey(key)));
			}
			else {
				DramaMovieKey key(title, year, director);
				int* previous = this->get(key);
				int newStock = (previous == NULL ? 0 : *previous) + stock;

				this->put(key, newStock);
				if(previous == NULL)
					this->vec.push_back(std::shared_ptr<DramaMovieKey>(new DramaMovieKey(key)));
			}
		}
		else if (tokens[0] == "C") {
			int stock = stoi(tokens[1]);
			std::string director = tokens[2];
			std::string title = tokens[3];
			std::string actor_month_year = tokens[4];

			std::istringstream iss(actor_month_year);
			std::string actor_first;
			std::string actor_last;
			std::string month_str;
			std::string year_str;
			iss >> actor_first >> actor_last >> month_str >> year_str;
			int month = stoi(month_str);
			int year = stoi(year_str);

			ClassicMovieKey key(title, year, director, actor_first + " " + actor_last, month);
			int* previous = this->get(key);
			int newStock = (previous == NULL ? 0 : *previous) + stock;

			this->put(key, newStock);
			if (previous == NULL)
				this->vec.push_back(std::shared_ptr<ClassicMovieKey>(new ClassicMovieKey(key)));
		}
		else {
			//?
		}
	}
}

void DatabaseMovie::write(std::ostream& os)
{
	for(std::vector<MovieKey>::size_type i = 0; i != vec.size(); i++)
	{
		MovieKey* key = vec[i].get();
		int* stock = this->get(*key);
		os << (i + 1) << ". ";
		key->print(os, stock == NULL ? -1 : *stock);
		os << std::endl;
	}
}
