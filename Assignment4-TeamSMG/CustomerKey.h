#pragma once

#include <string>
#include "map.h"
#include "comparable.h"

class CustomerKey : public Hashable, public Comparable{    

protected:
    int customerID;
    std::string firstName;
    std::string lastName; 
    
public:
    CustomerKey(int customerID);
    
    CustomerKey(int customerID, std::string firstName);
    
    CustomerKey(int customerID, std::string firstName, std::string lastName);
    
        /*
	Generate hash value based on customerID, firstName, and lastname.
	Chidren class must override this method again to produce
	different hash value.
	*/
    virtual int hashCode() const;    
    
	/*
	Check if this object's customerID, firstName, and lastName
	is exactly matching with the 'other' object's
	customerID, firstName, and lastName. If 'other' is not
	same type as this object, it should be always false.
	*/
    virtual bool equals(const Hashable* other) const;
    
    /*
	All children class must implement this method
	in order to compare depending on their cutomerID
	Different customerID has different comparison rule.
	*/
    int compareTo(const Comparable* other) const;

	CustomerKey clone() const;
};
