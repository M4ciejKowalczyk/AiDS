#pragma once

#include <cstdio>
#include "Vector.h"
#include "Queue.h"

struct Vertex {
    int id;
    int degree;
};

class Graph
{
private:
    int n;
    int doubledNumberOfEdges;
    Vector<int>* adjacencyList;
    //sortowanie dla ci¹gu stopniowego
    void mergeSort(Vector<int>& array);
    static void merge(const Vector<int>& leftArray, const Vector<int>& rightArray, Vector<int>& array);
    //sortowanie wierzcho³ków do kolorowania
    void mergeSort(Vector<Vertex>& array);
    static void merge(const Vector<Vertex>& leftArray, const Vector<Vertex>& rightArray, Vector<Vertex>& array);
    void BFS(Vector<bool>& visited, int start);

public:
    explicit Graph(int n);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    void addEdge(int u, int v);
    void degreeSequence();
    int numberOfComponents();
    void numberOfComplementsEdges() const;
    bool bipartiness();
    void greedy();
    void LFMethod();
    void eccencrity();
    int BFSforComponentSize(Vector<int>& component, int start, int componentIndex);
    int BFSforEcc(Vector<int>& component, int start, int componentIndex, int componentSize);
    void printAnswer();
    ~Graph();
};