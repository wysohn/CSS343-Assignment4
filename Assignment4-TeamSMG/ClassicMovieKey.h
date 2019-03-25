#pragma once

#include <iostream>

#include "MovieKey.h"

class ClassicMovieKey :
	public MovieKey
{
private:
	std::string actor;
	int month;

public:
	ClassicMovieKey(std::string title, int year, std::string director, std::string actor, int month);

	int hashCode() const;

	bool equals(const Hashable* other) const;

	int compareTo(const Comparable* other) const;

	MovieKey* clone() const;

	std::string name() const;

	void print(std::ostream& out, int stock) const;
};
