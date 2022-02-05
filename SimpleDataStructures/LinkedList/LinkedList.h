//#ifndef DATA_STRUCTURES_LINKED_LIST_H
//#define DATA_STRUCTURES_LINKED_LIST_H

#pragma once

#include <iostream>

namespace DS {

    template<class T>
    struct LL_Node {
        T data;
        LL_Node<T> *next;

        // Constructor

        explicit LL_Node(T data) {
            this->data = data;
            next = nullptr;
        }

        // Destructor

        ~LL_Node() = default;

        std::ostream &operator << (std::ostream &outFunc) {
            outFunc << this->data;
            return outFunc;
        }
    };


    template<class T>
    struct LinkedList {
    protected:
        LL_Node<T> *head;
        LL_Node<T> *tail;
        int size;


    public:

        // Constructor and Destructor

        LinkedList() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        ~LinkedList() {
            auto curr = head;
            while (curr != nullptr) {
                auto temp = curr;
                curr = curr->next;
                delete temp;
            }
        }


        // Getters

        int getSize() const {
            return size;
        }

        T getFirst() {
            if (size == 0)
                throw std::out_of_range("Linked List Out of Range");
            return head->data;
        }

        T getLast() {
            if (size == 0)
                throw std::out_of_range("Linked List Out of Range");
            return tail->data;
        }


        // Display

        void displayList() {
            if (head == nullptr) {
                std::cout << "Empty!\n";
                return;
            }

            auto curr = head;
            while (curr != nullptr) {
                std::cout << curr->data << " ";
                curr = curr->next;
            }
            std::cout << "\n";
        }


        // Insertions

        void append(T data) {
            auto n = new LL_Node<T>(data);
            if (head == nullptr) {
                head = n;
                tail = n;
            } else {
                tail->next = n;
                tail = n;
            }
            size++;
        }

        void prepend(T data) {
            auto n = new LL_Node<T>(data);
            if (head == nullptr) {
                head = n;
                tail = n;
            } else {
                n->next = head;
                head = n;
            }
            size++;
        }

        void insertAt(int pos, T data) {
            if (pos > size + 1 || pos < 1)
                throw std::invalid_argument("Received Invalid Position");
            if (pos == 1)
                return prepend(data);
            if (pos == size + 1)
                return append(data);

            auto n = new LL_Node<T>(data);

            // Reach pos
            auto curr = head;
            for (int i = 1; i < pos - 1; i++)
                curr = curr->next;

            n->next = curr->next;
            curr->next = n;
            size++;
        }


        // Deletions

        T removeHead() {
            if (head == nullptr)
                throw std::invalid_argument("Empty, nothing to remove");

            if (size == 1)
                return removeLastNode();

            auto returnNode = head;
            head = head->next;
            size--;

            T returnData = returnNode->data;
            delete returnNode;
            return returnData;
        }

        T removeTail() {
            if (head == nullptr)
                throw std::invalid_argument("Empty, nothing to remove");

            if (size == 1)
                return removeLastNode();

            auto returnNode = tail;
            auto prev = head;

            while (prev->next != tail)
                prev = prev->next;

            tail = prev;
            tail->next = nullptr;
            size--;

            T returnData = returnNode->data;
            delete returnNode;
            return returnData;
        }

        T removeAt(int pos) {
            if (head == nullptr)
                throw std::invalid_argument("Empty, nothing to remove");
            if (pos > size || pos < 1)
                throw std::invalid_argument("Received Invalid Position");
            if (pos == 1)
                return removeHead();
            if (pos == size)
                return removeTail();

            // Reach the pos - 1
            auto cur = head;
            for (int i = 1; i <= pos - 1; i++)
                cur = cur->next;

            auto returnNode = cur->next;
            cur->next = cur->next->next;
            size--;

            auto returnData = returnNode->data;
            delete returnNode;
            return returnData;
        }


        // Private Methods
    private:

        T removeLastNode() {
            T returnData = head->data;
            delete head;

            head = nullptr;
            tail = nullptr;
            size = 0;

            return returnData;
        }
    };
}

//#endif  // DATA_STRUCTURES_LINKED_LIST_H

/*
 * SE: (Self Explanatory)
 *
 * T is any data type
 * LinkedList<T> (Example: LinkedList<int>)
 * Indices from 1 to n
 *
 * getSize(): (SE) returns n
 * getFirst(): (SE) returns the data in head
 * getLast(): (SE) returns the data in tail
 *
 * append(T data): (SE)
 * prepend(T data): (SE)
 * insertAt(int pos, T data): (SE) inserts at position pos
 *                            pushes the next elements one step to the right
 *                            throws an error if the position is not accessible
 *
 * removeHead(): (SE) returns the data at head
 * removeTail(): (SE) returns the data at tail
 * removeAt(int pos): (SE) returns the data in the position otherwise throws an error
 *
 */
