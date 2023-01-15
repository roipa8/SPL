#include "../include/Tree.h"
#include "../include/Session.h"

using namespace std;

//Constructor Tree
Tree::Tree(int rootLabel) : node(rootLabel), children(), depth(0) {
}

//Copy Constructor Tree
Tree::Tree(const Tree &other) : node(other.node), children(), depth(other.depth) {
    int size = other.children.size();
    for (int i = 0; i < size; i++) {
        children.push_back(other.children.at(i)->clone());
    }
}

//Move Constructor Tree
Tree::Tree(Tree &&other) : node(other.node), children(), depth(other.depth) {
    int size = other.children.size();
    for (int i = 0; i < size; i++) {
        children.push_back(other.children.at(i)->clone());
        other.children.at(i) = nullptr;
    }
    other.depth = 0;

}

void Tree::clear() { //deletes a tree's data
    if (!children.empty()) {
        int size = children.size();
        for (int i = 0; i < size; i++) {
            delete children.at(i);
        }
    }
}

//Destructor Tree
Tree::~Tree() {
    clear();
}


Tree *Tree::createTree(const Session &session, int rootLabel) { //Creates a tree depends on the kind that is given
    Tree *currTree;
    if (session.getTreeType() == Cycle) {
        currTree = new CycleTree(rootLabel, session.getCycle());
    } else {
        if (session.getTreeType() == MaxRank) {
            currTree = new MaxRankTree(rootLabel);
        } else {
            currTree = new RootTree(rootLabel);
        }
    }
    return currTree;
}


void Tree::addChild(const Tree &child) { //Adds a child to the tree
    Tree *newChild = child.clone();
    newChild->depth = depth + 1;
    children.push_back(newChild);
}


//Assignment Operator Tree
Tree &Tree::operator=(const Tree &other) {
    if (&other != this) {
        clear();
        node = other.node;
        int otherSize = other.children.size();
        for (int i = 0; i < otherSize; i++) {
            children.push_back(other.children.at(i)->clone());
        }
        depth = other.depth;
    }
    return *this;
}

//Move Assignment Operator Tree
Tree &Tree::operator=(Tree &&other) {
    if (&other != this) {
        clear();
        node = other.node;
        int otherSize = other.children.size();
        for (int i = 0; i < otherSize; i++) {
            children.push_back(other.children.at(i)->clone());
            other.children.at(i) = nullptr;
        }
        depth = other.depth;
        other.depth = 0;
    }
    return *this;
}

int Tree::getNode() const {
    return node;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

//Copy Constructor CycleTree
CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.currCycle) {}

//Assignment Operator CycleTree
CycleTree &CycleTree::operator=(const CycleTree &other) {
    if (&other != this) {
        Tree::operator=(other);
        currCycle = other.currCycle;
    }
    return *this;
}

Tree *CycleTree::clone() const { //Creates a clone of a CycleTree
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    CycleTree *currTree = this;
    int currNode = node;
    for (int i = 0; i < currCycle; i++) {
        if (currTree->children.empty()) {
            return currNode;
        }
        currTree = (CycleTree *) currTree->children.at(0);
        currNode = currTree->node;
    }
    return currNode;
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

//Copy Constructor MaxRankTree
MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {}

//Assignment Operator MaxRankTree
MaxRankTree &MaxRankTree::operator=(const MaxRankTree &other) {
    if (&other != this) {
        Tree::operator=(other);
    }
    return *this;
}


Tree *MaxRankTree::clone() const { return new MaxRankTree(*this); } //Creates a clone of a MaxRankTree


int MaxRankTree::traceTree() {
    MaxRankTree *currTree = this;
    MaxRankTree *returnTree = currTree;
    MaxRankTree *tempTree;
    int size = currTree->children.size();
    int numOfChildren = size;
    int numOfChildrenOfChild;
    std::stack<MaxRankTree *> s;
    s.push(currTree);
    int index = 0;
    while (!s.empty()) {
        for (int i = 0; i < size; i++) {
            numOfChildrenOfChild = ((MaxRankTree *) currTree->children.at(i))->children.size();
            if (numOfChildrenOfChild > numOfChildren) {
                returnTree = (MaxRankTree *) currTree->children.at(i);
                numOfChildren = returnTree->children.size();
                index = i;
            } else {
                if (numOfChildrenOfChild == numOfChildren) {
                    tempTree = (MaxRankTree *) currTree->children.at(i);
                    if (tempTree->depth < returnTree->depth) {
                        returnTree = tempTree;
                        index = i;
                    } else {
                        if (tempTree->depth == returnTree->depth && i < index) {
                            returnTree = tempTree;
                            index = i;
                        }
                    }
                }
            }
            s.push((MaxRankTree *) currTree->children.at(i));
        }
        currTree = s.top();
        s.pop();
        size = currTree->children.size();
    }
    return returnTree->node;

}

Tree *Tree::getNextTree() const {  //for BFS
    return children.back();
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

//Copy Constructor RootTree
RootTree::RootTree(const RootTree &other) : Tree(other) {}

//Assignment Operator RootTree
RootTree &RootTree::operator=(const RootTree &other) {
    if (&other != this) {
        Tree::operator=(other);
    }
    return *this;
}

Tree *RootTree::clone() const { return new RootTree(*this); } //Creates a clone of a RootTree

int RootTree::traceTree() {
    return node;
}





