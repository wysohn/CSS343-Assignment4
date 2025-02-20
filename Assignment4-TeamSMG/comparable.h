#pragma once
class Comparable
{
public:
	bool operator==(const Comparable& other) const;

	/*
	Pure virtual method, which compare this object with other object.
	If the 'other' is same type as this object, this method should
	return one of the following: -1 if this object is smaller than 'other,'
	0 if this object is same as 'other,' and 1 if this object is larger than
	'other.'
	*/
	virtual int compareTo(const Comparable* other) const =0;
};

