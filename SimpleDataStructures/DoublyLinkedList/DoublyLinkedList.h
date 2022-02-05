//#ifndef DATA_STRUCTURES_DOUBLY_LINKED_LIST_H
//#define DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

#pragma once

#include <iostream>

namespace DS {

    template<class T>
    struct DLL_Node {
        T data;
        DLL_Node<T> *next;
        DLL_Node<T> *prev;

        // Constructor

        explicit DLL_Node(T data) {
            this->data = data;
            next = nullptr;
            prev = nullptr;
        }

        // Destructor

        ~DLL_Node() = default;

        std::ostream &operator<<(std::ostream &outFunc) {
            outFunc << this->data;
            return outFunc;
        }
    };


    template<class T>
    struct DoublyLinkedList {
    protected:
        DLL_Node<T> *head;
        DLL_Node<T> *tail;
        int size;


    public:

        // Constructor and Destructor

        DoublyLinkedList() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        ~DoublyLinkedList() {
            auto curr = head;
            while (curr != nullptr) {
                auto temp = curr;
                curr = curr->next;
                delete temp;
            }
        }


        // Getters

        int getSize() {
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


        // Displays

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

        void displayListReverse() {
            if (tail == nullptr) {
                std::cout << "Empty!\n";
                return;
            }

            auto curr = tail;
            while (curr != nullptr) {
                std::cout << curr->data << " ";
                curr = curr->prev;
            }
            std::cout << "\n";
        }


        // Insertions

        void append(T data) {
            auto n = new DLL_Node<T>(data);
            if (head == nullptr) {
                head = n;
                tail = n;
            } else {
                tail->next = n;
                n->prev = tail;
                tail = n;
            }
            size++;
        }

        void prepend(T data) {
            auto n = new DLL_Node<T>(data);
            if (head == nullptr) {
                head = n;
                tail = n;
            } else {
                n->next = head;
                head->prev = n;
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

            auto n = new DLL_Node<T>(data);

            // Reach pos
            auto curr = head;
            for (int i = 1; i < pos - 1; i++)
                curr = curr->next;

            n->next = curr->next;
            curr->next->prev = n;

            curr->next = n;
            n->prev = curr;

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
            head->prev = nullptr;
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

            tail = tail->prev;
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

            auto curr = head;
            auto returnNode = head;

            if (pos <= size / 2) {
                curr = head;
                for (int i = 1; i <= pos - 1; i++)
                    curr = curr->next;

                returnNode = curr->next;
                curr->next = returnNode->next;
                returnNode->next->prev = curr;
            } else {
                curr = tail;
                for (int i = size; i >= pos + 1; i--)
                    curr = curr->prev;

                returnNode = curr->prev;
                curr->prev = returnNode->prev;
                returnNode->prev->next = curr;
            }
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

//#endif  // DATA_STRUCTURES_DOUBLY_LINKED_LIST_H

/*
 * SE: (Self Explanatory)
 *
 * T is any data type
 * DoublyLinkedList<T> (Example: DoublyLinkedList<int>)
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
