#include <iostream>
#include <string>

class Person
{
    public:

        Person(std::string n = "n/a", int a = 0) : name(n), age(a) {};
        friend std::ostream& operator<<(std::ostream& os, const Person& p);

        void setName(std::string newName)
        {
            name = newName;
        }

        void setAge(int newAge)
        {
            age = newAge;
        }


    private:
        std::string name;
        int age;

};
  
std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << "Name: " << p.name << ", Age: " << p.age << std::endl;
    
    return os;
}



template <typename T>
class LinkedList 
{
  
  public:

    LinkedList() : dummy_head(nullptr)
    {
        dummy_head = new Node(T());                         // call default constructor on whatever type T is

        
    }


    LinkedList(const LinkedList& l2) : dummy_head(nullptr)
    {
        Node* newDummyHead = new Node(T());
        this->dummy_head = newDummyHead;

        Node* newLLIter = newDummyHead;        
        Node* oldLLIter = l2.dummy_head->next;

        while (oldLLIter)
        {
            Node* newNode = new Node(oldLLIter->value);
            newLLIter->next = newNode;

            oldLLIter = oldLLIter->next;
            newLLIter = newNode;
        }

    }

    // delete old stuff and reassign to new object
    // LinkedList& operator=(const LinkedList& l2)
    // {

    // }

    ~LinkedList()
    {
        Node* curr = dummy_head;
        std::cout << "Destructor called." << std::endl;
        while (curr)
        {
            Node* temp = curr->next;
            std::cout << "Deleted: " << curr->value << std::endl;
            delete curr;

            curr = temp;
        }

    }



    void push_front(const T &datum)
    {
        Node* newNode = new Node(datum);

        if (dummy_head->next == nullptr)                 // no nodes currently
        {   
            dummy_head->next = newNode;
        }

        else
        {
            Node* firstNode = dummy_head->next;               // insert new Node between dummy_head and first node
            dummy_head->next = newNode;
            newNode->next = firstNode;
        }
    }
    
    void push_back(const T &datum)
    {
        Node* newNode = new Node(datum);

        if (dummy_head->next == nullptr)                  // no nodes currently
        {
            dummy_head->next = newNode;
        }

        else
        {
            Node* curr = dummy_head->next;

            while (curr->next)                          // go until the last node
            {
                curr = curr->next;
            }

            curr->next = newNode;
        }
 
    }

    void pop_front()
    {
        if (dummy_head->next)
        {
            Node* front_node = dummy_head->next;
            dummy_head->next = front_node->next;

            delete front_node;
        }
        else{
            throw std::runtime_error("No exisiting node.");
        }
    }

    void pop_back()
    {
        if (dummy_head->next)                   // nodes exist
        {
            Node* prev = dummy_head;
            Node* curr = dummy_head->next;

            while (curr->next)                  // stop when you get to last node, prev will be penultimate node
            {
                prev = prev->next;
                curr = curr->next;
            }

            prev->next = nullptr;
            delete curr;
            
        }

        else
        {
            throw std::runtime_error("No existing node.");
        }
    }

    
    
    void toStr()
    {
        for (Iterator it = this->dummy_head->next; it != Iterator (nullptr); ++it)
        {
            std::cout << *it << std::endl;
        }
        
    }

  
  private:

    struct Node
    {
        T value;              // should be able to hold any object type
        Node* next = nullptr;

        Node(const T& v = T()) : value(v) {};         // call default constructor of whatever T is

    };

    Node* dummy_head;





    class Iterator{

        public:

            Iterator(Node* node = nullptr) : nodeptr(node) {};

            T & operator*()
            {
                if (nodeptr == nullptr)
                {
                    throw std::runtime_error("Cannot dereference null pointer.");
                }
                return nodeptr->value;
            }

            // prefix increment
            Iterator& operator++()
            {
                if (nodeptr == nullptr)
                {
                    throw std::runtime_error("Cannot increment null pointer.");
                }
                nodeptr = nodeptr->next;
                return *this;
            }

            bool operator==(const Iterator& rhs) const
            {
                return (nodeptr == rhs.nodeptr);
            }

            bool operator!=(const Iterator& rhs) const
            {
                return (nodeptr != rhs.nodeptr);
            }

        private:
            Node* nodeptr;

        };
  
};








template <typename T>
class DoublyLinkedList
{
    public:

    DoublyLinkedList() 
    {
        dummy_head = new Node(T());
        dummy_tail = new Node(T());

        dummy_head->next = dummy_tail;
        dummy_head->prev = nullptr;                             // defaulted to nullptr, so redudant

        dummy_tail->prev = dummy_head;
        dummy_tail->next = nullptr;                             // defaulted to nullptr

    }



    void push_front(const T& datum)
    {
        Node* newNode = new Node(datum);    
        Node* firstNode = dummy_head->next;                     // if empty, gets set as dummy_tail

        dummy_head->next = newNode;
        newNode->prev = dummy_head;

        newNode->next = firstNode;
        firstNode->prev = newNode;


        
    }

    void push_back(const T& datum)
    {
        Node* newNode = new Node(datum);
        Node* lastNode = dummy_tail->prev;

        lastNode->next = newNode;
        newNode->prev = lastNode;


        dummy_tail->prev = newNode;
        newNode->next = dummy_tail;


    }

    void pop_front()
    {
        if (dummy_head->next == dummy_tail)                     // no nodes to remove
        {
            throw std::runtime_error("No node to remove.");
        }

        Node* firstNode = dummy_head->next;                     // can't be dummy_tail if got here
        Node* secondNode = firstNode->next;                     // can be dummy_tail if list has 1 value

        dummy_head->next = secondNode;
        secondNode->prev = dummy_head;

        delete firstNode;
       
    }


    void pop_back()
    {
        if (dummy_tail->prev == dummy_head)                 // no nodes to remove
        {
            throw std::runtime_error("No node to remove");
        }

        Node* lastNode = dummy_tail->prev;                 // cant be dummy_head        
        Node* penultimateNode = lastNode->prev;            // can be dummy_head


        dummy_tail->prev = penultimateNode;
        penultimateNode->next = dummy_tail;

        delete lastNode;

    }

    void toStr()
    {
        for (Iterator it = dummy_head->next; it != dummy_tail; ++it)
        {
            std::cout << *it << std::endl;
        }
        
    }


    

    private:

    struct Node
    {
        T datum;
        Node* next = nullptr;
        Node* prev = nullptr;


        Node(const T& v = T()) : datum(v) {}; 
    };

        Node* dummy_head;
        Node* dummy_tail;




    class Iterator
    {

    public:

        Iterator(Node* node = nullptr) : nodeptr(node) {};

        T & operator*()
        {
            if (nodeptr == nullptr)
            {
                throw std::runtime_error("Cannot dereference null pointer.");
            }
            return nodeptr->datum;
        }

        // prefix increment
        Iterator& operator++()
        {
            if (nodeptr == nullptr)
            {
                throw std::runtime_error("Cannot increment null pointer.");
            }
            nodeptr = nodeptr->next;
            return *this;
        }

        bool operator==(const Iterator& rhs) const
        {
            return (nodeptr == rhs.nodeptr);
        }

        bool operator!=(const Iterator& rhs) const
        {
            return (nodeptr != rhs.nodeptr);
        }

    private:
        Node* nodeptr;

    };

};



class BinarySearchTree
{
    
    public:
        
        // MODIFIES: Default constructor, set default values
        BinarySearchTree() : root(nullptr) {};

        ~BinarySearchTree()
        {
            // iterate through a tree and delete each node
        }

        bool empty() const
        {
            return root == nullptr;                                            // no nodes exist
        }

        int size() const
        {
            return sizeHelper(root);
        }

        bool contains(const int& value) const
        {
            
            return containsHelper(root, value);
        }

        void insert(const int& value) 
        {
            root = insertHelper(root, value);
        }

        void toStr()
        {
            print(std::cout, root);
        }

    private:
        struct Node
        {
            int value;
            Node* left;
            Node* right;

            Node(int v = 0) : value(v), left(nullptr), right(nullptr) {} ;
        };

        Node* root;

        int sizeHelper(Node* r) const
        {
            if (r == nullptr)                               // R is not a node, base case
            {
                return 0;
            }                                               // recursive step, add 1 and down left and all the way down right, go up 1 and repeat

            return 1 + sizeHelper(r->left) + sizeHelper(r->right);
        }


        bool containsHelper(Node* r, const int& val) const
        {
            if (r == nullptr)
            {
                return false;
            }
            
            if (r->value == val)
            {
                return true;
            }

            else if (val < r->value)                    // if value is less than current node, node must be in left subtree if exists
            {
                return containsHelper(r->left, val);
            }
            
            else                                      // if value is greater tha current node, value must be in right subtree if exists
            {
                return containsHelper(r->right, val);
            }


        }


        Node* insertHelper(Node* r, const int& val)
        {
            
            if (r == nullptr)                                   // reached nullptr, create new node, assign to r, and return this node address
            {
                r = new Node(val);
               
            }
            
            else if (val <= r->value)
            {
                r->left = insertHelper(r->left, val);           // assign left pointer of current r to this node -> node created once hit nullptr and return address gets stored in left ptr
            }
            else
            {
                r->right = insertHelper(r->right, val);         // assign right pointer of current r to this node -> node created once hit nullptr and return address gets stored in right ptr
            }

            return r;                                           // return r to correctly assign each pointer when going back up
        }


        std::ostream& print(std::ostream& os, Node* r)
        {
            if (r == nullptr)
            {
                return os;
            }
            
            

            os << r->value << std::endl;
            print(os, r->left);
            print(os, r->right);
            return os;
        }


        
};



int main() 
{
    BinarySearchTree bst1;
    bst1.insert(15);            // root
    bst1.insert(12);            // root left child
    bst1.insert(20);            // root right child
    bst1.insert(10);            // 12 left child
    bst1.insert(14);            // 12 right child, goes down left of 15, then right of 12
    bst1.insert(11);            // down left of 15, left of 12, right of 10

    bst1.toStr();

    return 0;
}

