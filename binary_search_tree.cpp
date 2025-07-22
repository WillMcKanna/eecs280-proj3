#include "binary_search_tree.hpp"

// default constructor sets root and its sides to nullptr
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
    
    numOfNodes = 0;
}


// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
{
    this->root = nullptr;
    this->numOfNodes = 0;

    if (other.root != nullptr)
    {
        root = copyHelper(other.root);                      // calls copy helper to go down tree inserting nodes, and reassigning pointers when unwinding
        numOfNodes = other.numOfNodes;
    }
   

}

// assignment operator
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) 
{
    // need to delete current existing object heap data, to then reassign


    deleteNodes(root);                                      // call delete nodes to recurisevly delete nodes when going down tree
    this->root = nullptr;
    this->numOfNodes = 0;


    
    if (other.root != nullptr)
    {           
        root = copyHelper(other.root);                              // calls copy helper, similar to copy constructor
        numOfNodes = other.numOfNodes;
    }

    return *(this);
}


// use copy helper to copy nodes in constructor and assignment operator
BinarySearchTree::TreeNode* BinarySearchTree::copyHelper(TreeNode* node)
{
    if (node == nullptr)                                                // base case, once hit go back up
    {
        return nullptr;
    }
    else
    {
        TreeNode* nodeToInsert = new TreeNode(node->datum);             // create new node each time

        nodeToInsert->left = copyHelper(node->left);                    // correctly assign pointers when unwinding copyHelper
        nodeToInsert->right = copyHelper(node->right);

        return nodeToInsert;
    }
}

// destructor
BinarySearchTree::~BinarySearchTree()
{
    deleteNodes(root);                                                  // wrapper to delete nodes
}

void BinarySearchTree::deleteNodes(TreeNode* node) 
{
    if (node == nullptr)                                                // base case, return once hitting nullptr
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)                // make sure node is a leaf node and then delete node, decrement numOfNodes
    {
        delete node;
        numOfNodes--;
        node = nullptr;
    }
    else
    {
        deleteNodes(node->left);                                       // traverse left until we reach base case
        deleteNodes(node->right);                                      // traverse right until we reach base case
        delete node;                                            
        node = nullptr;
    }
}

void BinarySearchTree::insert(const Movie& data) 
{
    root = insertHelper(root, data);                                    // call insert wrapper function
    numOfNodes++;
}

BinarySearchTree::TreeNode* BinarySearchTree::insertHelper(BinarySearchTree::TreeNode* node, const Movie& data)
{
    if (node == nullptr)                                                       // reached nullptr, create new node, assign to node, and return this node address
    {
        node = new TreeNode(data);
    }
    else if (data < node->datum || data == node->datum)                        // assign left pointer of current node to this node -> node created once hit nullptr and return address gets stored in left ptr
    {
        node->left = insertHelper(node->left, data);
    }
    else                                                                       // assign right pointer of current r to this node -> node created once hit nullptr and return address gets stored in right ptr
    {
        node->right = insertHelper(node->right, data);
    }

    return node;
}


const Movie* BinarySearchTree::contains(const std::string& data) 
{
    TreeNode* lastNodeWithName = nullptr;                                                   // assign tempNode to nullptr, in case node isn't in tree
    TreeNode* node = root;                                                                  // start with root
    while (node != nullptr)                                                                 // loop iteratively through tree
    {
        if (node->datum.get_title() == data)                                                // check if current node has same data, if so, reassign node and continue down subtree
        {
            lastNodeWithName = node;
            node = node->right;
        }
        else if (node->datum.get_title() < data)                                            // go right if current node is less than target
        {
            node = node->right;
        }
        else{                                                                               // go left if current node is greater than target
            node = node->left;
        }
    }
    
    return &lastNodeWithName->datum;                                                        // returns address of node with matching name if found, nullptr otherwise
}



void BinarySearchTree::print(std::ostream& os) const 
{
    printTree(os, root);                                                                    // wrapper function for printing nodes
}

size_t BinarySearchTree::size() const 
{
    return numOfNodes;
}

std::ostream& BinarySearchTree::printTree(std::ostream& os, BinarySearchTree::TreeNode* node) const
{
    if (node == nullptr)
    {
        return os;
    }

    os << node->datum << std::endl;                                                         // prints tree in pre-order
    printTree(os, node->left);
    printTree(os, node->right);
    return os;
}
