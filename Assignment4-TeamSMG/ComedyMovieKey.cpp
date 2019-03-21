#include "ComedyMovieKey.h"

ComedyMovieKey::ComedyMovieKey(std::string title, int year, std::string director) :
	MovieKey(title, year, director)
{}

int ComedyMovieKey::compareTo(const Comparable * other) const
{
	if (const ComedyMovieKey* key = dynamic_cast<const ComedyMovieKey*>(other)) {
		//compare title
		if (this->title < key->title) {
			return -1;
		}
		else if (this->title > key->title) {
			return 1;
		}
		//if title is same, compare year
		else {
			if (this->year < key->year) {
				return -1;
			}
			else if (this->year > key->year) {
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

std::string ComedyMovieKey::name() const
{
	return "Comedy";
}

void ComedyMovieKey::print(std::ostream& out, int stock) const
{
	out << "F, " << stock << ", " << director << ", " << title << ", " << year;
}
