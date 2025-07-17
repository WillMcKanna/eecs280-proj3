#include "doubly_linked_list.hpp"

DoublyLinkedList::DoublyLinkedList()
{
    dummy_head = new Node(Movie());                         // dummy_head is always at beginning of list, skip over when iterating
    dummy_tail = new Node(Movie());                         // dummy_tail is always at end of list, stop iteration once hit

    
    dummy_head->next = dummy_tail;
    dummy_head->prev = nullptr;

    dummy_tail->prev = dummy_head;
    dummy_tail->next = nullptr;

    sizeOfList = 0;
    
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* curr = dummy_head;

    // deletes dummy_head and dummy_tail and all nodes that were created on heap in list
    while (curr)
    {
        Node* temp = curr->next;

        delete curr;
        curr = nullptr;

        curr = temp;
    }
}

 
 void DoublyLinkedList::insert(const Movie& newMovie)
 { 

    Node* newNodeMovie = new Node(newMovie);

    Node* lastNode = dummy_tail->prev;                                          // if empty, lastNode will be dummy_head

    lastNode->next = newNodeMovie;
    newNodeMovie->prev = lastNode;

    newNodeMovie->next = dummy_tail;
    dummy_tail->prev = newNodeMovie;
    
    sizeOfList++;
 }


 const Movie* DoublyLinkedList::contains(const std::string& title)
 {

    Node* curr = dummy_head->next;

    while (curr)
    {
        if(curr->datum.get_title() == title)
        {
            return &(curr->datum);
        }
        curr = curr->next;
  
    }
    return nullptr;

 }


// only call if movie exists in inventory
void DoublyLinkedList::deleteMovie(const Movie& movieToRemove)
{
    if (contains(movieToRemove.get_title()))                           // only look to remove a movie if it exists (not nullptr)
    {
        Node* curr = dummy_head->next;
        
        while (curr != dummy_tail)                                     // keeps iterating 
        {
            if (curr->datum == movieToRemove)
            {
                
                Node* previousNode = curr->prev;
                Node* nextNode = curr->next;

                previousNode->next = nextNode;
                nextNode->prev = previousNode;

                delete curr;
                curr = nullptr;

                sizeOfList--;
                
                return;

            }
           
            curr = curr->next;
        }
    }

    return;
    
}

// only call if both movies are in inventory
void DoublyLinkedList::swapMovie(const Movie& movie1, const Movie& movie2)
{

    
    if (!contains(movie1.get_title()) || !contains(movie2.get_title()))                             // list must comtain both movie titles
    {
        return;
    }

    Node* movie1Node = nullptr;
    Node* movie2Node = nullptr;

    Node* currNode = dummy_head->next;

    while (currNode != dummy_tail)
    {
        if (currNode->datum == movie1)
        {
            movie1Node = currNode;
            break;
        }
      currNode = currNode->next;    
    }

    currNode = dummy_head->next;

    while (currNode != dummy_tail)
    {
        if (currNode->datum == movie2)
        {
            movie2Node = currNode;
            break;
        }
      currNode = currNode->next; 
    }

    Node* movie1NodePrev = movie1Node->prev;
    Node* movie1NodeNext = movie1Node->next;

    Node* movie2NodePrev = movie2Node->prev;
    Node* movie2NodeNext = movie2Node->next;


    movie1NodeNext->prev = movie2Node;
    movie1NodePrev->next = movie2Node;
    
    movie2NodeNext->prev = movie1Node;
    movie2NodePrev->next = movie1Node;
    

    
    movie2Node->prev = movie1NodePrev;
    movie2Node->next = movie1NodeNext;

    movie1Node->next = movie2NodeNext;
    movie1Node->prev = movie2NodePrev;
}




size_t DoublyLinkedList::size() const 
{
    return sizeOfList;
}

bool DoublyLinkedList::empty() const
 {
    return (dummy_head->next == dummy_tail);
 }






