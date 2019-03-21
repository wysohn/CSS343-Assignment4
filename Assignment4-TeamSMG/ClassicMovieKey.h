#pragma once
#include "MovieKey.h"

class ClassicMovieKey :
	public MovieKey
{
public:
	ClassicMovieKey(std::string title, int year, std::string director, std::string actor);

	int compareTo(const Comparable* other) const;

	MovieKey clone() const;

	std::string name() const;

	std::string actor;
};
