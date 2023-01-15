#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <queue>

class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    Session(const std::string &path);

    Session(const Session &other);

    Session(Session &&other);

    Session &operator=(const Session &other);

    Session &operator=(Session &&other);

    virtual ~Session();

    void clear();

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    const Graph &getGraph() const;

    void enqueueInfected(int);

    int dequeueInfected();

    TreeType getTreeType() const;

    bool isEmpty();

    int getCycle() const;

    void createOutput();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    std::queue<int> Infected;
    std::vector<int> infectedFinal;
    int cycle;
};

#endif