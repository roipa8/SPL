#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/json.hpp"
#include "../include/Agent.h"

using json = nlohmann::json;

//Constructor Session
Session::Session(const std::string &path) : g({}), treeType(), agents(), Infected(), infectedFinal(), cycle(0) {
    std::ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    if (j["tree"] == "C") {
        treeType = Cycle;
    } else {
        if (j["tree"] == "M") {
            treeType = MaxRank;
        } else {
            treeType = Root;
        }
    }
    int size = j["agents"].size();
    for (int k = 0; k < size; k++) {
        if (j["agents"][k][0] == "C") {
            agents.push_back(new ContactTracer);
        } else {
            agents.push_back(new Virus(j["agents"][k][1]));
            g.infectNode(j["agents"][k][1]);
        }
    }
}

//Copy Constructor Session
Session::Session(const Session &other) : g(other.g), treeType(other.treeType), agents(other.agents),
                                         Infected(other.Infected), infectedFinal(other.infectedFinal),
                                         cycle(other.cycle) {
    int size = other.agents.size();
    for (int i = 0; i < size; i++) {
        agents.at(i) = other.agents.at(i)->clone();
    }
}


//Move Constructor Session
Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents),
                                    Infected(other.Infected), infectedFinal(other.infectedFinal), cycle(other.cycle) {
    int size = other.agents.size();
    for (int i = 0; i < size; i++) {
        agents.at(i) = other.agents.at(i)->clone();
        other.agents.at(i) = nullptr;
    }
    other.cycle = 0;
}

//Destructor Session
Session::~Session() {
    clear();
}

void Session::clear() { //Deletes all agents data
    if (!agents.empty()) {
        int size = agents.size();
        for (int i = 0; i < size; i++) {
            delete agents.at(i);
        }
    }
}

//Assignment Operator Session
Session &Session::operator=(const Session &other) {
    if (&other != this) {
        clear();
        g = other.getGraph();
        treeType = other.getTreeType();
        int size = other.agents.size();
        for (int i = 0; i < size; i++) {
            agents.at(i) = other.agents.at(i)->clone();
        }
        cycle = other.getCycle();
    }
    return *this;
}

//Move Assignment Operator Session
Session &Session::operator=(Session &&other) {
    if (&other != this) {
        clear();
        g = other.getGraph();
        treeType = other.getTreeType();
        int size = other.agents.size();
        for (int i = 0; i < size; i++) {
            agents.at(i) = other.agents.at(i)->clone();
            other.agents.at(i) = nullptr;
        }
        cycle = other.getCycle();
        other.cycle = 0;
    }
    return *this;
}

void Session::simulate() { //Simulates whole session
    while (!g.isFinish()) {
        int size = agents.size();
        for (int i = 0; i < size; i++) {
            agents.at(i)->act(*this);
        }
        cycle = cycle + 1;
    }
    createOutput();
}

void Session::addAgent(const Agent &agent) { //Clones an agent and adds it to the agents queue
    Agent *newAgent = agent.clone();
    agents.push_back(newAgent);
}

void Session::enqueueInfected(int newInf) { //Adds infected node to the infected queue
    Infected.push(newInf);
    infectedFinal.push_back(newInf);
}

int Session::dequeueInfected() { //Removes infected node from the infected queue
    int returnInf = Infected.front();
    Infected.pop();
    return returnInf;
}

TreeType Session::getTreeType() const { //Returns a type of a tree
    return treeType;
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

const Graph &Session::getGraph() const { //Returns the graph
    return g;
}

bool Session::isEmpty() { // Checks if "Infected" is empty
    return Infected.empty();
}

int Session::getCycle() const { // Returns what cycle we are in
    return cycle;
}

void Session::createOutput() { // Creates an output file
    std::ofstream i("output.json");
    json j;
    j["infected"] = infectedFinal;
    j["graph"] = g.getEdges();
    i << j;
}