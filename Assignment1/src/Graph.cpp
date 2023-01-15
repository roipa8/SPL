#include "../include/Graph.h"

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), statusList() { //Initializes all the healthy nodes
    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        statusList.push_back(Healthy);
    }
}


void Graph::infectNode(int nodeInd) { //Changes the status of a node to infected
    statusList[nodeInd] = Infected;

}

bool Graph::isInfected(int nodeInd) { //Returns if a node is infected
    return statusList[nodeInd] == Infected;
}

void Graph::setSick(int nodeInd) { //Returns if a node is sick
    statusList[nodeInd] = Sick;
}


bool Graph::isHealthy(int nodeInd) { //Returns if a node is healthy
    return statusList[nodeInd] == Healthy;
}


Tree *Graph::BFS(const Session &session, int nodeInd) { //Runs BFS algorithm
    Tree *root = Tree::createTree(session, nodeInd);
    std::vector<bool> isVisited;
    isVisited.reserve(edges.size());
    int size = edges.size();
    for (int i = 0; i < size; i++) {
        isVisited.push_back(false);
    }
    std::queue<Tree *> q;
    q.push(root);
    isVisited[nodeInd] = true;
    while (!q.empty()) {
        Tree *currTree = q.front();
        q.pop();
        for (int i = 0; i < size; i++) {
            if (!isVisited[i] && edges[i][currTree->getNode()] == 1) {
                isVisited[i] = true;
                Tree *nextTree = Tree::createTree(session, i);
                currTree->addChild(*nextTree);
                q.push(currTree->getNextTree());
                delete nextTree;
            }
        }
    }
    return root;
}


bool Graph::isFinish() { //the termination condition
    std::vector<bool> isVisited;
    int size = edges.size();
    isVisited.reserve(size);
    for (int i = 0; i < size; i++) {
        isVisited.push_back(false);
    }
    for (int i = 0; i < size; i++) {
        if ((statusList[i] == Infected) || (!isFinishAux(isVisited, i, statusList[i]))) {
            return false;
        }
    }
    return true;
}

bool Graph::isFinishAux(std::vector<bool> &isVisited, int row, Status status) {
    int size = edges.size();
    for (int i = 0; i < size; i++) {
        if (edges[row][i] == 1) {
            if (!isVisited[i]) {
                isVisited[i] = true;
                if (statusList[i] != status) {
                    return false;
                } else {
                    return isFinishAux(isVisited, i, statusList[i]);
                }
            }
        }
    }
    return true;

}

void Graph::removeEdges(int nIndex) { //Disconnect a node from his neighbours
    int size = edges.size();
    for (int i = 0; i < size; i++) {
        if (edges[nIndex][i] == 1) {
            edges[nIndex][i] = 0;
            edges[i][nIndex] = 0;
        }
    }
}


const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}




