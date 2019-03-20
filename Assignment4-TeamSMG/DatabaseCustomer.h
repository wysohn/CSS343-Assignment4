#pragma once

#include <iostream>

#include "map.h"
#include "Hashable.h"

/*
Abstract class which represent Database.
Any children class must use the 'data', which is a Map, to store or retrive values.
Also, the read() and write() method should be overriden to
read or write data from stream. For Assignment4, read() must be
overriden at least to read data from the istream, which will
be the fstream that is connected with the given file for Assignment4.
*/
template <class T>
class DatabaseCustomer
{
	friend std::ostream& operator<< (std::ostream& os, const DatabaseCustomer& ad) {
		//let the write() method to handle the rest
		ad.write(os);
		return os;
	}

	friend std::istream& operator>> (std::istream& is, const DatabaseCustomer& ad) {
		//let the read() method to handle the rest
		ad.read(is);
		return is;
	}

protected:
	Map<T> data;

public:
	T* get(Hashable* key);
	T* put(Hashable* key, T* val);
        
        void addCustomer();

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

template<class T>
inline T * DatabaseCustomer<T>::get(Hashable * key)
{
	return data.get(key);
}

template<class T>
inline T * DatabaseCustomer<T>::put(Hashable * key, T * val)
{
	return data.put(key, val);
}

template<class T>
inline void DatabaseCustomer<T>::read(std::istream & is)    
{
	 //string, int for reading words and numbers from file
        std::string customerInfo;
        int customerID;           
        std::string firstName;
        std::string lastName;
                
        //read number which are from node, to node and the weight
        while(customerID > 0){
         is >> customerID >> firstName >> lastName;
         customerInfo = customerID + " " + firstName + " " + lastName;
         if (is.eof()) break; 
        }
        data.put(&customerID, &customerInfo);
}

template<class T>
inline void DatabaseCustomer<T>::write(std::ostream & os)
{
    //do nothing if not overrided
}
