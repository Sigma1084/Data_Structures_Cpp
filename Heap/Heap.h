//
// Created by Sig on 05-02-2022.
//

//#ifndef DATA_STRUCTURES_HEAP_H
//#define DATA_STRUCTURES_HEAP_H

#pragma once

#include <vector>
using std::vector;

#include <stdexcept>
using std::invalid_argument;


namespace DS {

    template<class T>
    struct HeapNode {
        T data;

        HeapNode() = default;

        HeapNode(T data) : data(data) {};

        ~HeapNode() = default;

        std::ostream &operator<<(std::ostream &outFunc) {
            outFunc << this->data;
            return outFunc;
        }

        bool operator==(T checkData) {
            if (this->data == checkData)
                return true;
            return false;
        }
    };


    template<class T>
    class Heap {

    private:

        vector<HeapNode<T> *> nodeArr;

        void privatePrintHeap(int index, std::string pre = "") {
            std::cout << pre;

            if (nodeArr.size() == 0) {
                std::cout << '-' << " ";
                return;
            }
            std::cout << nodeArr[index]->data << "  ";

            if (hasLeft(index))
                std::cout << nodeArr[getLeft(index)]->data << " ";
            else
                std::cout << '-' << " ";

            if (hasRight(index))
                std::cout << nodeArr[getRight(index)]->data << " ";
            else
                std::cout << '-' << " ";

            std::cout << "\n";

            if (hasLeft(index) && hasLeft(getLeft(index)))
                privatePrintHeap(getLeft(index), pre + "    ");
            if (hasRight(index) && hasLeft(getLeft(index)))
                privatePrintHeap(getRight(index), pre + "    ");
        }

        int getLeft(int index) {
            return 2 * index + 1;
        }

        int getRight(int index) {
            return 2 * index + 2;
        }

        int getParent(int index) {
            return (index - 1) / 2;
        }

        bool hasLeft(int index) {
            return getLeft(index) < nodeArr.size();
        }

        bool hasRight(int index) {
            return getRight(index) < nodeArr.size();
        }

        void swap(int i, int j) {
            HeapNode<T> *temp = nodeArr[i];
            nodeArr[i] = nodeArr[j];
            nodeArr[j] = temp;
        }

        void heapifyUp(int index) {
            if (index == 0)
                return;
            int parent = getParent(index);
            while (index > 0 && mainChecker(index, parent)) {
                swap(index, parent);
                index = parent;
                parent = getParent(index);
            }
        }

        void heapifyDown(int index = 0) {
            if (index >= nodeArr.size())
                return;

            int left = getLeft(index);
            int right = getRight(index);
            int upper = index;

            if (hasLeft(index) && mainChecker(left, upper))
                upper = left;
            if (hasRight(index) && mainChecker(right, upper))
                upper = right;

            if (upper != index) {
                swap(index, upper);
                heapifyDown(upper);
            }
        }

        // Decides which index goes to the head
        bool mainChecker(int i, int j) {
            return upperFirst(nodeArr[i]->data, nodeArr[j]->data);
        }

        void insertPrivate(T data) {
            HeapNode<T> *n = new HeapNode<T>(data);
            nodeArr.push_back(n);
            heapifyUp(nodeArr.size() - 1);
        }

        // Assuming the Heap has at least 1 element
        T removePrivate(int index = 0) {
            HeapNode<T> *retValNode = nodeArr[index];
            nodeArr[index] = nodeArr[nodeArr.size() - 1];
            nodeArr.pop_back();
            heapifyDown(index);

            T retData = retValNode->data;
            delete retValNode;
            return retData;
        }


    protected:

        // Extend this function
        virtual bool upperFirst(T first, T second) {
            return first > second;
        }


    public:
        Heap() = default;

        T peek() {
            if (nodeArr.empty())
                throw std::invalid_argument("Heap is Empty");
            return nodeArr[0];
        }

        void push(T data) {
            insertPrivate(data);
        }

        T pop() {
            if (nodeArr.size() == 0)
                throw std::invalid_argument("Heap is Empty");
            return removePrivate();
        }

        void print() {
            privatePrintHeap(0);
            std::cout << "\n";
        }

        ~Heap() {
            for (int i = 0; i < nodeArr.size(); i++)
                delete nodeArr[i];
            nodeArr.clear();
        }
    };


    template<class T>
    class MaxHeap : public Heap<T> {
    protected:

        // Extending the function
        virtual bool upperFirst(T first, T second) {
            return first > second;
        }
    };


    template<class T>
    class MinHeap : public Heap<T> {
    protected:
        
        // Extending the function
        virtual bool upperFirst(T first, T second) {
            return first < second;
        }
    };
}


//#endif  // DATA_STRUCTURES_HEAP_H
