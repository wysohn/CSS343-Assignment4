#include <iostream>
#include <fstream>

/*
Uncomment this to perform test
*/
#define TEST

#ifdef TEST

//start of definitions
/////////////////////////////////////////////////////////////////////////
#include <iomanip>
#include <sstream>
#include <string>

int success = 0;
int fail = 0;

template <class T>
bool equals(T a, T b) {
	return a == b;
}

template <class T, class Pred>
void test(int line, const char* name, T expected, T actual, Pred pred) {
	std::cout << "TEST " << "line: " << line << std::setw(20) << name << " START" << std::endl;
	std::cout << std::endl;

	std::cout << std::setw(10) << "expected:" << expected << std::endl;
	std::cout << std::setw(10) << "actual:" << actual << std::endl;
	std::cout << std::endl;

	if (pred(expected, actual)) {
		std::cout << std::setw(10) << "PASS" << std::endl;
		success++;
	}
	else {
		std::cout << std::setw(10) << "FAIL" << "\t\t\t\t[!]" << std::endl;
		fail++;
	}

	std::cout << std::endl;
	std::cout << "TEST " << std::setw(20) << name << " END";
	std::cout << std::endl << "--------------------------------------------" << std::endl;
}

template <class T>
void test(int line, const char* name, T expected, T actual) {
	return test(line, name, expected, actual, equals<T>);
}

void test(int line, const char* name, bool value) {
	return test(line, name, true, value);
}

#define private public
#define protected public

#define ASSERT_EQ(expected, actual) test(__LINE__, "[EQ] "#actual, expected, actual)
#define ASSERT_TRUE(value) test(__LINE__, "[TRUE] "#value, value)
#define ASSERT_FALSE(value) test(__LINE__, "[FALSE] "#value, !value)
#define ASSERT_NULL(value) test(__LINE__, "[NULL] "#value, value == NULL)
#define ASSERT_NOTNULL(value) test(__LINE__, "[NOTNULL] "#value, value != NULL)
#define ASSERT_CUSTOM(expected, actual, pred) test(__LINE__, "[CUSTOM] "#actual, expected, actual, pred)
//end of definitions
/////////////////////////////////////////////////////////////////////////

#include <queue>

#include "Map.h"
#include "DramaMovieKey.h"
#include "CustomerKey.h"
#include "DatabaseTransaction.h"

class TempHashable : public Hashable {

	friend std::ostream& operator<< (std::ostream& os, TempHashable& h) {
		os << h.value;
		return os;
	}

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
	Map<TempHashable, int> map; //constructor test (also rehash() is executed in constructor)
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
	Map<TempHashable, int>::Pair* pair = map.find_pair(temp1);
	ASSERT_NULL(pair);

	//put
	int* prev = map.put(temp1, temp1_val);
	ASSERT_NULL(prev);
	ASSERT_EQ(1, map.get_capacity());

	//put (replacement test)
	prev = map.put(temp1, temp1_collision_val);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(temp1_val, *prev);
	prev = map.put(temp1, temp1_collision_val2);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(temp1_collision_val, *prev);
	prev = map.put(temp1, temp1_collision_val3);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(temp1_collision_val2, *prev);
	prev = map.put(temp1, temp1_val);
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(temp1_collision_val3, *prev);

	//find_pair(found) with put test
	pair = map.find_pair(temp1);
	ASSERT_NOTNULL(pair);
	ASSERT_FALSE(pair->deleted);
	ASSERT_EQ(temp1, *pair->key);
	ASSERT_EQ(temp1_val, *pair->value);

	//get
	int* get = map.get(temp1);
	ASSERT_EQ(temp1_val, *get);
	get = map.get(temp2);
	ASSERT_NULL(get);

	//containsKey
	ASSERT_FALSE(map.containsKey(temp2));
	ASSERT_TRUE(map.containsKey(temp1));

	//remove
	ASSERT_FALSE(map.remove(temp2));
	ASSERT_TRUE(map.remove(temp1));

	//get (for value deleted)
	ASSERT_NULL(map.get(temp1));

	//collision test (50, 18, 82, 114)
	ASSERT_EQ(1, map.current_capacity);
	ASSERT_EQ(32, map.max_size);
	map.put(temp1_collision, temp1_collision_val);
	map.put(temp1_collision2, temp1_collision_val2);
	map.put(temp1_collision3, temp1_collision_val3);
	ASSERT_EQ(4, map.current_capacity);
	ASSERT_EQ(32, map.max_size);
	pair = map.find_pair(temp1_collision);
	ASSERT_EQ(temp1_collision, *pair->key);
	ASSERT_EQ(temp1_collision_val, *pair->value);
	pair = map.find_pair(temp1_collision2);
	ASSERT_EQ(temp1_collision2, *pair->key);
	ASSERT_EQ(temp1_collision_val2, *pair->value);
	pair = map.find_pair(temp1_collision3);
	ASSERT_EQ(temp1_collision3, *pair->key);
	ASSERT_EQ(temp1_collision_val3, *pair->value);

	ASSERT_EQ(temp1, *map.buckets[18]->key);
	ASSERT_EQ(temp1_collision, *map.buckets[19]->key);
	ASSERT_EQ(temp1_collision2, *map.buckets[20]->key);
	ASSERT_EQ(temp1_collision3, *map.buckets[21]->key);

	//rehash test on put

	//create new map
	Map<TempHashable, int> map2;
	//force set max_size for test
	//this will cause memory leak as size is changed but actual size of array is same
	map2.max_size = 3;
	// max_load = 3 * 0.75 = (int)2.25 = 2
	// (18, 82, 114, 53) 18%3 = 0, 82%3 = 1, 114%3 = 0, 53%3 = 2
	map2.put(temp1_collision, temp1_collision_val);
	map2.put(temp1_collision2, temp1_collision_val2);
	map2.put(temp1_collision3, temp1_collision_val3);
	// the forth element should invoke rehash()
	map2.put(temp2, temp2_val);
	// check
	ASSERT_EQ(6, map2.max_size);
	ASSERT_EQ(4, map2.current_capacity);
}

class TempKey : public MovieKey {
public:
	TempKey(std::string title, int year, std::string director)
		: MovieKey(title, year, director)
	{
	}

	//just return 0 as we are not gonna use it
	int compareTo(const Comparable* other) const{
		return 0;
	}
};

void test_MovieKey() {
	TempKey key("King of Hearts", 1967, "Phillippe De Broca");
	TempKey same(key);
	TempKey different("Amazing Story", 2019, "Some person");

	//"King of Hearts" = 1285
	//1285 * 31 = 39835
	//"Phillippe De Broca" = 1665
	//1655 * 31 = 51305
	ASSERT_EQ(39835 + 31 * 1967 + 51305, key.hashCode());
	ASSERT_TRUE(key.equals(&same));
	ASSERT_FALSE(key.equals(&different));
}

void test_DramaMovieKey() {
	//basic test
	DramaMovieKey drama_key("King of Hearts", 1967, "Phillippe De Broca");
	ASSERT_EQ(std::string("King of Hearts"), drama_key.title);
	ASSERT_EQ(1967, drama_key.year);
	ASSERT_EQ(std::string("Phillippe De Broca"), drama_key.director);

	//compareTo() test. Director, then Title
	
	DramaMovieKey same_key(drama_key);
	ASSERT_EQ(std::string("King of Hearts"), same_key.title);
	ASSERT_EQ(1967, same_key.year);
	ASSERT_EQ(std::string("Phillippe De Broca"), same_key.director);

	DramaMovieKey larger(same_key);
	larger.title = "Laughing man";
	larger.director = "Questionable Person";
	ASSERT_EQ(std::string("Laughing man"), larger.title);
	ASSERT_EQ(1967, larger.year);
	ASSERT_EQ(std::string("Questionable Person"), larger.director);

	DramaMovieKey smaller(same_key);
	smaller.title = "Joker";
	smaller.director = "Omg";
	ASSERT_EQ(std::string("Joker"), smaller.title);
	ASSERT_EQ(1967, smaller.year);
	ASSERT_EQ(std::string("Omg"), smaller.director);

	//director equal
	ASSERT_TRUE(drama_key.compareTo(&same_key) == 0);

	//director smaller
	ASSERT_TRUE(drama_key.compareTo(&larger) == -1);

	//director larger
	ASSERT_TRUE(drama_key.compareTo(&smaller) == 1);

	//title eqaul
	ASSERT_TRUE(drama_key.compareTo(&same_key) == 0);

	//title smaller
	ASSERT_TRUE(drama_key.compareTo(&larger) == -1);

	//title larger
	ASSERT_TRUE(drama_key.compareTo(&smaller) == 1);
}

class TempKey2 : public CustomerKey {
public:
	TempKey2(int customerID)
		: CustomerKey(customerID)
	{
	}

	//just return 0 as we are not gonna use it
	int compareTo(const Comparable* other) const{
		return 0;
	}
};

void test_CustomerKey() {
	TempKey2 key(3333);  
	TempKey2 same(key);
	TempKey2 different(8888);

	//3333 * 31 = 103323
        
	ASSERT_EQ(103323, key.hashCode());
	ASSERT_TRUE(key.equals(&same));
	ASSERT_FALSE(key.equals(&different));
}

void test_Database_Transaction() {
	DatabaseTransaction dt;

	CustomerKey key(1234);
	std::queue<std::string> queue;
	queue.push("test1");
	queue.push("test2");

	std::queue<std::string>* prev = dt.put(key, queue);
	ASSERT_NULL(prev);

	std::queue<std::string>* get = dt.get(key);
	ASSERT_NOTNULL(get);
	ASSERT_EQ((unsigned) 2, get->size());
	ASSERT_EQ(std::string("test1"), get->front());
	get->pop();
	ASSERT_EQ((unsigned)1, get->size());
	ASSERT_EQ(std::string("test2"), get->front());
	get->pop();
	ASSERT_EQ((unsigned) 0, get->size());
}

int main() {
	///beginning of test

	test_Map();
	test_MovieKey();
	test_DramaMovieKey();
	test_CustomerKey();

	test_Database_Transaction();

	///end of test
	
	std::cout << std::endl << "SUCCESS: " << success << ", FAIL: " << fail;
}

#else

#include <queue>
#include <iostream>

#include "AbstractDatabase.h"
#include "MovieKey.h"
#include "CustomerKey.h"
#include "DatabaseMovie.h"
#include "DatabaseTransaction.h"

void inventory() {

}

int main() {
	std::ifstream file_movies("data4movies.txt");
	if (!file_movies) {
		std::cout << "data4movie.txt couldn't be opened";
		return -1;
	}

	std::ifstream file_customers("data4customers.txt");
	if (!file_movies) {
		std::cout << "data4customers.txt couldn't be opened";
		return -1;
	}

	std::ifstream file_commands("data4commands.txt");
	if (!file_movies) {
		std::cout << "data4commands.txt couldn't be opened";
		return -1;
	}

	DatabaseMovie database_movies;
	//DatabaseCustomer database_customers;
	DatabaseTransaction database_transactions;

	//read movies file
	file_movies >> database_movies;

	//read customers files
	//file_customers >> database_customers;

	//process commands
	char buffer[256];
	
	char actionType = 0;
	int customerId = -1;
	char mediaType = 0;
	char movieType = 0;
	std::string data;
	while (file_commands) {
		file_commands >> actionType;
		switch (actionType) {
		case 'B'://borrow (customerID, media type, movie type, move data)
			file_commands >> customerId;
			file_commands >> mediaType;
			file_commands >> movieType;
			file_commands.getline(buffer, 256);
			data = std::string(buffer);


			break;
		case 'R'://return (customerID, media type, movie type, move data)
			file_commands >> customerId;
			file_commands >> mediaType;
			file_commands >> movieType;
			file_commands.getline(buffer, 256);
			data = std::string(buffer);


			break;
		case 'I'://inventory ()
			std::cout << database_movies;
			break;
		case 'H'://history (customerID)
			file_commands >> customerId;
			//CustomerKey key(customerId);
			//database_transactions.showTransactions(std::cout, &key);
			break;
		default:
			std::cout << "Unknown Command " << actionType << " !" << std::endl;
			continue;
		}
	}
	
	return 0;
}

#endif
