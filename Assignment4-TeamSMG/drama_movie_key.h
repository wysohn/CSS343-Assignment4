#pragma once

#include "movie_key.h"

class DramaMovieKey : public MovieKey
{
public:
	DramaMovieKey(std::string title, int year, std::string director);

	/*
	-dramas (��D��) are sorted by Director, then Title 
	*/
	int compareTo(const Comparable* other);
};

