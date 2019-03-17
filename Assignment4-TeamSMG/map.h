#pragma once

#include <cstddef>

//when capacity of Map reaches CURRENT_LOAD, it should be rehashed.
#define CURRENT_LOAD(max_size) max_size * 0.75

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
	public:
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
		virtual bool equals(const Hashable* other) const = 0;
	};

private:
	struct Pair{
		/*
		This becomes true to mark the value deleted
		*/
		bool deleted;

		/*
		The key, which is Hashable
		*/
		const Hashable* key;
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
	Pair* find_pair(const Hashable* key) const;

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
	T* get(const Hashable* key) const;

	/*
	Store the value paired with given key.
	If there was already a value stored with given key, it will be
	replaced with new value.
	Returns previous value if replaced or NULL if it's new value.
	*/
	T* put(const Hashable* key, T* value);

	/*
	Check if given key exist in this Map.
	Returns true if exists, false otherwise.
	*/
	bool containsKey(const Hashable* key) const;

	/*
	Remove the value paired with the given key.
	Note that removing the element simply mark the bucket
	as 'deleted,' not actually emptying the bucket, so
	the capacity of map does not change after remove()
	is called or not.
	Returns true if removed, false if not exist.
	*/
	bool remove(const Hashable* key);
};

template<class T>
inline void Map<T>::rehash()
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
				put((temp[i])->key, (temp[i])->value);
			}
		}

		//delete previous
		clear(temp, prev_max);
	}

}

template<class T>
inline void Map<T>::clear(Pair** bucket, int size)
{
	//delete each bucket
	for (int i = 0; i < size; i++) {
		if(bucket[i])
			delete bucket[i];
	}

	//delete the bucket array
	delete[] bucket;
}

template<class T>
inline typename Map<T>::Pair* Map<T>::find_pair(const Hashable* key) const
{
	int hash = key->hashCode() % this->max_size;

	Pair* pair = NULL;

	//check if count is less than the max_size, so iteration doesn't go cyclic
	int count = 0;
	for (; count < this->max_size; count++) {
		//get pair at (hash + count) % max
		pair = this->buckets[(hash + count) % this->max_size];

		//skip if NULL or deleted recently
		if (pair == NULL || pair->deleted) {
			continue;
		}

		//if the pair is what we are looking for, stop iteration.
		if (key->equals(pair->key)) {
			break;
		}
	}

	//if count is same as max_size, we couldn't find the value.
	if (count == this->max_size) {
		return NULL;
	}

	return pair;
}

template<class T>
Map<T>::Map() : current_capacity(0), max_size(8), buckets(NULL)
{
	//max_size start from 8, so that constructor
	//expand the buckets to 16, which is commonly
	//used number for the size of initial bucket.
	rehash();
}

template<class T>
Map<T>::~Map()
{
	this->clear(this->buckets, this->max_size);
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
T* Map<T>::get(const Hashable* key) const
{
	//retrive appropriate value
	Pair* pair = find_pair(key);

	//return the value of found pair
	return pair == NULL ? NULL : pair->value;
}

template<class T>
T* Map<T>::put(const Hashable* key, T* value)
{
	//retrive previous pair
	Pair* prev_pair = find_pair(key);

	//create new pair if not exist
	if (prev_pair == NULL) {
		//check if rehashing is required
		if (CURRENT_LOAD(this->max_size) < this->current_capacity) {
			this->rehash();
		}

		int hash = key->hashCode() % this->max_size;
		int index = -1;

		//iterate all buckets at least once until finding empty bucket
		int count = 0;
		for (; count < this->max_size; count++) {
			//keep move forward until find an empty bucket
			index = (hash + count) % this->max_size;
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
		bucket->key = key;
		bucket->value = value;

		//assign to bucket
		this->buckets[index] = bucket;
		this->current_capacity++;

		return NULL;
	}
	//or replace
	else {
		T* prev = prev_pair->value;
		prev_pair->value = value;

		//return the previous value
		return prev;
	}
}

template<class T>
bool Map<T>::containsKey(const Hashable* key) const
{
	//retrive appropriate value if exist
	Pair* pair = find_pair(key);

	//true if not NULL and not marked as deleted
	return pair != NULL && !pair->deleted;
}

template<class T>
bool Map<T>::remove(const Hashable* key)
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