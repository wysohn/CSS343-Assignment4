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
	std::cout << "TEST " << std::setw(20) << name << " END" << std::endl;
}

template <class T>
void test(const char* name, T expected, T actual) {
	return test(name, expected, actual, equals<T>);
}

void test(const char* name, bool value) {
	return test(name, true, value);
}

#define ASSERT_EQ(expected, actual) test(#actual, expected, actual)
#define ASSERT_TRUE(value) test(#value, value)
#define ASSERT_CUSTOM(expected, actual, pred) test(#actual, expected, actual, pred)
//end of definitions
/////////////////////////////////////////////////////////////////////////

#include "map.h"

int main() {
	///beginning of test

	//test for Map
	Map<int> map; //constructor test
	ASSERT_EQ(0, map.get_capacity());
	ASSERT_EQ(16, map.get_max_size());

	///end of test
	
	std::cout << std::endl << "SUCCESS: " << success << ", FAIL: " << fail;
}

#else

int main() {
	std::cout << "hello world";
	return 0;
}

#endif