#pragma once
#include "MovieKey.h"
class ComedyMovieKey :
	public MovieKey
{
public:

	std::string name() const;

	int compareTo(const Comparable* other) const;
};

