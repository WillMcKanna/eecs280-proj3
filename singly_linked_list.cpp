#include "singly_linked_list.hpp"

// constructor
SinglyLinkedList::SinglyLinkedList()
{
    this->head = nullptr;
}

// tells whether the list is empty or not
bool SinglyLinkedList::empty() const
{
    if (this->head == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

// adds new data to the front of the list
void SinglyLinkedList::push_front(Movie& datum)
{
    // Create a new node
    Node* tempNode = new Node();
    // Set node's datum to new datum
    tempNode->datum = datum;
    // Set node's pointer to current head
    tempNode->next = this->head;
    // Set the node's head to the new node
    this->head = tempNode;
}

// gets a reference to the *data* value of the front node
Movie& SinglyLinkedList::front()
{
    return this->head->datum;
}

// removes and deallocates the front node of the list
void SinglyLinkedList::pop_front()
{
    if (!empty()) {
        // Stores the new head in a temp value
        Node* nextNode = this->head->next;

        // Deletes the old head and sets equal to null
        delete head;
        head = nullptr;

        // Sets head equal to the temp value
        this->head = nextNode;
    }
}

// check if the list contains a particular item
bool SinglyLinkedList::contains(const Movie& datum) const
{
    // Creates a temporary variable 
    Node* tempNode = this->head;

    if (empty()) {
        return false;
    }

    while (tempNode != nullptr) {
        if (tempNode->datum == datum) {
            return true;
        }
        tempNode = tempNode->next;
    }

    return false;
}

// pushes all elements from another list onto this one
void SinglyLinkedList::push_all(const SinglyLinkedList& other)
{
    // Creates a pointer to the head of the other list
    Node* tempNode = other.head;

    // While the node isnt null, pushes node to the front
    while (tempNode != nullptr) {
        push_front(tempNode->datum);
        tempNode = tempNode->next;
    }

    return;
}

// removes all of the data from this list
void SinglyLinkedList::pop_all()
{
    // While the list is not empty, deletes the front element of the list
    while (!empty()) {
        pop_front();
    }

    return;
}

// prints the list to a stream
void SinglyLinkedList::print(std::ostream& output_stream) const
{
    output_stream << "[";
    for (Node* node = head; node != nullptr; node = node->next) {
        if (node->next != nullptr) {
            output_stream << node->datum << ", ";
        }
        else {
            output_stream << node->datum;
        }
    }
    output_stream << "]";
}

// prints the list to a stream in a convenient way
std::ostream& operator<< (std::ostream& output_stream, const SinglyLinkedList& list)
{
    list.print(output_stream);
    return output_stream;
}

bool SinglyLinkedList::operator== (const SinglyLinkedList& other) const
{
    Node* otherNode = other.head;
    for (Node* node = head; node != nullptr; node = node->next) {
        if (node->datum != otherNode->datum.get_title()) {                              // shouldn't otherNode be set to otherNode->next?3
            return false;
        }

        // If lists are not the same size, they are not the same list
        if (otherNode == nullptr) {
            return false;
        }
        otherNode = otherNode->next;
    }

    return true;
}

// check if two lists are not equal by first checking if they are equal
//   and then negating the result
bool SinglyLinkedList::operator!= (const SinglyLinkedList& other) const
{
    return !(*this == other);
}

// copy constructor
SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr)
{
    this->push_all(other);
}

// sets this list equal to another one (in a sane way)
SinglyLinkedList& SinglyLinkedList::operator= (const SinglyLinkedList& other)
{
    this->pop_all();
    this->push_all(other);
    return *this;
}

// destructor
SinglyLinkedList::~SinglyLinkedList()
{
    this->pop_all();
}

// constructor
SinglyLinkedList::Iterator::Iterator() : node(nullptr)
{

}

// constructor from a node pointer
SinglyLinkedList::Iterator::Iterator(Node* _node) : node(_node)
{

}

// the beginning of the linked list is the head
SinglyLinkedList::Iterator SinglyLinkedList::begin()
{
    return this->head;
}

// the end of a linked list is always a nullptr
SinglyLinkedList::Iterator SinglyLinkedList::end()
{
    return nullptr;
}

// get the data value of a node via an iterator
Movie& SinglyLinkedList::Iterator::operator*() const
{
    return node->datum;
}

// move an iterator to the next node
//   this is the prefix operator, i.e., ++iterator
SinglyLinkedList::Iterator& SinglyLinkedList::Iterator::operator++ ()
{
	node = node->next;
    return *this;
}

// move an iterator to the next node
//   this is the postfix operator, i.e., iterator++
SinglyLinkedList::Iterator& SinglyLinkedList::Iterator::operator++ (int)
{
    node = node->next;
    return *this;
}

// check if one iterator is at the same position as another
//   just compare them on the basis of the address of the nodes the represent
bool SinglyLinkedList::Iterator::operator== (SinglyLinkedList::Iterator other) const
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
bool SinglyLinkedList::Iterator::operator!= (SinglyLinkedList::Iterator other) const
{
    return !(*this == other);
}
