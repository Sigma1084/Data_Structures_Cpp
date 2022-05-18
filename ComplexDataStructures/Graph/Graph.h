//
// Created by Sig on 05-02-2022.
//

//#ifndef DATA_STRUCTURES_GRAPH_H
//#define DATA_STRUCTURES_GRAPH_H

#pragma once

#include <vector>
using std::vector;
using std::pair;
#define vector<int> vi
#define pair<int, int> pii

#include <unordered_map>
using std::unordered_map;

#include <stdexcept>
using std::invalid_argument;


template <class T>
struct GraphNode {
    int index;
    T data;

    GraphNode() = default;

    GraphNode (int index, T data): index(index), data(data) {};

    ~GraphNode() = default;

    std::ostream &operator << (std::ostream &outFunc) {
        outFunc << this->data;
        return outFunc;
    }

    bool operator == (T checkData) {
        if (this->data == checkData)
            return true;
        return false;
    }
};


class Graph {
private:
    // Let's say n is the number vertices
    // Let's say m number of edges
    vi vertices;
    unordered_map<int, vi> edges;


    bool doesExist(index) {
        for (int vert: vertices) {
            if (vert == index)
                return true;
        }
        return false;
    }

    void insertPrivate(int index) {
        vertices.push_back(index);
    }

    void insertEdge(int vertex1, int vertex2) {
        pii p(vertex1, vertex2);

        edges.insert(p);
    }


public:
    void insertVertex (int index) {
        insertPrivate(index);
    }
};


//#endif  // DATA_STRUCTURES_GRAPH_H
