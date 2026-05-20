#include <cstdio>
#include "Graph.h"

int main()
{
    int numberOfGraphs;
    scanf_s("%d", &numberOfGraphs);
    while (numberOfGraphs--) {
        int graphOrder;
        scanf_s("%d", &graphOrder);

        Graph graph(graphOrder);

        for (int i = 1; i <= graphOrder; ++i) {
            int numberOfNeighbors;
            scanf_s("%d", &numberOfNeighbors);

            for (int j = 0; j < numberOfNeighbors; ++j) {
                int neighbor;
                scanf_s("%d", &neighbor);
                graph.addEdge(i, neighbor);
            }
        }
        graph.printAnswer();

    }

    return 0;
}



