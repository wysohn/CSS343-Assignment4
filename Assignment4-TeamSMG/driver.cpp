#include <iostream>

/*
Uncomment this to perform test
*/
#define TEST

#ifdef TEST

//start of definitions
/////////////////////////////////////////////////////////////////////////
#include <iomanip>
#include <sstream>

int success = 0;
int fail = 0;

template <class T>
bool equals(T a, T b) {
	return a == b;
}

template <class T, class Pred>
void test(const char* name, T expected, T actual, Pred pred) {
	std::cout << "TEST " << std::setw(20) << name << " START" << std::endl;
	std::cout << std::endl;

	std::cout << std::setw(10) << "expected:" << expected << std::endl;
	std::cout << std::setw(10) << "actual:" << actual << std::endl;
	std::cout << std::endl;

	if (pred(expected, actual)) {
		std::cout << std::setw(10) << "PASS" << std::endl;
		success++;
	}
	else {
		std::cout << std::setw(10) << "FAIL\t\t\t[!]" << std::endl;
		fail++;
	}

	std::cout << std::endl;
	std::cout << "TEST " << std::setw(20) << name << " END";
	std::cout << std::endl << "--------------------------------------------" << std::endl;
}

template <class T>
void test(const char* name, T expected, T actual) {
	return test(name, expected, actual, equals<T>);
}

void test(const char* name, bool value) {
	return test(name, true, value);
}

#define private public
#define protected public

#define ASSERT_EQ(expected, actual) test("[EQ] "#actual, expected, actual)
#define ASSERT_TRUE(value) test("[TRUE] "#value, value)
#define ASSERT_FALSE(value) test("[FALSE] "#value, !value)
#define ASSERT_NULL(value) test("[NULL] "#value, value == NULL)
#define ASSERT_NOTNULL(value) test("[NOTNULL] "#value, value != NULL)
#define ASSERT_CUSTOM(expected, actual, pred) test("[CUSTOM] "#actual, expected, actual, pred)
//end of definitions
/////////////////////////////////////////////////////////////////////////

#include "map.h"

class TempHashable : public Map<int>::Hashable {
private:
	int value;

public:
	TempHashable(int value) : value(value) {

	}

	int hashCode() const{
		return value;
	}

	bool equals(const Hashable* other) const{
		if (const TempHashable* d = dynamic_cast<const TempHashable*>(other)) {
			return this->value == d->value;
		}
		else {
			return false;
		}
	}
};

void test_Map() {
	//test for Map
	Map<int> map; //constructor test (also rehash() is executed in constructor)
	ASSERT_EQ(0, map.get_capacity());
	ASSERT_EQ(16, map.get_max_size());
	map.rehash(); //test rehash with previous array existing
	ASSERT_EQ(0, map.get_capacity());
	ASSERT_EQ(32, map.get_max_size());

	TempHashable temp1(50);
	int temp1_val = 50;

	TempHashable temp2(53);
	int temp2_val = 53;

	TempHashable temp1_collision(18);
	int temp1_collision_val = 18;

	TempHashable temp1_collision2(82);
	int temp1_collision_val2 = 82;

	TempHashable temp1_collision3(114);
	int temp1_collision_val3 = 114;

	//functional tests of methods (find_pair put get containsKey remove)

	//find_pair (not found)
	Map<int>::Pair* pair = map.find_pair(&temp1);
	ASSERT_NULL(pair);

	//put
	int* prev = map.put(&temp1, &temp1_val);
	ASSERT_NULL(prev);
	ASSERT_EQ(1, map.get_capacity());

	//put (replacement test)
	prev = map.put(&temp1, &temp1_collision_val);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(&temp1_val, prev);
	prev = map.put(&temp1, &temp1_collision_val2);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(&temp1_collision_val, prev);
	prev = map.put(&temp1, &temp1_collision_val3);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(&temp1_collision_val2, prev);
	prev = map.put(&temp1, &temp1_val);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(&temp1_collision_val3, prev);

	//find_pair(found) with put test
	pair = map.find_pair(&temp1);
	ASSERT_NOTNULL(pair);
	ASSERT_FALSE(pair->deleted);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1), pair->key);
	ASSERT_EQ(&temp1_val, pair->value);

	//get
	int* get = map.get(&temp1);
	ASSERT_EQ(&temp1_val, get);
	get = map.get(&temp2);
	ASSERT_NULL(get);

	//containsKey
	ASSERT_FALSE(map.containsKey(&temp2));
	ASSERT_TRUE(map.containsKey(&temp1));

	//remove
	ASSERT_FALSE(map.remove(&temp2));
	ASSERT_TRUE(map.remove(&temp1));

	//get (for value deleted)
	ASSERT_NULL(map.get(&temp1));

	//collision test (50, 18, 82, 114)
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(32, map.max_size);
	map.put(&temp1_collision, &temp1_collision_val);
	map.put(&temp1_collision2, &temp1_collision_val2);
	map.put(&temp1_collision3, &temp1_collision_val3);
	ASSERT_EQ(4, map.current_capacity);
	ASSERT_EQ(32, map.max_size);
	pair = map.find_pair(&temp1_collision);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1_collision), pair->key);
	ASSERT_EQ(&temp1_collision_val, pair->value);
	pair = map.find_pair(&temp1_collision2);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1_collision2), pair->key);
	ASSERT_EQ(&temp1_collision_val2, pair->value);
	pair = map.find_pair(&temp1_collision3);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1_collision3), pair->key);
	ASSERT_EQ(&temp1_collision_val3, pair->value);

	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1), map.buckets[18]->key);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1_collision), map.buckets[19]->key);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1_collision2), map.buckets[20]->key);
	ASSERT_EQ(static_cast<const Map<int>::Hashable*>(&temp1_collision3), map.buckets[21]->key);

	//rehash test on put

	//create new map
	Map<int> map2;
	//force set max_size for test
	//this will cause memory leak as size is changed but actual size of array is same
	map2.max_size = 3;
	// max_load = 3 * 0.75 = (int)2.25 = 2
	// (18, 82, 114, 53) 18%3 = 0, 82%3 = 1, 114%3 = 0, 53%3 = 2
	map2.put(&temp1_collision, &temp1_collision_val);
	map2.put(&temp1_collision2, &temp1_collision_val2);
	map2.put(&temp1_collision3, &temp1_collision_val3);
	// the forth element should invoke rehash()
	map2.put(&temp2, &temp2_val);
	// check
	ASSERT_EQ(6, map2.max_size);
	ASSERT_EQ(4, map2.current_capacity);
}

int main() {
	///beginning of test

	test_Map();

	///end of test
	
	std::cout << std::endl << "SUCCESS: " << success << ", FAIL: " << fail;
}

#else

int main() {
	std::cout << "hello world";
	return 0;
}

#endif