#pragma once
#include "movie.hpp"
#include "inventory.hpp"
#include <iostream>
#include <vector>

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
            Iterator(BinarySearchTree::TreeNode* rootNode) 
            {
                index = 0;
                BinarySearchTree::TreeNode* tempNode = rootNode;
                populateTree(tempNode);
            }

            void populateTree(BinarySearchTree::TreeNode* node) 
            {
                // go all the way down and save smallest value
                // than go all the way down until the node which the ->left = the smallest value
                // at that point go right, then keep goin left

                if (node == nullptr) {
                    return;
                }

                populateTree(node->left);
                movies.push_back(node);
                populateTree(node->right);
            } 
      
          // EFFECTS:  Returns the current element by reference.
          // WARNING:  Dereferencing an iterator returns an element from the tree
          //           by reference, which could be modified. It is the
          //           responsibility of the user to ensure that any
          //           modifications result in a new value that compares equal
          //           to the existing value. Otherwise, the sorting invariant
          //           will no longer hold.
          Movie& operator*() const {
            return movies[index]->datum;
          }

          // Prefix ++
          Iterator &operator++() {
            index++;
            return *this;
          }
      
          // Postfix ++ (implemented in terms of prefix ++)
          Iterator operator++(int) {
            Iterator temp = *this;
            this->index++;
            return temp;
          }
      
          bool operator==(const Iterator &rhs) const {
            return (this->index == rhs.index);
          }
      
          bool operator!=(const Iterator &rhs) const {
            return !(this->index == rhs.index);
          }


        private:
          friend class BinarySearchTree;
          std::vector<BinarySearchTree::TreeNode*> movies;
          int index;
        };

        Iterator begin() const {
            return Iterator(root);
        }
        // EFFECTS: Returns an iterator to past-the-end.
        Iterator end() const {
            Iterator it(root);
            it.index = it.movies.size();
            
            return it;
        }
};