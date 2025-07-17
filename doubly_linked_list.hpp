#include "inventory.hpp"
#include "movie.hpp"

class DoublyLinkedList
{
    private:
    // recursive data structure to hold each chunk of the list
	struct Node {
		Movie datum;	// holds a piece of data
		Node* next;	// holds a pointer to the next chunk
        Node* prev; // holds pointer to the last node
	};

	Node* head;		// first node of the list
    Node* tail;     //last node of the list


    public:

    //default constructor
    DoublyLinkedList();
    
    
    // copy constructor
    DoublyLinkedList(const DoublyLinkedList& other);

    // destructor
    ~DoublyLinkedList();

    // insert movie at end, push_back
    void insert(const Movie&);

    // find first instance of movie return pointer to it, if doesn't exist return null pointer
    const Movie* contains(const std::string& title);

    // find movie and remove from linked list
    void deleteMovie(const Movie& movieToRemove);

    // swap movies
    void swapMovie(const Movie& movie1, const Movie& movie2);

    // returrns size of list
    size_t size() const;

    // prints out list
    void print(std::ostream&) const;



};
