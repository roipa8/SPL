#include "../include/Agent.h"

//Constructor Agent
Agent::Agent() {};

//Destructor Agent
Agent::~Agent() = default;

//Constructor Contact Tracer
ContactTracer::ContactTracer() {};


void ContactTracer::act(Session &session) { //depends on the tree that is given, disconnect a node from his neighbours
    if (!session.isEmpty()) {
        int rNode = session.dequeueInfected();
        Graph g1 = session.getGraph();
        Tree *treeToCut = g1.BFS(session, rNode);
        int nodeToCut = treeToCut->traceTree();
        g1.removeEdges(nodeToCut);
        session.setGraph(g1);
        delete treeToCut;
    }
}

Agent *ContactTracer::clone() const { return new ContactTracer(*this); } //Makes a clone of a contact tracer

//Constructor Virus
Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

Agent *Virus::clone() const { return new Virus(*this); } //Creates a clone of a virus

void Virus::act(Session &session) { //Gets himself sick and spread the virus to the next neighbour node
    Graph g1 = session.getGraph();
    if (g1.isInfected(nodeInd)) {
        g1.setSick(nodeInd);
        session.enqueueInfected(nodeInd);
        session.setGraph(g1);
    }
    bool isFound = false;
    int size = g1.getEdges().size();
    for (int i = 0; i < size && !isFound; i++) {
        if (g1.isHealthy(i) && g1.getEdges()[nodeInd][i] == 1) {
            g1.infectNode(i);
            session.addAgent(Virus(i));
            isFound = true;
            session.setGraph(g1);
        }
    }
}