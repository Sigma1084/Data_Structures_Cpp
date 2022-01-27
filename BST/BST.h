//
// Created by Sig on 25-01-2022.
//

// #ifndef DATA_STRUCTURES_BST_H
// #define DATA_STRUCTURES_BST_H

#pragma once

namespace DS {

    template<class T>
    struct BST_Node {
        T data;
        int weight;  // The number of nodes under this including itself (Leaf Node: Weight = 1)
        bool isLeftChild;
        BST_Node<T> *left, *right, *parent;

        BST_Node() = default;

        BST_Node(T data, bool isLeftChild = false, BST_Node<T> *par = nullptr) :
                data(data), isLeftChild(isLeftChild), parent(par), weight(1), left(nullptr), right(nullptr) {}

        bool isLeaf() {
            return left == nullptr && right == nullptr;
        }

        bool hasRight() {
            return right != nullptr;
        }

        bool hasLeft() {
            return left != nullptr;
        }

        void updateWeight() {
            int leftWeight, rightWeight;

            if (left == nullptr)
                leftWeight = 0;
            else
                leftWeight = left->weight;

            if (right == nullptr)
                rightWeight = 0;
            else
                rightWeight = right->weight;

            this->weight = leftWeight + rightWeight + 1;
        }
    };

    template<class T>
    class BST {

    private:
        // Make new Node

        virtual BST_Node<T> *makeNode(T data) {
            BST_Node<T> *newNode = new BST_Node<T>(data);
            return newNode;
        }

        void updateWeights(BST_Node<T> *currNode, int val) {
            while (currNode != nullptr) {
                currNode->weight += val;
                currNode = currNode->parent;
            }
        }

        // Printing functions

        void privatePrintWeights(BST_Node<T> *node, std::string pre = "") {
            std::cout << pre;

            if (node == nullptr) {
                std::cout << '-' << " ";
                return;
            }
            std::cout << node->weight << "  ";

            if (node->hasLeft())
                std::cout << node->left->weight << " ";
            else
                std::cout << '-' << " ";

            if (node->hasRight())
                std::cout << node->right->weight << " ";
            else
                std::cout << '-' << " ";

            std::cout << "\n";

            if (node->left != nullptr && !node->left->isLeaf())
                privatePrintWeights(node->left, pre + "    ");
            if (node->right != nullptr && !node->right->isLeaf())
                privatePrintWeights(node->right, pre + "    ");
        }

        void privatePrintTree(BST_Node<T> *node, std::string pre = "") {
            std::cout << pre;

            if (node == nullptr) {
                std::cout << '-' << " ";
                return;
            }
            std::cout << node->data << "  ";

            if (node->hasLeft())
                std::cout << node->left->data << " ";
            else
                std::cout << '-' << " ";

            if (node->hasRight())
                std::cout << node->right->data << " ";
            else
                std::cout << '-' << " ";

            std::cout << "\n";

            if (node->left != nullptr && !node->left->isLeaf())
                privatePrintTree(node->left, pre + "    ");
            if (node->right != nullptr && !node->right->isLeaf())
                privatePrintTree(node->right, pre + "    ");
        }

        void privatePrintIsLefts(BST_Node<T> *node, std::string pre = "") {
            std::cout << pre;

            if (node == nullptr) {
                std::cout << '-' << " ";
                return;
            }
            std::cout << node->isLeftChild << "  ";

            if (node->hasLeft())
                std::cout << node->left->isLeftChild << " ";
            else
                std::cout << '-' << " ";

            if (node->hasRight())
                std::cout << node->right->isLeftChild << " ";
            else
                std::cout << '-' << " ";

            std::cout << "\n";

            if (node->left != nullptr && !node->left->isLeaf())
                privatePrintIsLefts(node->left, pre + "    ");
            if (node->right != nullptr && !node->right->isLeaf())
                privatePrintIsLefts(node->right, pre + "    ");
        }

        // Traversal functions

        static void goToMin(BST_Node<T> *&currNodePtr) {
            while (currNodePtr->hasLeft())
                currNodePtr = currNodePtr->left;
        }

        static void goToMax(BST_Node<T> *&currNodePtr) {
            while (currNodePtr->hasRight())
                currNodePtr = currNodePtr->right;
        }

        // Insertions

        virtual void makeRootNode(BST_Node<T> *newNode) {
            root = newNode;
        }

        void insertEqual(BST_Node<T> *currNodePtr, BST_Node<T> *newNode) {

            // If right is empty, just insert
            if (!currNodePtr->hasRight()) {
                makeLeafNode(currNodePtr, newNode, 1);
                return;
            }

            // If left is empty, just insert
            if (!currNodePtr->hasLeft()) {
                makeLeafNode(currNodePtr, newNode, -1);
                return;
            }

            // Now, we know that the current Node has both right and left elements

            // When right side is heavier, go to left and insert at the max position
            if (currNodePtr->right->weight > currNodePtr->left->weight) {
                currNodePtr = currNodePtr->left;
                goToMax(currNodePtr);
                makeLeafNode(currNodePtr, newNode, 1);
            }

                // Now, we know left side is heavier or at the same weight as the right side
                // Therefore, go to right and insert at the min position
            else {
                currNodePtr = currNodePtr->right;
                goToMin(currNodePtr);
                makeLeafNode(currNodePtr, newNode, -1);
            }
        }

        void insertPrivate(BST_Node<T> *newNode) {

            // When the root is empty
            if (root == nullptr) {
                makeRootNode(newNode);
                return;
            }

            int status;
            BST_Node<T> *nearestNodePtr = getNearestNodePtr(newNode->data, status);


            // When the data is already present
            // Decide what to do when the data is already present
            if (status == 0) {
                insertEqual(nearestNodePtr, newNode);
                return;
            }

            // Here, insert into the tree directly
            makeLeafNode(nearestNodePtr, newNode, status);
        }

        // Deletions

        void removeSingleRootNode() {
            delete root;
            root = nullptr;
        }

        // Handle the removal and have the currNodePtr to the node that is being removed
        void handleRemoveInternalNode(BST_Node<T> *&currNodePtr) {

            BST_Node<T> *temp = currNodePtr;

            // Left side is heavier
            // Here, we remove one node from left and replace it with the currNode
            if (currNodePtr->left->weight > currNodePtr->right->weight) {
                currNodePtr = currNodePtr->left;
                goToMax(currNodePtr);
            }

                // Right side is heavier or they have equal weight
                // Here, we remove one node from right and replace it with the currNode
            else {
                currNodePtr = currNodePtr->right;
                goToMin(currNodePtr);
            }

            // currNodePtr is the one pointing to the one to be replaced
            // temp is the one pointing to the one to be removed

            temp->data = currNodePtr->data;
        }

        // Here, we assume the Node is present and weight > 0
        void removePrivate(BST_Node<T> *currNodePtr) {

            // The case where we remove the root node and it is the only node
            if (getWeight() == 1) {
                removeSingleRootNode();
                return;
            }

            // Handling internal Node first
            // We call a handleRemoveInternalNode method
            // We copy the data into the current Node and move to the required node here
            if (currNodePtr->hasLeft() && currNodePtr->hasRight())
                handleRemoveInternalNode(currNodePtr);

            // After handleRemoveInternalNode, currNodePtr is pointing to the node that will be removed

            // This is just the reference of the current node and is the node that is removed
            BST_Node<T> *nodeToBeDeleted = currNodePtr;


            // After handling the internalNode
            // Here, we are left with either a leaf node or a half filled tree

            // The case when the node to be removed has an empty left subtree
            if (currNodePtr->hasRight()) {
                if (currNodePtr == root) {
                    currNodePtr->right->parent = nullptr;
                    root = currNodePtr->right;
                } else
                    connect(currNodePtr->parent, currNodePtr->right, currNodePtr->isLeftChild);
                currNodePtr = currNodePtr->right;
            }

                // The case when the node to be removed has an empty right subtree
            else if (currNodePtr->hasLeft()) {
                if (currNodePtr == root) {
                    currNodePtr->left->parent = nullptr;
                    root = currNodePtr->left;
                } else
                    connect(currNodePtr->parent, currNodePtr->left, currNodePtr->isLeftChild);
                currNodePtr = currNodePtr->left;
            }

                // The case when the node to be removed is a leaf
            else {
                if (currNodePtr->isLeftChild)
                    currNodePtr->parent->left = nullptr;
                else
                    currNodePtr->parent->right = nullptr;
            }

            currNodePtr = currNodePtr->parent;

            delete nodeToBeDeleted;

            // We are currently at the parent who's child Node was deleted or replaced

            handleDeletionFrom(currNodePtr);
        }

    protected:
        BST_Node<T> *root;

        // Function to connect 2 non empty nodes
        void connect(BST_Node<T> *parent, BST_Node<T> *child, bool isLeft) {
            if (parent == nullptr || child == nullptr)
                return;

            child->isLeftChild = isLeft;
            child->parent = parent;

            if (isLeft)
                parent->left = child;
            else
                parent->right = child;
        }

        // Some traversal functions

        static void goUp(BST_Node<T> **&currNodePtr) {
            currNodePtr = &((*currNodePtr)->parent);
        }

        static void goRight(BST_Node<T> **&currNodePtr) {
            currNodePtr = &((*currNodePtr)->right);
        }

        static void goLeft(BST_Node<T> **&currNodePtr) {
            currNodePtr = &((*currNodePtr)->left);
        }


        // Function related to insertions and is extended
        virtual void makeLeafNode(BST_Node<T> *parent, BST_Node<T> *newNode, int status) {
            connect(parent, newNode, status == -1);
            updateWeights(parent, 1);
        }

        // Function related to deletions and is extended
        virtual void handleDeletionFrom(BST_Node<T> *currNodePtr) {
            updateWeights(currNodePtr, -1);
        }


        // The main traversal function

        // It is assumed that the tree is not empty
        BST_Node<T> *getNearestNodePtr(T data, int &status) {
            // Status 0 if we find data in some node
            // Status -1 if we find a node and the data is supposed to be left of that node
            // Status 1 if we find a node and the data is supposed to be right of that node

            BST_Node<T> *currNodePtr = root;  // Start iterating from root (not empty)

            // Traverse the tree till we encounter a Leaf Node
            while (true) {

                // When the data is found in some node, we return the pointer to that node
                if (currNodePtr->data == data) {
                    status = 0;  // Indicating we the data is present in the current node
                    return currNodePtr;
                }

                // The data lies to the left of the current subtree
                if (data < currNodePtr->data) {

                    // The left subtree is empty
                    if (!currNodePtr->hasLeft()) {
                        status = -1;
                        return currNodePtr;
                    }

                    // The left subtree is not empty
                    currNodePtr = currNodePtr->left;
                }

                    // The data lies to the right of the current subtree
                else {

                    // The right subtree is empty
                    if (!currNodePtr->hasRight()) {
                        status = 1;
                        return currNodePtr;
                    }

                    // The right subtree is not empty
                    currNodePtr = currNodePtr->right;
                }
            }
        }


    public:
        BST() {
            root = nullptr;
        }

        void insert(T data) {
            BST_Node<T> *newNode = makeNode(data);
            insertPrivate(newNode);
        }

        void removeIfExists(T data) {
            if (root == nullptr)
                return;

            int status;
            BST_Node<T> *nearestNodePtr = getNearestNodePtr(data, status);

            if (status != 0)
                return;

            removePrivate(nearestNodePtr);
        }

        void remove(T data) {
            if (root == nullptr)
                throw std::invalid_argument("Data Not present");

            int status;
            BST_Node<T> *nearestNodePtr = getNearestNodePtr(data, status);

            if (status != 0)
                throw std::invalid_argument("Data Not present");

            removePrivate(nearestNodePtr);
        }

        int getWeight() {
            if (root == nullptr)
                return 0;
            return root->weight;
        }

        void printWeights() {
            privatePrintWeights(root);
            std::cout << "\n";
        }

        void printIsLefts() {
            privatePrintIsLefts(root);
            std::cout << "\n";
        }

        void printTree() {
            privatePrintTree(root);
            std::cout << "\n";
        }
    };
}

// #endif  // DATA_STRUCTURES_BST_H
