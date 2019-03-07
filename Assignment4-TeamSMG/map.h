#pragma once

#include <cstddef>

#define CURRENT_LOAD(current_capacity) current_capacity * 0.75

template <class T>
class Map
{
public:
	class Hashable {
		virtual int hashCode() const = 0;
		virtual bool equals(const Hashable& other) const = 0;
	};

private:
	struct Pair{
		Hashable key;
		T value;
	};

	int current_capacity;
	int max_size;
	Pair* buckets;

	void rehash();

public:
	Map();
	~Map();

	T& get(const Hashable& key) const;
	T& put(const Hashable& key, const T& value);
};

