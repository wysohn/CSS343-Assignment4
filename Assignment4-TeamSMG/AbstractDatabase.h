#pragma once

#include <iostream>

#include "Map.h"

/*
Abstract class which represent Database.
Any children class must use the 'data', which is a Map, to store or retrive values.
Also, the read() and write() method should be overriden to
read or write data from stream. For Assignment4, read() must be
overriden at least to read data from the istream, which will
be the fstream that is connected with the given file for Assignment4.
*/
template <class K, class T>
class AbstractDatabase
{
	friend std::ostream& operator<< (std::ostream& os, AbstractDatabase<K, T>& ad) {
		//let the write() method to handle the rest
		ad.write(os);
		return os;
	}

	friend std::istream& operator>> (std::istream& is, AbstractDatabase<K, T>& ad) {
		//let the read() method to handle the rest
		ad.read(is);
		return is;
	}

protected:
	Map<K, T> data;

public:
	T* get(K & key);
	T* put(K & key, T & val);

	/*
	Virtual method which will be used to read data from istream.
	Does nothing if not overrided
	*/
	virtual void read(std::istream& is);

	/*
	Virtual method which will be used to write data to ostream.
	Send out nothing to the ostream if this method is not overrided.
	*/
	virtual void write(std::ostream& os);
};

template<class K, class T>
T * AbstractDatabase<K, T>::get(K & key)
{
	return data.get(key);
}

template<class K, class T>
T * AbstractDatabase<K, T>::put(K & key, T & val)
{
	return data.put(key, val);
}

template<class K, class T>
void AbstractDatabase<K, T>::read(std::istream & is)
{
	//do nothing if not overrided
}

template<class K, class T>
void AbstractDatabase<K, T>::write(std::ostream & os)
{
	//do nothing if not overrided
}
