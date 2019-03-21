#include "ClassicMovieKey.h"

MovieKey ClassicMovieKey::clone() const
{
	return ClassicMovieKey(*this);
}

//Overloaded name()
std::string ClassicMovieKey::name() const
{
	return "Classic";
}