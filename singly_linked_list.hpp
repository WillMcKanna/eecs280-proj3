#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <iostream>
#include "movie.hpp"
#include "inventory.hpp"

class SinglyLinkedList : public Inventory {
private:
	// recursive data structure to hold each chunk of the list
	struct Node {
		Movie datum;	// holds a piece of data
		Node* next;	// holds a pointer to the next chunk
	};

	Node* head;		// first node of the list

public:
	// constructor
	// Initialize head pointer to null
	SinglyLinkedList();

	// tells whether the list is empty or not
	// Check if the head is null, empty if true
	bool empty() const;

	// adds new data to the front of the list
	virtual void insert(const Movie&) override;

	// gets a reference to the *data* value of the front node
	Movie& front();
	
	// removes and deallocates the front node of the list
	void pop_front();
	
	// check if the list contains a particular item
	virtual const Movie* contains(const std::string&) override;

	// pushes all elements from another list onto this one
	void push_all(const SinglyLinkedList&);

	// removes all of the data from the list
	void pop_all();

	// returns the size of the linked list
	virtual size_t size() const override;

	// prints the list to a stream
	virtual void print(std::ostream&) const override;

	// prints the list to a stream in a convenient way
	// NOTE: non-member function
	friend std::ostream& operator<< (std::ostream&, const SinglyLinkedList&);

	// determines if the data contained by one list is the same as in the other
	bool operator== (const SinglyLinkedList&) const;
	
	// calls operator== and negates it
	bool operator!= (const SinglyLinkedList&) const;

	// ***************************************************************************
	// These are "the big three" that make it easier to work with complex data types
	// copy constructor
	SinglyLinkedList(const SinglyLinkedList&);

	// sets this list equal to another one (in a sane way)
	SinglyLinkedList& operator= (const SinglyLinkedList&);
	
	// destructor
	~SinglyLinkedList();
	// ***************************************************************************

	// iterator class is an attribute of the SinglyLinkedList class
	class Iterator
	{
		// allow SinglyLinkedList to access private variables 
		friend class SinglyLinkedList;
	private:
		Node* node;

	public:
		// constructor
		Iterator();

		// constructor starting from a particular node
		Iterator(Node*);

		// adapation of dereference operator
		Movie& operator* () const;

		// prefix iterator increment operator
		Iterator& operator++ ();

		// postfix iterator increment operator
		Iterator& operator++ (int);

		// equality check between two iterators
		bool operator== (Iterator) const;

		// inequality check between two iterators
		bool operator!= (Iterator) const;
	}; // this is an important semicolon

	// get an iterator starting at the beginning of the list
	Iterator begin();

	// get an iterator corresponding to the end of the list (nullptr)
	Iterator end();
};
#endif // SINGLY_LINKED_LIST_HPP
