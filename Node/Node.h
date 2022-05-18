#pragma once

template <class T>
struct Node {
    T data;

    Node() = default;
    Node (T data): data(data) {};
    ~Node() = default;

    std::ostream &operator << (std::ostream &outFunc) {
        outFunc << this->data;
        return outFunc;
    }

    bool operator == (const T &checkData) {
        return this->data == checkData;
    }
};
