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
        root = copyHelper(other.root);
        numOfNodes = other.numOfNodes;
    }
   

}

// assignment operator
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) 
{
    deleteNodes(root);
    this->root = nullptr;
    this->numOfNodes = 0;


    if (other.root != nullptr)
    {
        root = copyHelper(other.root);
        numOfNodes = other.numOfNodes;
    }

    return *(this);
}

BinarySearchTree::TreeNode* BinarySearchTree::copyHelper(TreeNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        TreeNode* nodeToInsert = new TreeNode(node->datum);

        nodeToInsert->left = copyHelper(node->left);
        nodeToInsert->right = copyHelper(node->right);

        return nodeToInsert;
    }
}

// destructor
BinarySearchTree::~BinarySearchTree()
{
    deleteNodes(root);
}

void BinarySearchTree::deleteNodes(TreeNode* node) 
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        delete node;
        numOfNodes--;
        node = nullptr;
    }
    else
    {
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
        node = nullptr;
    }
}

void BinarySearchTree::insert(const Movie& data) 
{
    root = insertHelper(root, data);
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
    const Movie* tempMoviePtr = &(containsHelper(root, data)->datum);
    return tempMoviePtr;
}

BinarySearchTree::TreeNode* BinarySearchTree::containsHelper(BinarySearchTree::TreeNode* node, const std::string& data) 
{

    // method 1
    // if (node == nullptr)
    // {
    //     return nullptr;
    // }

    // if ((node->datum).get_title() == data)
    // {
    //     TreeNode* currNode = node;
    //     node = node->left;
    //     while (node)
    //     {
    //         if (node->datum.get_title() == data)
    //         {
    //             currNode = node;
    //             node = node->left;
    //         }
    //         else if (node->datum.get_title() < data)
    //         {
    //             node = node->right;
    //         }
    //         else
    //         {
    //             node = node->left;
    //         }

    //     }
    //     return currNode;
        
    // }
    
    // if ((node->datum).get_title() < data)
    // {
    //     return containsHelper(node->right, data);
    // }
    // else
    // {
    //     return containsHelper(node->left, data);
    // }



    TreeNode* lastNodeWithName = nullptr;

    while (node != nullptr)
    {
        if (node->datum.get_title() == data)
        {
            lastNodeWithName = node;
            node = node->left;
        }
        else if (node->datum.get_title() < data)
        {
            node = node->right;
        }
        else{
            node = node->left;
        }
    }
    
    return lastNodeWithName;
}

void BinarySearchTree::print(std::ostream& os) const 
{
    printTree(os, root);
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

    os << node->datum << std::endl;
    printTree(os, node->left);
    printTree(os, node->right);
    return os;
}













