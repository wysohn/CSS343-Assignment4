#include "CustomerInfo.h"


CustomerInfo::CustomerInfo(int customerID)
                    : customerID(customerID){
    
}

CustomerInfo::CustomerInfo(int customerID, std::string firstName) 
                    : customerID(customerID), firstName(firstName){
    
}

CustomerInfo::CustomerInfo(int customerID, std::string firstName, 
        std::string lastName)
            : customerID(customerID), firstName(firstName), lastName(lastName){
    
}


int CustomerInfo::hashCode() const{
    return hashString(firstName) + hashString(lastName);
}

bool CustomerInfo::equals(const Hashable* other) const{
    if(const CustomerInfo* key = dynamic_cast<const CustomerInfo*>(other)){
        if(this->firstName != key->firstName)
            return false;
        if(this->lastName != key->lastName)
            return false;
        
        return true;
    }else{
        return false;
    }
}

int CustomerInfo::compareTo(const Comparable * other) const{
	if (const CustomerInfo* key = dynamic_cast<const CustomerInfo*>(other)) {
		//compare director
		if (this->firstName < key->firstName) {
			return -1;
		}
		else if (this->lastName > key->lastName) {
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
