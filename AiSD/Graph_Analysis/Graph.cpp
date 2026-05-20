#include "Graph.h"

Graph::Graph(int n) : n(n), doubledNumberOfEdges(0) {
    adjacencyList = new Vector<int>[n + 1];
}

Graph::Graph(const Graph& other) : n(other.n), doubledNumberOfEdges(other.doubledNumberOfEdges) {
    adjacencyList = new Vector<int>[n + 1];
    for (int i = 0; i <= n; i++) {
        adjacencyList[i] = other.adjacencyList[i];
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this == &other) return *this;

    delete[] adjacencyList;

    n = other.n;
    doubledNumberOfEdges = other.doubledNumberOfEdges;
    adjacencyList = new Vector<int>[n + 1];
    for (int i = 0; i <= n; i++) {
        adjacencyList[i] = other.adjacencyList[i];
    }

    return *this;
}

void Graph::addEdge(int u, int v) {
    adjacencyList[u].push_back(v);
    doubledNumberOfEdges++;
}

void Graph::mergeSort(Vector<int>& array) {
    int length = array.getSize();
    if (length < 2) return;
    int middle = length / 2;

    Vector<int> leftArray(middle), rightArray(length - middle);
    int i = 0;
    int j = 0;
    for (; i < length; i++) {
        if (i < middle) {
            leftArray[i] = array[i];
        }
        else {
            rightArray[j] = array[i];
            j++;
        }
    }
    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(leftArray, rightArray, array);
}

void Graph::merge(const Vector<int>& leftArray, const Vector<int>& rightArray, Vector<int>& array) {
    int leftSize = leftArray.getSize();
    int rightSize = rightArray.getSize();
    int i = 0, l = 0, r = 0;
    while (l < leftSize && r < rightSize) {
        if (leftArray[l] <= rightArray[r]) {
            array[i++] = leftArray[l++];
        }
        else {
            array[i++] = rightArray[r++];
        }
    }
    while (l < leftSize) {
        array[i++] = leftArray[l++];
    }
    while (r < rightSize) {
        array[i++] = rightArray[r++];
    }
}

void Graph::mergeSort(Vector<Vertex>& array) {
    int length = array.getSize();
    if (length < 2) return;
    int middle = length / 2;

    Vector<Vertex> leftArray(middle), rightArray(length - middle);
    int i = 0;
    int j = 0;
    for (; i < length; i++) {
        if (i < middle) {
            leftArray[i] = array[i];
        }
        else {
            rightArray[j] = array[i];
            j++;
        }
    }
    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(leftArray, rightArray, array);
}

void Graph::merge(const Vector<Vertex>& leftArray, const Vector<Vertex>& rightArray, Vector<Vertex>& array) {
    int leftSize = leftArray.getSize();
    int rightSize = rightArray.getSize();
    int i = 0, l = 0, r = 0;
    while (l < leftSize && r < rightSize) {
        if (leftArray[l].degree > rightArray[r].degree ||
            (leftArray[l].degree == rightArray[r].degree && leftArray[l].id < rightArray[r].id)) {
            array[i++] = leftArray[l++];
        }
        else {
            array[i++] = rightArray[r++];
        }
    }
    while (l < leftSize) {
        array[i++] = leftArray[l++];
    }
    while (r < rightSize) {
        array[i++] = rightArray[r++];
    }
}

void Graph::BFS(Vector<bool>& visited, int start) {
    Queue<int> q;
    q.push(start);

    visited[start] = true;

    while (!q.empty()) {
        int v = q.getFront();
        q.pop();

        for (size_t i = 0; i < adjacencyList[v].getSize(); i++) {
            int neighbor = adjacencyList[v][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void Graph::degreeSequence() {
    Vector<int> degreesArray(n, 0);
    for (int i = 1; i <= n; i++) {
        degreesArray[i - 1] = adjacencyList[i].getSize();
    }
    mergeSort(degreesArray);

    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", degreesArray[i]);
    }
    printf("\n");
}

int Graph::numberOfComponents() {
    Vector<bool> visited(n + 1, false);
    int components = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            BFS(visited, i);
            components++;
        }
    }
    return components;
}

void Graph::numberOfComplementsEdges() const {
    long long result = (long long)n * (long long)(n - 1) / 2 - (long long)doubledNumberOfEdges / 2;
    printf("%lld\n", result);
}

// -1 - nieoznaczony, 0 jedna strona, 1 druga strona
bool Graph::bipartiness() {
    Vector<int> side(n + 1, -1); 
    for (int i = 1; i <= n; i++) {
        if (side[i] == -1) {
            Queue<int> q;
            q.push(i);
            side[i] = 0;
            while (!q.empty()) {
                int v = q.getFront();
                q.pop();
                for (size_t j = 0; j < adjacencyList[v].getSize(); j++) {
                    int neighbor = adjacencyList[v][j];
                    if (side[neighbor] == -1) {
                        side[neighbor] = 1 - side[v];
                        q.push(neighbor);
                    }
                    else if (side[neighbor] == side[v]) {
                        return false;//jeœli s¹siaduj¹cy wierzcho³ek jest po tej samej stronie, graf nie jest dwudzielny
                    }
                }
            }
        }
    }
    return true;
}

void Graph::greedy() {
    Vector<int> colors(n + 1, 0); // Vector do przechowywania kolorów wierzcho³ków
    Vector<bool> usedColors(n + 1, false); //Vector do œledzenia u¿ytych kolorów
    Vector<int> usedColorIndices; //Vector do przechowywania indeksów u¿ytych kolorów (przyspiesza zerowanie Vectora usedColors)

    for (int i = 1; i <= n; i++) {
        for (size_t j = 0; j < usedColorIndices.getSize(); j++) {
            int colorIndex = usedColorIndices[j];
            usedColors[colorIndex] = false;
        }
        usedColorIndices.clear();

        for (size_t j = 0; j < adjacencyList[i].getSize(); j++) {
            int neighbor = adjacencyList[i][j];
            if (colors[neighbor] != 0) {
                usedColors[colors[neighbor]] = true;
                usedColorIndices.push_back(colors[neighbor]);
            }
        }

        for (int j = 1; j <= n; j++) {
            if (!usedColors[j]) {
                colors[i] = j;
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", colors[i]);
    }
    printf("\n");
}

void Graph::LFMethod() {
    Vector<int> colors(n + 1, 0); // Vector do przechowywania kolorów wierzcho³ków
    Vector<Vertex> vertexOrder(n); //Vector do przechowywania wierzcho³ków posortowanych wzglêdem stopnia
    Vector<bool> usedColors(n + 1, false); //Vector do œledzenia u¿ytych kolorów
    Vector<int> usedColorIndices; //Vector do przechowywania indeksów u¿ytych kolorów (przyspiesza zerowanie Vectora usedColors)

    for (int i = 1; i <= n; i++) {
        vertexOrder[i - 1] = { i, (int)adjacencyList[i].getSize() };
    }
    
    mergeSort(vertexOrder);

    for (size_t k = 0; k < vertexOrder.getSize(); k++) {
        int i = vertexOrder[k].id;
        for (size_t j = 0; j < usedColorIndices.getSize(); j++) {
            int colorIndex = usedColorIndices[j];
            usedColors[colorIndex] = false;
        }
        usedColorIndices.clear();

        for (size_t j = 0; j < adjacencyList[i].getSize(); j++) {
            int neighbor = adjacencyList[i][j];
            if (colors[neighbor] != 0) {
                usedColors[colors[neighbor]] = true;
                usedColorIndices.push_back(colors[neighbor]);
            }
        }

        for (int j = 1; j <= n; j++) {
            if (!usedColors[j]) {
                colors[i] = j;
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", colors[i]);
    }
    printf("\n");
}

int Graph::BFSforComponentSize(Vector<int>& component, int start, int componentIndex) {
    Queue<int> q;
    q.push(start);
    component[start] = componentIndex;
    int componentSize = 0;

    while (!q.empty()) {
        int v = q.getFront();
        q.pop();
        componentSize++;

        for (int i = 0; i < adjacencyList[v].getSize(); ++i) {
            int neighbor = adjacencyList[v][i];
            if (component[neighbor] == -1) {
                component[neighbor] = componentIndex;
                q.push(neighbor);
            }
        }
    }

    return componentSize;
}

int Graph::BFSforEcc(Vector<int>& component, int start, int componentIndex, int componentSize) {
    Queue<int> q;
    q.push(start);
    q.push(-1);
    component[start] = componentIndex;
    int distance = 0;
    int vcounter = 1;

    while (!q.empty() && vcounter < componentSize) {
        int v = q.getFront();
        q.pop();

        if (v == -1) {
            distance++;
            if (!q.empty()) {
                q.push(-1);
            }
        }
        else {
            for (int i = 0; i < adjacencyList[v].getSize(); ++i) {
                int neighbor = adjacencyList[v][i];
                if (component[neighbor] != componentIndex) {
                    component[neighbor] = componentIndex;
                    q.push(neighbor);
                    vcounter++;
                }
            }
        }
    }

    if (componentSize > 1) {
        distance++;
    }

    return distance;
}

void Graph::eccencrity() {
    Vector<int> nonIsolatedNodes;
    Vector<bool> isolatedNodes(n + 1, false);

    // Pierwszy krok: znajdowanie izolowanych wierzcho³ków
    for (int i = 1; i <= n; ++i) {
        if (adjacencyList[i].getSize() == 1 && adjacencyList[i][0] == 0) {
            isolatedNodes[i] = true;
        }
        else {
            nonIsolatedNodes.push_back(i);
        }
    }

    int nonIsolatedCount = nonIsolatedNodes.getSize();
    Vector<int> component(n + 1, -1);
    Vector<int> componentSizes(n + 1, 0);

    int componentIndex = 0;

    // Podzia³ na sk³adowe spójnoœci dla nieizolowanych wierzcho³ków
    for (int i = 0; i < nonIsolatedCount; ++i) {
        int node = nonIsolatedNodes[i];
        if (component[node] == -1) {
            int componentSize = BFSforComponentSize(component, node, componentIndex);
            for (int j = 0; j < nonIsolatedCount; ++j) {
                int compNode = nonIsolatedNodes[j];
                if (component[compNode] == componentIndex) {
                    componentSizes[compNode] = componentSize;
                }
            }
            componentIndex++;
        }
    }

    // Obliczanie ekscentrycznoœci
    int bfsIndex = componentIndex + 1;
    for (int i = 1; i <= n; ++i) {
        if (isolatedNodes[i]) {
            printf("0 ");
        }
        else if (componentSizes[i] == 2) {
            printf("1 ");
        }
        else {
            int eccencrity = BFSforEcc(component, i, bfsIndex, componentSizes[i]);
            bfsIndex++;
            printf("%d ", eccencrity);
        }
    }
    printf("\n");
}

void Graph::printAnswer() {
    degreeSequence();
    printf("%d\n", numberOfComponents());
    printf("%s\n", bipartiness() ? "T" : "F");
    eccencrity();
    for (int i = 0; i < 1; i++) {
        printf("?\n");
    }
    greedy();
    LFMethod();
    for (int i = 0; i < 2; i++) {
        printf("?\n");
    }
    numberOfComplementsEdges();
}

Graph::~Graph() {
    delete[] adjacencyList;
}
