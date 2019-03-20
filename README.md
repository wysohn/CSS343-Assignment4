Team SMG: Jeremiah Griffith, Tony Moon, Wooyoung Son

# Inventory Tracking System Proposal
Inventory Tracking System (ITS) is a system which is separated into two parts: the front-end and back-end. The front-end portion of the system will directly interact with the user and responsible for utilizing the methods provided by back-end portion of the system to gather and organize the DVD related information, such as tracking the number of DVDs left, borrowing and returning the DVDs, sorting the DVDs by appropriate format, etc. each database will consist of a Map, which is a data structure which stores key-value pair, and when our team will implement the Map, we are going to use hashing algorithm so that the read/write access will be O(1), thereby providing instantaneous access to the data values without much computational overhead. Our InventoryDriver class has main() method, which will drive the system by invoking the methods of databases appropriately. 

# Class Diagram
## System Classes
![alt text](https://github.com/wysohn/CSS343-Assignment4/blob/master/Classes_System.jpg)

## Data Clases
![alt text](https://github.com/wysohn/CSS343-Assignment4/blob/master/Classes_Data.jpg)

# Class Description
## System Classes
* `AbstractDatabase<Hashable, V>` - This class acts as an abstract class overarching the databases of this project,including movies, customers, etc. It holds the structure of a map, where the key isa hashable value, and the value is to be defined in the children classes. Itincludes the functions shared by the children classes, whose individualimplementation will be defined within the children (ex. input/output, get/set).

* `DatabaseMovie<MovieKey, int>`-This class acts as a database for all movies in the stock. Within this class, wehave std::vector, which is added to sort the MovieKey, along with the Mapinherited from the parent class to control the movie stock. Movies are sortedbased on the algorithms provided in the assignment doc, and may be searchedfor based on distinct keys assigned to them.-The sort() method is responsible for sorting the values in the std::vector, and weare going to implement it by using the std::sort() method provided by STL, whichworks with std::vector, yet we are going to provide custom comparator, thefunction, so that we can sort the MovieKeys in the order provided in theassignment doc.

* `DatabaseCustomer<CustomerKey, CustomerInfo>`-This class acts as a database for all customers interacting with the movie stock.Customers are stored based on their distinct ID number using CustomerKey, andthe corresponding CustomerInfo identifies them by first and last name. Thisnumber acts as the key value to be search, if necessary.

* `DatabaseTransaction<CustomerKey, std::queue<std::string>>`-This class acts as a database for all transactions which occur on the movie stockcontents. Transactions are held within a queue structure, as the transactionhistory should be available in the order of occurrence. The key for searching willbe the CustomerKey, the ID number of the customer whose history is beingsearched, and the value will be a queue containing the transaction history of saidcustomer.

## Data Classes

* `Hashable` - An interface that represent any class that can be ‘hashed.’ Since this is aninterface, the children classes must implement their own hashCode() and
TeamSMGJeremiah Griffith, Tony Moon, Wooyoung Sonequals() method in order to make themselves as ‘hashable’ object. ThehashCode() produce the integer value that is as unique as possible, and theequals() method will be used for probing the hashtable when there are more thanone distinctive value, which are stored in linked list, exist for one hash valueexists.

* `Comparable` - An interface that represent any class that can be compared with anotherComparable. Any children classes must implement comapreTo() method tocompare itself with any other Comparable classes. Depending on the context, themethod should return -1 if the current class is smaller than the class it’scomparing with, 0 if the current class is exactly the same with the class it’scomparing with, and 1 if the current class is larger than the class it’s comparingwith. The value returned is completely depending on the implementation of thechildren classes.

* `CustomerKey` - The wrapper class that will hold the customer ID number, which is a std::string.This class act as an adaptor to implement Hashable and Comparable interfacesas std::string is from the shared library, which we do not have any control.

* `CustomerInfo` - The class represent the details of the customer. It contains the customer ID, theirfirst name, and their last name.

* `MovieKey` - The abstract representation of the any movie’s key. All movies have title, year,and director by default, so we decided to put these shared fields into the abstractclass. By doing so, we can assume that any MovieKey must have title, year, anddirector regardless of their movie type.

* `ClassicMovieKey` - The class represent the Classic Movie. Classic movie, apart from the sharedfields like title, year, and director, has month and actor specific to the ClassicMovie.

* `ComedyMovieKey` - The class represent the Comedy

* `DramaMovieKey` - The class represent the Drama

# How to use
## Compile
* Environment: Linux
* Requirements: gcc, g++, or any c++ compatible compilers

1. Download the source codes
2. Move to the folder where source codes are saved
3. If you are using gcc, do `g++ *.cpp`. If you are using something other than gcc, make sure to compile all the cpp files at the same time.
4. Run executable that has the name whatever you have chosen. Default is usually a.out. If it is default output, do `./a.out`

## Data Files
In order for the program to run properly, it has to read the three files that is formatted according to the specification. Examples are attached together with the source codes.

### data4movies.txt
This text file consist of all the movies to be loaded on the system. There are three types of movies currently supported:
1. F - Comedy
2. D - Drama
3. C - Classic

Each line indicates a movie, and they have to be formatted accordingly based on their type. Each elements are separated by comma(,). The first element indicates one of the type of movies listed above.

##### Comedy
Stock, Director, Title, Year of release

`F, 10, Nora Ephron, You've Got Mail, 1998`

##### Drama
Stock, Director, Title, Year of release

`D, 10, Steven Spielberg, Schindler's List, 1993`

##### Classic
Stock, Director, Title, Major actor and Release date

`C, 10, George Cukor, Holiday, Cary Grant 9 1938`

### data4customers.txt
The text file consist of customers who are able to borrow movies.

Each line consist of each customer, and each elements are separated by comma(,).

##### Format
CustomerID, First name, Last name

`3333 Witch Wicked`

### data4commands.txt
The text file consist of actions to make with this program. These are the currently supported types of commands:
1. B (Borrow): Borrow a movie.
2. R (Return): Return a borrowed movie.
3. I (Inventory): Show all the available movies.
4. H (History): Show history of borrow/return.

##### Borrow
Borrow movie to the specified customer.

* `CustomerID MediaType MovieType Data`
* * CustomerID: the customer who is borrowing the movie
* * MediaType: the type of media. Currently only support DVD(D)
* * MovieType: the type of movie loaded in movie data
* * Data: the data of the movie. The format is same as movie data.

`B 8000 D F You've Got Mail, 1998`

##### Return
Return the movie borrowed.

* `CustomerID MediaType MovieType Data`
* * CustomerID: the customer who is returning the movie
* * MediaType: the type of media. Currently only support DVD(D)
* * MovieType: the type of movie loaded in movie data
* * Data: the data of the movie. The format is same as movie data.

`R 5000 D C 3 1971 Ruth Gordon`

##### Inventory
List every movies available.

##### History
List history of borrow/return of the specified customer.

* `CustomerID`
* * CustomerID: the customer to look up

`H 5000`
