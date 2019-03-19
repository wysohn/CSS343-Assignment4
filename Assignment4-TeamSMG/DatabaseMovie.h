#pragma once
#include "MovieKey.h"
#include "AbstractDatabase.h"
#include <vector>


class DatabaseMovie : AbstractDatabase<MovieKey>
{
	public:

		void sort();

		bool sortHelper(MovieKey *, MovieKey *);

		void addMovie();

	private:

		std::vector<MovieKey> vec;

};
