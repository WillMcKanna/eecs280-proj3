#include <iostream>


class BinarySearchTree1
{
    private:
        struct TreeNode
        
        {
            int datum;
            TreeNode* left;
            TreeNode* right;

            TreeNode(int data = 0) : datum(data), left(nullptr), right(nullptr) {} ;            // create default node, and node with movie passed in
        };

        TreeNode* root;
        int numOfNodes;



 

    public:

        // default constructor
        BinarySearchTree1()
        {
            root = nullptr;
            numOfNodes = 0;
        }


        /* BIG THREE for Binary Search Tree */

        // copy constructor
        BinarySearchTree1(const BinarySearchTree1& other)
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
        BinarySearchTree1& operator=(const BinarySearchTree1& other)
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

        // destructor
        ~BinarySearchTree1()
        {
            deleteNodes(root);
        }
        
        // helper functions for big 3
        TreeNode* copyHelper(TreeNode* node)
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
        
        void deleteNodes(TreeNode* node)
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


        /* Pure Virtual functions inhereited from Inventory */

        // insert movie into tree
        void insert(const int& data)
        {
                root = insertHelper(root, data);
                numOfNodes++;
        }

        TreeNode* insertHelper(TreeNode* node, const int& data)
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

        // iterate through tree to find movie
        const int* contains(const int& data)
        {
                const int* tempMoviePtr = &(containsHelper(root, data)->datum);
                return tempMoviePtr;
        }

        TreeNode* containsHelper(TreeNode* node, const int& data)
        {

            TreeNode* lastNodeWithName = nullptr;

            while (node != nullptr)
            {
                if (node->datum == data)
                {
                    lastNodeWithName = node;
                    node = node->left;
                }
                else if (node->datum < data)
                {
                    node = node->right;
                }
                else{
                    node = node->left;
                }
            }
            
            return lastNodeWithName;
        }

        // prints Movie info from tree nodes
        void print(std::ostream& os) const 
        {
            printTree(os, root);
            printTreeDiffWay(os, root);
            printTreeDiffWayAgain(os, root);
        }

        //
        std::ostream& printTree(std::ostream& os, TreeNode* node) const
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

        std::ostream& printTreeDiffWay(std::ostream& os2, TreeNode* node) const
        {
            os2 << "\n";
            if (node == nullptr)
            {
                return os2;
            }

            
            printTree(os2, node->left);
            os2 << node->datum << std::endl;
            printTree(os2, node->right);
            return os2;
        }

        std::ostream& printTreeDiffWayAgain(std::ostream& os3, TreeNode* node) const
        {
            os3 << "\n";
            if (node == nullptr)
            {
                return os3;
            }

            
            printTree(os3, node->left);
            printTree(os3, node->right);
            os3 << node->datum << std::endl;
            return os3;
        }

        // returns the size of the binary search tree
        size_t size() const ;

};


int main()
{

    BinarySearchTree1 bst1;
    bst1.insert(5);
    bst1.insert(2);
    bst1.insert(6);
    bst1.insert(4);
    bst1.insert(3);
    bst1.insert(6);

    BinarySearchTree1 bst2(bst1);
    BinarySearchTree1 bst3;
    bst3 = bst1;

    bst1.print(std::cout);
    std::cout << std::endl << std::endl;
    bst2.print(std::cout);
    std::cout << std::endl << std::endl;
    bst3.print(std::cout);


}