#include "doubly_linked_list.hpp"

DoublyLinkedList::DoublyLinkedList()
{
    // dummy_head is always at beginning of list, skip over when iterating
    // dummy_tail is always at end of list, stop iteration once hit
    // make sure they point at each other whem empty, and when constructing

    dummy_head = new Node(Movie());
    dummy_tail = new Node(Movie());

    // next and prev are initalized as nullptr
    dummy_head->next = dummy_tail;
    dummy_head->prev = nullptr;

    dummy_tail->prev = dummy_head;
    dummy_tail->next = nullptr;

    sizeOfList = 0;
    
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) : dummy_head(new Node(Movie())), dummy_tail(new Node(Movie()))
{
    sizeOfList = 0;

    // should point at each other and also have nullptr in front of dummy_head and after dummy_tail
    dummy_head->next = dummy_tail;
    dummy_head->prev = nullptr;

    dummy_tail->prev = dummy_head;
    dummy_tail->next = nullptr;


    Node* currentNode = other.dummy_head->next;

    // inserts new node before dummy_tail and after last current node, fixes pointer in functions
    while (currentNode != other.dummy_tail)
    {
        this->insert(currentNode->datum);
        currentNode = currentNode->next;
    }
    
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

 
 // insert new node before dummy_tail and after last node, perserve order
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

    while (curr != dummy_tail)
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
void DoublyLinkedList::remove(const Movie& movieToRemove)
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
    else
    {
        std::cerr << "Movie does not exist in user's list." << std::endl;
    }
    return;
    
}

// only call if both movies are in inventory
void DoublyLinkedList::swap(const Movie& movie1, const Movie& movie2)
{

    
    if (!contains(movie1.get_title()) || !contains(movie2.get_title()))                             // list must comtain both movie titles
    {
        std::cerr << "A movie input does not exist." << std::endl;
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

    

    // if movie1 comes right before movie2
    if (movie1Node->next == movie2Node)
    {
        Node* tempPrevPtr = movie1Node->prev;
        Node* tempNextPtr = movie2Node->next;

        movie1Node->next = tempNextPtr;
        movie1Node->prev = movie2Node;
        
        movie2Node->next = movie1Node;
        movie2Node->prev = tempPrevPtr;

        tempPrevPtr->next = movie2Node;
        tempNextPtr->prev = movie1Node;
    }
    // if movie1 comes right after movie2
    else if (movie1Node->prev == movie2Node)
    {
        Node* tempPrevPtr = movie2Node->prev;
        Node* tempNextPtr = movie1Node->next;

        movie2Node->next = tempNextPtr;
        movie2Node->prev = movie1Node;

        movie1Node->next = movie2Node;
        movie1Node->prev = tempPrevPtr;

        tempPrevPtr->next = movie1Node;
        tempNextPtr->prev = movie2Node;
    }
    // not adjacent
    else
    {
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

}



void DoublyLinkedList::print(std::ostream& output_stream) const
{
    
    for (Node* node = dummy_head->next; node != dummy_tail; node = node->next) {
        if (node->next != dummy_tail) 
        {
            output_stream << node->datum << std::endl;
        }
        else 
        {
            output_stream << node->datum;
        }
    }
    
}


std::ostream& operator<< (std::ostream& output_stream, const DoublyLinkedList& list)
{
    list.print(output_stream);
    return output_stream;
}




size_t DoublyLinkedList::size() const 
{
    return sizeOfList;
}

bool DoublyLinkedList::empty() const
 {
    return (dummy_head->next == dummy_tail);
 }

DoublyLinkedList::Iterator::Iterator() : node(nullptr) {}

DoublyLinkedList::Iterator::Iterator(Node* _node) : node(_node) {}

DoublyLinkedList::Iterator DoublyLinkedList::begin() {
    return this->dummy_head;
}

DoublyLinkedList::Iterator DoublyLinkedList::end() {
    return this->dummy_tail;
}

Movie& DoublyLinkedList::Iterator::operator*() const {
    return node->datum;
}

DoublyLinkedList::Iterator& DoublyLinkedList::Iterator::operator++() {
    node = node->next;
    return *this;
}

DoublyLinkedList::Iterator& DoublyLinkedList::Iterator::operator--() {
    node = node->prev;
    return *this;
}

DoublyLinkedList::Iterator& DoublyLinkedList::Iterator::operator--(int) {
    node = node->prev;
    return *this;
}

// check if one iterator is at the same position as another
//   just compare them on the basis of the address of the nodes the represent
bool DoublyLinkedList::Iterator::operator== (DoublyLinkedList::Iterator other) const
{
    if (this->node == other.node) {
        return true;
    }
    else {
        return false;
    }
}

// check if one iterator is NOT at the same position as another
//   calls and negates operator==
bool DoublyLinkedList::Iterator::operator!= (DoublyLinkedList::Iterator other) const
{
    return !(*this == other);
}






