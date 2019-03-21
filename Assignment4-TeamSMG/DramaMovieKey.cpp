#include "DramaMovieKey.h"

DramaMovieKey::DramaMovieKey(std::string title, int year, std::string director)
	: MovieKey(title, year, director)
{
}

int DramaMovieKey::compareTo(const Comparable * other) const
{
	if (const DramaMovieKey* key = dynamic_cast<const DramaMovieKey*>(other)) {
		//compare director
		if (this->director < key->director) {
			return -1;
		}
		else if (this->director > key->director) {
			return 1;
		}
		//if director is same, compare title
		else {
			if (this->title < key->title) {
				return -1;
			}
			else if(this->title > key->title){
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

std::string DramaMovieKey::name() const
{
	return "Drama";
}

void DramaMovieKey::print(std::ostream& out) const
{
	out << "D, " << " [insert stock], "<< director << ", " << title << ", " << year << std::endl;
}