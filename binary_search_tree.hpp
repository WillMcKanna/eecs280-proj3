#pragma once
#include "movie.hpp"
#include "inventory.hpp"
#include <iostream>

class BinarySearchTree : public Inventory
{
    private:
        struct TreeNode
        
        {
            Movie datum;
            TreeNode* left;
            TreeNode* right;

            TreeNode(Movie data = Movie()) : datum(data), left(nullptr), right(nullptr) {} ;            // create default node, and node with movie passed in
        };

        TreeNode* root;

    public:

        // default constructor
        BinarySearchTree();



        /* BIG THREE for Binary Search Tree */

        // copy constructor
        BinarySearchTree(const BinarySearchTree& other);

        // assignment operator
        BinarySearchTree& operator=(const BinarySearchTree& other);

        // destructor
        ~BinarySearchTree();

        



};