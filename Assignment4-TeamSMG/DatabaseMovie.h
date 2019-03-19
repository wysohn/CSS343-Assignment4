#pragma once
#include "movie_key.h"
#include "abstract_database.h"
#include <vector>


class DatabaseMovie : public AbstractDatabase<MovieKey>
{
	public:

		void sort();

		bool sortHelper(MovieKey *, MovieKey *);

		void addMovie();

	private:

		std::vector<MovieKey> vec;

};
