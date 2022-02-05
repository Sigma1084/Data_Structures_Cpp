//#ifndef DATA_STRUCTURES_QUEUE_H
//#define DATA_STRUCTURES_QUEUE_H

#pragma once

#include "../LinkedList/LinkedList.h"

namespace DS {

    template<class T>
    struct Queue : private LinkedList<T> {

        Queue() = default;

        ~Queue() = default;

        void enqueue(T data) {
            this->append(data);
        }

        T dequeue() {
            return this->removeHead();
        }

        T peek() {
            return this->getFirst();
        }

        void display() {
            this->displayList();
        }
    };
}

//#endif  // DATA_STRUCTURES_QUEUE_H

/*
 * SE: (Self Explanatory)
 *
 * Queue<T>
 *
 * enqueue(T data): (SE)
 * dequeue(): (SE)
 * peek(): (SE)
 *
 */
