#pragma once

#include <string>

/*
The interface that represent the instances, which can be hashed.
The children classes of Hashable must implement hashCode() and equals().
hashCode() has to return any hash value, and the equals()
method will be used when there are multiple values, with same hash values,
stored in the bucket (as linked-list), so it can search for the exact instance.
*/
class Hashable {
public:
	/*
	Return hash value unique (as much as possible)
	to the given string.
	*/
	static int hashString(std::string str) {
		int hash = 0;
		for (unsigned i = 0; i < str.length(); i++) {
			hash += str[i];
		}
		return 31 * hash;
	}

	/*
	The hash value of this instance. More the unique this value is, then
	less collision will occur.
	*/
	virtual int hashCode() const = 0;

	/*
	Compare to see if the instance in the bucket is same as this instance.
	This will be used when there are multiple Hashables with same hash value
	(a.k.a collision).
	*/
	virtual bool equals(const Hashable* other) const = 0;
};
