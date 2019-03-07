#include "map.h"

template<class T>
void Map<T>::rehash()
{
	//temporarily store previous data
	Pair* temp = this->buckets;
	int prev_max = this->max_size;

	//resize the buckets
	this->max_size *= 2;
	this->buckets = new Pair[this->max_size];

	//copy previous data if exist
	if (temp != NULL) {
		for (int i = 0; i < prev_max; i++) {
			if (temp[i] != NULL) {
				put(temp[i].key, temp[i].value);
			}
		}

		//delete previous
		delete[] temp;
	}

}

template<class T>
Map<T>::Map() : current_capacity(0), max_size(8)
{
	
}

template<class T>
Map<T>::~Map()
{
	rehash();
}

template<class T>
T& Map<T>::get(const Hashable & key) const
{
	return &T();
}

template<class T>
T& Map<T>::put(const Hashable & key, const T & value)
{
	return &T();
}

