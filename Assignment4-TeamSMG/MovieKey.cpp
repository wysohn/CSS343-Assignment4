#include "MovieKey.h"

MovieKey::MovieKey(std::string title, int year, std::string director)
	: title(title), year(year), director(director)
{
}

int MovieKey::hashCode() const
{
	return hashString(title);
}

bool MovieKey::equals(const Hashable * other) const
{
	//try to cast it to MovieKey*
	if (const MovieKey* key = dynamic_cast<const MovieKey*>(other)) {
		//compare each fields
		if (this->title != key->title)
			return false;

		//they are same only if every fields are the same
		return true;
	}
	//if cannot be casted, they are certainly not equal
	else {
		return false;
	}
}

int MovieKey::compareTo(const Comparable* other) const
{
	throw;
}

std::string MovieKey::name() const
{
	return "";
}

MovieKey* MovieKey::clone() const
{
	return new MovieKey(*this);
}

void MovieKey::print(std::ostream& out, int stock) const
{
	
}