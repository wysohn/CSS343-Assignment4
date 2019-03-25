#include "ClassicMovieKey.h"

MovieKey* ClassicMovieKey::clone() const
{
	return new ClassicMovieKey(*this);
}

//call MovieKey constructor for title, year, and director, and then assign passed major actor
//to the actor field of this class
ClassicMovieKey::ClassicMovieKey(std::string title, int year, std::string director, std::string actor, int month)
	: MovieKey(title, year, director), actor(actor), month(month)
{
}

int ClassicMovieKey::hashCode() const
{
	return 31 * month + 31 * year + hashString(actor);
}

bool ClassicMovieKey::equals(const Hashable * other) const
{
	//try to cast it to MovieKey*
	if (const ClassicMovieKey* key = dynamic_cast<const ClassicMovieKey*>(other)) {
		//compare each fields
		if (this->month != key->month)
			return false;
		if (this->year != key->year)
			return false;
		if (this->actor != key->actor)
			return false;

		//they are same only if every fields are the same
		return true;
	}
	//if cannot be casted, they are certainly not equal
	else {
		return false;
	}
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

void ClassicMovieKey::print(std::ostream& out, int stock) const
{
	out << "C, " << stock << ", " << director << ", " << title << ", " << actor << " " << month << " " << year;
}