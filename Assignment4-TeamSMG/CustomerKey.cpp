#include "CustomerKey.h"

CustomerKey::CustomerKey(int customerID)
                    : customerID(customerID), firstName(""), lastName(""){
    
}

int CustomerKey::hashCode() const{
    return 31 * customerID;
}

bool CustomerKey::equals(const Hashable* other) const{
    if(const CustomerKey* key = dynamic_cast<const CustomerKey*>(other)){
        if(this->customerID != key->customerID)
            return false;
        if(this->firstName != key->firstName)
            return false;
        if(this->lastName != key->lastName)
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
