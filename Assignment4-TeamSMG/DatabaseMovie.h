#pragma once
#include "MovieKey.h"
#include "AbstractDatabase.h"
#include "DramaMovieKey.h"
#include "ClassicMovieKey.h"
#include "ComedyMovieKey.h"
#include <algorithm>
#include <typeinfo>
#include <vector>

/*
Notes:
1. The input format is always correct, but it may have invalid input
2. Each movie has different format
3. There can be same movies in different line (then should add up stocks)
*/


class DatabaseMovie : public AbstractDatabase<MovieKey, int>
{
	public:
		void sort();

		//bool sortHelper(const MovieKey *, const MovieKey *);

		//bool comp(MovieKey, MovieKey) const;

		void read(std::istream& is);

		void write(std::ostream& os);
	private:

		std::vector<std::shared_ptr<MovieKey>> vec;
};
