#pragma once
#include "MovieKey.h"
#include "AbstractDatabase.h"
#include <algorithm>
#include <typeinfo>
#include <vector>


class DatabaseMovie : public AbstractDatabase<MovieKey>
{
	public:

		void sort();

		void write(std::ostream& os);

	private:

		std::vector<MovieKey> vec;

		bool sortHelper(MovieKey *, MovieKey *);
};
