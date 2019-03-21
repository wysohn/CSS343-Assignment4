#pragma once
#include "MovieKey.h"
class ComedyMovieKey :
	public MovieKey
{
public:
	ComedyMovieKey(std::string, int, std::string);

	std::string name() const;

	int compareTo(const Comparable* other) const;

	void print(std::ostream& out, int stock) const;
};

