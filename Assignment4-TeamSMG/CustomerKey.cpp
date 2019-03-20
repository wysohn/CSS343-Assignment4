#include "CustomerKey.h"

CustomerKey::CustomerKey(int customerID)
                    : customerID(customerID){
    
}

CustomerKey::CustomerKey(int customerID, std::string firstName) 
                    : customerID(customerID), firstName(firstName){
    
}

CustomerKey::CustomerKey(int customerID, std::string firstName, 
        std::string lastName)
            : customerID(customerID), firstName(firstName), lastName(lastName){
    
}


int CustomerKey::hashCode() const{
    return 31 * customerID + hashString(firstName) + hashString(lastName);
}

bool CustomerKey::equals(const Hashable* other) const{
    if(const CustomerKey* key = dynamic_cast<const CustomerKey*>(other)){
        if(this->customerID != key->customerID)
            return false;
        
        return true;
    }else{
        return false;
    }
}

int CustomerKey::compareTo(const Comparable * other){
	if (const CustomerKey* key = dynamic_cast<const CustomerKey*>(other)) {            
		if (this->customerID < key->customerID) {
			return -1;
		}
		else if (this->customerID > key->customerID) {
			return 1;
		}                
		else {
                    return 0;
		}
	}
	else {
		throw;
	}
}
