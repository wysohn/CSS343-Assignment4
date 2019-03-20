#pragma once

#include <string>

#include "map.h"
#include "comparable.h"

class MovieKey : public Hashable, public Comparable 
{
protected:
	std::string title;
	int year;
	std::string director;

public:
	MovieKey(std::string title, int year, std::string director);

	/*
	Generate hash value based on title, year, and director.
	Chidren class must override this method again to produce
	different hash value.
	*/
	virtual int hashCode() const;

	/*
	Check if this object's title, year, and director
	is exactly matching with the 'other' object's
	title, year, and director. If 'other' is not
	same type as this object, it should be always false.
	*/
	virtual bool equals(const Hashable* other) const;

	/*
	All children class must implement this method
	in order to compare depending on their movie type.
	Different type of movie has different comparison rule.

	-comedy movies (¡®F¡¯) sorted by Title, then Year it released 
	-dramas (¡®D¡¯) are sorted by Director, then Title 
	-classics (¡®C¡¯) are sorted by Release date, then Major actor
	*/
	virtual int compareTo(const Comparable* other) const;
};

