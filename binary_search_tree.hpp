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
        int numOfNodes;


        /* Helper Functions */
        TreeNode* insertHelper(TreeNode* node, const Movie& data);

        TreeNode* containsHelper(TreeNode* node, const std::string& data);

 

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
        
        // helper functions for big 3
        TreeNode* copyHelper(TreeNode* node);
        void deleteNodes(TreeNode* node);


        /* Pure Virtual functions inhereited from Inventory */

        // insert movie into tree
        void insert(const Movie&) override;

        // iterate through tree to find movie
        const Movie* contains(const std::string&) override;

        // prints Movie info from tree nodes
        void print(std::ostream&) const override;

        //
        std::ostream& printTree(std::ostream& os, TreeNode* node) const;

        // returns the size of the binary search tree
        size_t size() const override;

};