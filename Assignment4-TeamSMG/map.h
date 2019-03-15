#pragma once

#include <cstddef>

//when capacity of Map reaches CURRENT_LOAD, it should be rehashed.
#define CURRENT_LOAD(current_capacity) current_capacity * 0.75

/*
A Map is a storage, which stores values by pairing them with corresponding keys.
The keys must be Map::Hashable, and it implies that the keys are stored
in hashtable. Access to any value is thereby guaranteed to be O(1). Collision
policy of this Map is closed, linear probing.
*/
template <class T>
class Map
{
public:
	/*
	The interface that represent the instances, which can be hashed.
	The children classes of Hashable must implement hashCode() and equals().
	hashCode() has to return any hash value, and the equals()
	method will be used when there are multiple values, with same hash values,
	stored in the bucket (as linked-list), so it can search for the exact instance.
	*/
	class Hashable {
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
		virtual bool equals(const Hashable& other) const = 0;
	};

private:
	struct Pair{
		bool deleted;

		int key;
		T* value;
	};

	int current_capacity;
	int max_size;
	Pair* buckets;

	/*
	Twice the max_size of hash table and move
	previous contents to the newly allocated memory.
	*/
	void rehash();

public:
	Map();
	~Map();

	/*
	Get current capacity of this Map. Current capacity means
	how many elements exist in the Map. This is not necessarilly
	same as the maximum size of this Map.
	*/
	int get_capacity() const;

	/*
	The maximum size of the bucket. This size dynamic, so it can
	change depending on how many elements are in this Map.
	*/
	int get_max_size() const;

	/*
	Get the value stored in this Map that is paired with given key.
	Returns NULL if no such value is found.
	*/
	T* get(const Hashable& key) const;

	/*
	Store the value paired with given key.
	If there was already a value stored with given key, it will be
	replaced with new value.
	Returns previous value if replaced or NULL if it's new value.
	*/
	T* put(const Hashable& key, const T* value);

	/*
	Check if given key exist in this Map.
	Returns true if exists, false otherwise.
	*/
	bool containsKey(const Hashable& key) const;

	/*
	Remove the value paired with the given key.
	Returns true if removed, false if not exist.
	*/
	bool remove(const Hashable& key);
};

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
			if (temp+i != NULL) {
				put((temp+i)->key, (temp+i)->value);
			}
		}

		//delete previous
		delete[] temp;
	}

}

template<class T>
Map<T>::Map() : current_capacity(0), max_size(8)
{
	//max_size start from 8, so that constructor
	//expand the buckets to 16, which is commonly
	//used number for the size of initial bucket.
	rehash();
}

template<class T>
Map<T>::~Map()
{
	delete[] this->buckets;
}

template<class T>
int Map<T>::get_capacity() const
{
	return this->current_capacity;
}

template<class T>
int Map<T>::get_max_size() const
{
	return this->max_size;
}

template<class T>
T* Map<T>::get(const Hashable& key) const
{
	///fit hash value
	int hash = key.hashCode() % this->max_size;

	///retrive appropriate value
	Pair* pair = NULL;
	//check if count is less than the max_size, so iteration doesn't go cyclic
	int count = 0;
	for (; count < this->max_size; count++) {
		//get pair at (hash + count) % max
		pair = this->buckets[(hash + count) % this->max_size];

		//skip if deleted recently
		if (key.deleted) {
			continue;
		}

		//if the pair is what we are looking for, stop iteration.
		if (key.equals(*pair->value)) {
			break;
		}
	}

	//if count is same as max_size, we couldn't find the value.
	if (count == this->max_size) {
		return NULL;
	}

	//return the value of found pair
	return pair->value;
}

template<class T>
T* Map<T>::put(const Hashable& key, const T* value)
{
	return NULL;
}

template<class T>
bool Map<T>::containsKey(const Hashable& key) const
{
	return false;
}

template<class T>
bool Map<T>::remove(const Hashable& key)
{
	return false;
}