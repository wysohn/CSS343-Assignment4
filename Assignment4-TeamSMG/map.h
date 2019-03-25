#pragma once

#include <cstddef>
#include <string>

#include "Hashable.h"

//when capacity of Map reaches CURRENT_LOAD, it should be rehashed.
#define CURRENT_LOAD(max_size) max_size * 0.75

/*
return 'value' modulo 'div'.
if 'div' is 0, it will throw exception as
int divided by 0 is undefined.
*/
int modulo(int value, int div);

/*
A Map is a storage, which stores values by pairing them with corresponding keys.
The keys must be Map::Hashable, and it implies that the keys are stored
in hashtable. Access to any value is thereby guaranteed to be O(1). Collision
policy of this Map is closed, linear probing.

Template K should be Hashable and Clonable
*/
template <class K, class T>
class Map
{
private:
	struct Pair{
		/*
		This becomes true to mark the value deleted
		*/
		bool deleted;

		/*
		The key, which is Hashable
		*/
		K* key;
		/*
		Actual value saved
		*/
		T* value;
	};

	int current_capacity;
	int max_size;
	Pair** buckets;

	/*
	Twice the max_size of hash table and move
	previous contents to the newly allocated memory.
	*/
	void rehash();

	/*
	Clear everything in the given bucket.
	*/
	void clear(Pair** bucket, int size);

	/*
	Attempt to get the pair associated with given key.
	*/
	Pair* find_pair(const K& key) const;

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
	T* get(const K& key) const;

	/*
	Store the value paired with given key.
	If there was already a value stored with given key, it will be
	replaced with new value.
	Returns previous value if replaced or NULL if it's new value.
	*/
	T* put(const K& key, T& value);

	/*
	Check if given key exist in this Map.
	Returns true if exists, false otherwise.
	*/
	bool containsKey(const K& key) const;

	/*
	Remove the value paired with the given key.
	Note that removing the element simply mark the bucket
	as 'deleted,' not actually emptying the bucket, so
	the capacity of map does not change after remove()
	is called or not.
	Returns true if removed, false if not exist.
	*/
	bool remove(const K& key);
};

template<class K, class T>
void Map<K, T>::rehash()
{
	//temporarily store previous data
	Pair** temp = this->buckets;
	int prev_max = this->max_size;

	//resize the buckets
	this->current_capacity = 0;
	this->max_size *= 2;
	this->buckets = new Pair*[this->max_size]{NULL, };

	//copy previous data if exist
	if (temp != NULL) {
		for (int i = 0; i < prev_max; i++) {
			if (temp[i] != NULL) {
				put(*(temp[i])->key, *(temp[i])->value);
			}
		}

		//delete previous
		clear(temp, prev_max);
	}

}

template<class K, class T>
void Map<K, T>::clear(Pair** bucket, int size)
{
	//delete each bucket
	for (int i = 0; i < size; i++) {
		if (bucket[i]) {
			delete bucket[i]->key;
			delete bucket[i]->value;
			delete bucket[i];
		}
	}

	//delete the bucket array
	delete[] bucket;
}

template<class K, class T>
typename Map<K, T>::Pair* Map<K, T>::find_pair(const K& key) const
{
	int hash = modulo(key.hashCode(), this->max_size);

	Pair* pair = NULL;

	//check if count is less than the max_size, so iteration doesn't go cyclic
	int count = 0;
	for (; count < this->max_size; count++) {
		//get pair at (hash + count) mod max
		pair = this->buckets[modulo(hash + count, this->max_size)];

		//skip if NULL or deleted recently
		if (pair == NULL || pair->deleted) {
			continue;
		}

		//if the pair is what we are looking for, stop iteration.
		if (key.equals(pair->key)) {
			break;
		}
	}

	//if count is same as max_size, we couldn't find the value.
	if (count == this->max_size) {
		return NULL;
	}

	return pair;
}

template<class K, class T>
Map<K, T>::Map() : current_capacity(0), max_size(8), buckets(NULL)
{
	//max_size start from 8, so that constructor
	//expand the buckets to 16, which is commonly
	//used number for the size of initial bucket.
	rehash();
}

template<class K, class T>
Map<K, T>::~Map()
{
	this->clear(this->buckets, this->max_size);
}

template<class K, class T>
int Map<K, T>::get_capacity() const
{
	return this->current_capacity;
}

template<class K, class T>
int Map<K, T>::get_max_size() const
{
	return this->max_size;
}

template<class K, class T>
T* Map<K, T>::get(const K& key) const
{
	//retrive appropriate value
	Pair* pair = find_pair(key);

	//return the value of found pair
	return pair == NULL ? NULL : pair->value;
}

template<class K, class T>
T* Map<K, T>::put(const K& key, T& value)
{
	//retrive previous pair
	Pair* prev_pair = find_pair(key);

	//create new pair if not exist
	if (prev_pair == NULL) {
		//check if rehashing is required
		if (CURRENT_LOAD(this->max_size) < this->current_capacity) {
			this->rehash();
		}

		int hash = modulo(key.hashCode(), this->max_size);
		int index = -1;

		//iterate all buckets at least once until finding empty bucket
		int count = 0;
		for (; count < this->max_size; count++) {
			//keep move forward until find an empty bucket
			index = modulo(hash + count, this->max_size);
			if (this->buckets[index] == NULL) {
				break;
			}
		}

		//coudln't find empty bucket. something went wrong
		if (count == this->max_size) {
			throw;
		}

		//create new pair
		Pair* bucket = new Pair();
		bucket->key = key.clone();
		bucket->value = new T(value);

		//assign to bucket
		this->buckets[index] = bucket;
		this->current_capacity++;

		return NULL;
	}
	//or replace
	else {
		T* prev = prev_pair->value;
		prev_pair->value = new T(value);

		//return the previous value
		return prev;
	}
}

template<class K, class T>
bool Map<K, T>::containsKey(const K& key) const
{
	//retrive appropriate value if exist
	Pair* pair = find_pair(key);

	//true if not NULL and not marked as deleted
	return pair != NULL && !pair->deleted;
}

template<class K, class T>
bool Map<K, T>::remove(const K& key)
{
	//retrive appropriate value if exist
	Pair* pair = find_pair(key);

	//nothing to delete if not exist or already deleted
	if (pair == NULL || pair->deleted) {
		return false;
	}

	//simply mark as deleted
	pair->deleted = true;

	return true;
}