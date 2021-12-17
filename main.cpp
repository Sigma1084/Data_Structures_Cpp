#include <iostream>
#include "LinkedList/LinkedList.h"
#include "DoublyLinkedList/DoublyLinkedList.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
//#include "BST/BST.h"


using namespace std;

int main() {
    // DLL
//
//    DS::DoublyLinkedList<int> dll;
//    dll.append(5);
//    dll.append(10);
//
//    dll.prepend(6);
//
//    cout << dll.removeTail() << "\n";
//
//    dll.displayList();
//    dll.displayListReverse();

//    try {
//        cout << dll.removeAt(5) << " ";
//    } catch (invalid_argument) {
//        cout << "FF";
//    }

//    dll.insertAt(2, 7);
//    dll.displayList();
//
//    dll.insertAt(4, 8);
//    dll.displayList();

    DS::Stack<int> s;
    for (int i=1; i<=3; i++)
        s.push(i);
    s.display();
    cout << s.pop() << "\n";
    s.display();
    cout << s.peek() << "\n";

    return 0;
}
