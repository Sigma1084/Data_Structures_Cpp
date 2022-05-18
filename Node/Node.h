#pragma once

template <class T>
struct Node {
    T data;

    Node() = default;
    Node (T data): data(data) {};
    ~Node() = default;

    friend std::ostream &operator << (std::ostream &outFunc, const Node &n) {
        outFunc << n.data;
        return outFunc;
    }

    bool operator == (const T &checkData) {
        return this->data == checkData;
    }
};
