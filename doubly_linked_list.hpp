#pragma once
#include <iostream>

#include "movie.hpp"


class DoublyLinkedList
{
    private:
    // recursive data structure to hold each chunk of the list
	struct Node 
    {
		Movie datum;	// holds a piece of data
		Node* next;	    // holds a pointer to the next chunk
        Node* prev;     // holds pointer to the last node

        Node(const Movie& d = Movie()) : datum(d), next(nullptr), prev(nullptr) {}; 
	};

	Node* dummy_head;		// first node of the list, make sure to skip
    Node* dummy_tail;     //last node of the list

    int sizeOfList;


    public:

    //default constructor
    DoublyLinkedList();
    
    
    // copy constructor
    DoublyLinkedList(const DoublyLinkedList& other);

    // destructor
    ~DoublyLinkedList();

    // insert movie at end, push_back
    void insert(const Movie& newMovie);

    // find first instance of movie return pointer to it, if doesn't exist return null pointer
    const Movie* contains(const std::string& title);

    // find movie and remove from linked list
    void remove(const Movie& movieToRemove);

    // swap movies
    void swap(const Movie& movie1, const Movie& movie2);

    // prints the list to a stream
    void print(std::ostream& output_stream) const;

    // prints the stream when using <<
    friend std::ostream& operator<< (std::ostream& output_stream, const DoublyLinkedList& list);

    // returrns size of list
    size_t size() const;


    bool empty() const;



};
