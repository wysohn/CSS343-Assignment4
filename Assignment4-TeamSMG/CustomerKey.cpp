#include "CustomerKey.h"

CustomerKey::CustomerKey(int customerID, std::string firstName, std::string lastName)
                    : customerID(customerID), firstName(firstName), lastName(lastName){
    
}

int CustomerKey::hashCode() const{
    return customerID + hashString(firstName) + hashString(lastName);
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
