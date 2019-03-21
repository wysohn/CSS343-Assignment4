#include "ClassicMovieKey.h"

MovieKey ClassicMovieKey::clone() const
{
	return ClassicMovieKey(*this);
}

//call MovieKey constructor for title, year, and director, and then assign passed major actor
//to the actor field of this class
ClassicMovieKey::ClassicMovieKey(std::string title, int year, std::string director, std::string actor)
	: MovieKey(title, year, director)
{
	actor = actor;
}

int ClassicMovieKey::compareTo(const Comparable * other) const
{
	if (const ClassicMovieKey* key = dynamic_cast<const ClassicMovieKey*>(other)) {
		//compare releaseDate
		if (this->year < key->year) {
			return -1;
		}
		else if (this->year > key->year) {
			return 1;
		}
		//if title is same, compare major actor
		else {
			if (this->actor < key->actor) {
				return -1;
			}
			else if (this->actor > key->actor) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	else {
		throw;
	}
}

//Overloaded name()
std::string ClassicMovieKey::name() const
{
	return "Classic";
}