#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>
#include "Tree.h"
#include <queue>

enum Status {
    Sick,
    Healthy,
    Infected
};


class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    void setSick(int nodeInd);

    bool isHealthy(int nodeInd);

    Tree *BFS(const Session &session, int nodeInd);

    bool isFinish();

    bool isFinishAux(std::vector<bool> &isVisited, int row, Status status);

    void removeEdges(int nI);

//    const std::vector<int> &getNeighbours(int nodeInd) const;
    const std::vector<std::vector<int>> &getEdges() const;

private:
    std::vector<std::vector<int>> edges;
    std::vector<Status> statusList;
};

#endif