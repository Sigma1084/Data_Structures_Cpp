//#ifndef DATA_STRUCTURES_STACK_H
//#define DATA_STRUCTURES_STACK_H

#pragma once

#include "../DoublyLinkedList/DoublyLinkedList.h"

namespace DS {
    template<class T>
    struct Stack : private DoublyLinkedList<T> {

        Stack() = default;

        ~Stack() = default;

        void push(T data) {
            this->append(data);
        }

        T pop() {
            try {
                return this->removeTail();
            } catch (std::out_of_range) {
                throw std::out_of_range("Stack is Empty");
            }
        }

        T peek() {
            try {
                return this->getLast();
            } catch (std::out_of_range) {
                throw std::out_of_range("Stack is Empty");
            }
        }

        void display() {
            this->displayList();
        }
    };
}

//#endif  // DATA_STRUCTURES_STACK_H

/*
 * SE: (Self Explanatory)
 *
 * Stack<T>
 *
 * push(T data): (SE)
 * pop(): (SE)
 * peek(): (SE)
 *
 * display(): (SE)
 *
 */
