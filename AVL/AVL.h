//
// Created by Sig on 26-01-2022.
//

// #ifndef DATA_STRUCTURES_AVL_H
// #define DATA_STRUCTURES_AVL_H

#pragma once
#include "../BST/BST.h"

namespace DS {

    template<class T>
    struct AVL_Node : BST_Node<T> {
        int height;

        AVL_Node() = default;

        explicit AVL_Node(T data, bool isLeftChild = false, BST_Node <T> *par = nullptr) :
                BST_Node<T>(data, isLeftChild, par), height(0) {}

        AVL_Node<T> *right() {
            return (AVL_Node<T> *) (((BST_Node<T> *) this)->right);
        }

        AVL_Node<T> *left() {
            return (AVL_Node<T> *) (((BST_Node<T> *) this)->left);
        }

        AVL_Node<T> *parent() {
            return (AVL_Node<T> *) (((BST_Node<T> *) this)->parent);
        }

        void updateHeight() {
            int rightHeight, leftHeight;

            if (this->hasRight())
                rightHeight = right()->height;
            else
                rightHeight = 0;

            if (this->hasLeft())
                leftHeight = left()->height;
            else
                leftHeight = 0;

            this->height = std::max(leftHeight, rightHeight) + 1;
        }

        int getBalanceFactor() {
            int rightHeight, leftHeight;

            if (this->hasRight())
                rightHeight = right()->height;
            else
                rightHeight = 0;

            if (this->hasLeft())
                leftHeight = left()->height;
            else
                leftHeight = 0;

            return leftHeight - rightHeight;
        }
    };

    template<class T>
    class AVL_Tree : public BST<T> {

    private:

        virtual BST_Node <T> *makeNode(T data) {
            AVL_Node<T> *newNode = new AVL_Node<T>(data);
            return newNode;
        }

        // Updates the heights till it encounters the same height
        void updateHeights(BST_Node <T> *currNodeBST) {
            AVL_Node<T> *currNode = (AVL_Node<T> *) currNodeBST;
            while (currNode != nullptr) {
                int oldHeight = currNode->height;
                currNode->updateHeight();
                if (currNode->height == oldHeight)
                    return;
                currNode = currNode->parent();
            }
        }

        // Just a function to print the heights like data
        void privatePrintHeights(AVL_Node<T> *node, std::string pre = "") {
            std::cout << pre;

            if (node == nullptr) {
                std::cout << '-' << " ";
                return;
            }
            std::cout << node->height << "  ";

            if (node->hasLeft())
                std::cout << node->left()->height << " ";
            else
                std::cout << '-' << " ";

            if (node->hasRight())
                std::cout << node->right()->height << " ";
            else
                std::cout << '-' << " ";

            std::cout << "\n";

            if (node->left() != nullptr && !node->left()->isLeaf())
                privatePrintHeights(node->left(), pre + "    ");
            if (node->right() != nullptr && !node->right()->isLeaf())
                privatePrintHeights(node->right(), pre + "    ");
        }

        // Just to extend the update height
        virtual void makeRootNode(BST_Node <T> *newNode) {
            this->root = newNode;
            updateHeights(newNode);
        }

        // Rotations with the node a being the pivot

        void rotateClockwise(BST_Node <T> *a) {
            BST_Node<T> *b = a->left;
            if (b == nullptr)
                return;

            // Sorting things with the parent of a
            b->parent = a->parent;
            b->isLeftChild = a->isLeftChild;
            if (b->parent != nullptr) {
                if (b->isLeftChild)
                    b->parent->left = b;
                else
                    b->parent->right = b;
            } else
                this->root = b;

            // Dealing with the child moving
            a->left = b->right;
            if (a->left != nullptr) {
                a->left->parent = a;
                a->left->isLeftChild = true;
            }

            // Dealing with a and b
            b->right = a;
            a->parent = b;
            a->isLeftChild = false;

            // Updating the weights
            a->updateWeight();
            b->updateWeight();

            // Updating the heights
            updateHeights(a);
        }

        void rotateAntiClockwise(BST_Node <T> *a) {
            BST_Node<T> *b = a->right;
            if (b == nullptr)
                return;

            // Sorting things with the parent of a
            b->parent = a->parent;
            b->isLeftChild = a->isLeftChild;
            if (b->parent != nullptr) {
                if (b->isLeftChild)
                    b->parent->left = b;
                else
                    b->parent->right = b;
            } else
                this->root = b;

            // Dealing with the child moving
            a->right = b->left;
            if (a->right != nullptr) {
                a->right->parent = a;
                a->right->isLeftChild = false;
            }

            // Dealing with a and b
            b->left = a;
            a->parent = b;
            a->isLeftChild = true;

            // Updating the weights
            a->updateWeight();
            b->updateWeight();

            // Updating the heights
            updateHeights(a);
        }

        // Balancing Insertion
        void balanceInsertion(BST_Node <T> *currNode) {
            bool firstLeft;
            bool secondLeft;

            int balanceFactor;

            firstLeft = currNode->isLeftChild;
            currNode = currNode->parent;
            secondLeft = currNode->isLeftChild;
            currNode = currNode->parent;

            while (currNode != nullptr) {

                balanceFactor = ((AVL_Node<T> *) currNode)->getBalanceFactor();

                if (abs(balanceFactor) <= 1) {
                    secondLeft = firstLeft;
                    firstLeft = currNode->isLeftChild;
                    currNode = currNode->parent;
                    continue;
                }

                if (firstLeft && secondLeft) {
                    // LL
                    rotateClockwise(currNode);
                } else if (firstLeft) {
                    // LR
                    rotateAntiClockwise(currNode->left);
                    rotateClockwise(currNode);
                } else if (secondLeft) {
                    // RL
                    rotateClockwise(currNode->right);
                    rotateAntiClockwise(currNode);
                } else {
                    // RR
                    rotateAntiClockwise(currNode);
                }

                break;
            }
        }

        // Balancing Deletion
        void balanceDeletion(BST_Node <T> *currNode) {
            int balanceFactor;

            while (currNode != nullptr) {

                balanceFactor = ((AVL_Node<T> *) currNode)->getBalanceFactor();

                if (balanceFactor < -1) {
                    // This means the tree is concentrated towards the right
                    // Here, we do a anti-clockwise rotation with the current node as the pivot
                    rotateAntiClockwise(currNode);

                    // Current node will come below its right child and hence we go 2 steps up
                    currNode = currNode->parent->parent;

                    continue;
                }

                if (balanceFactor > 1) {
                    // This means the tree is concentrated towards the left
                    // Here, we do a clockwise rotation with the current node as the pivot
                    rotateClockwise(currNode);

                    // Current node will come below its left child and hence we go 2 steps up
                    currNode = currNode->parent->parent;

                    continue;
                }

                // If neither of the cases happen, we know that the current node is balanced and hence we go up
                currNode = currNode->parent;
            }
        }


    protected:

        // Extending the makeLeafNode from BST
        virtual void makeLeafNode(BST_Node <T> *parent, BST_Node <T> *newNode, int status) {
            BST<T>::makeLeafNode(parent, newNode, status);
            updateHeights(newNode);
            balanceInsertion(newNode);
        }

        // Extending the handleDeletionFrom from BST
        virtual void handleDeletionFrom(BST_Node <T> *currNodePtr) {
            BST<T>::handleDeletionFrom(currNodePtr);
            updateHeights(currNodePtr);
            balanceDeletion(currNodePtr);
        }

    public:

        AVL_Tree() = default;

        void printHeights() {
            privatePrintHeights((AVL_Node<T> *) this->root);
            std::cout << "\n";
        }

    };

}

// #endif  // DATA_STRUCTURES_AVL_H
