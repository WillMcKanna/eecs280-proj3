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

        class Iterator {
        public:
            Iterator()
            : root(nullptr), node(nullptr) {}
      
          // EFFECTS:  Returns the current element by reference.
          // WARNING:  Dereferencing an iterator returns an element from the tree
          //           by reference, which could be modified. It is the
          //           responsibility of the user to ensure that any
          //           modifications result in a new value that compares equal
          //           to the existing value. Otherwise, the sorting invariant
          //           will no longer hold.
          Movie& operator*() const {
            return node->datum;
          }
      
          // EFFECTS:  Returns the current element by pointer.
          // WARNING:  Dereferencing an iterator returns an element from the tree
          //           by reference, which could be modified. It is the
          //           responsibility of the user to ensure that any
          //           modifications result in a new value that compares equal
          //           to the existing value. Otherwise, the sorting invariant
          //           will no longer hold.
          // NOTE:     This allows the -> operator to be applied to an iterator
          //           to access a member of the pointed-to element:
          //             BinarySearchTree<std::pair<int, double>> tree;
          //             auto it = tree.insert({ 3, 4.1 });
          //             cout << it->first << endl; // prints 3
          //             cout << it->second << endl; // prints 4.1
          Movie* operator->() const {
            return &node->datum;
          }

          // Prefix ++
          Iterator &operator++() {
            // ** EECS280 IMPLEMENTATION **
            // if (node->right) {
            //   // If has right child, next element is minimum of right subtree
            //   node = min_element_impl(current_node->right);
            // }
            // else {
            //   // Otherwise, look in the whole tree for the next biggest element
            //   node = min_greater_than_impl(root, current_node->datum);
            // }
            
            //return *this;
          }
      
          // Postfix ++ (implemented in terms of prefix ++)
          Iterator operator++(int) {
            Iterator result(*this);
            ++(*this);
            return result;
          }
      
          bool operator==(const Iterator &rhs) const {
            return this->node == rhs.node;
          }
      
          bool operator!=(const Iterator &rhs) const {
            return this->node != rhs.node;
          }

        private:
          friend class BinarySearchTree;
      
          TreeNode *root;
          TreeNode *node;
      
          Iterator(TreeNode *root_in, TreeNode* current_node_in)
            : root(root_in), node(current_node_in) {}
        };

        // Not exactly the same as EECS, might want to check later
        Iterator begin() const {
            return Iterator();
        }
        
        // EFFECTS: Returns an iterator to past-the-end.
        Iterator end() const {
            return Iterator();
        }
};