#pragma once
#include "MovieKey.h"

class ClassicMovieKey :
	public MovieKey
{
public:

	MovieKey clone() const;

	std::string name() const;

};
