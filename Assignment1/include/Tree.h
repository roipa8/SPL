#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "stack"

class Session;

class Tree {
public:
    Tree(int rootLabel);

    Tree(const Tree &other);

    Tree(Tree &&other);

    void addChild(const Tree &child);

    virtual Tree *clone() const = 0;

    void clear();

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    Tree &operator=(const Tree &other);

    Tree &operator=(Tree &&other);

    virtual ~Tree();

    int getNode() const;

    Tree *getNextTree() const;// for BFS

protected:
    int node;
    std::vector<Tree *> children;
    int depth;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    CycleTree(const CycleTree &other);

    CycleTree &operator=(const CycleTree &other);

    virtual Tree *clone() const;

    virtual int traceTree();

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    virtual Tree *clone() const;

    MaxRankTree(int rootLabel);

    MaxRankTree(const MaxRankTree &other);

    MaxRankTree &operator=(const MaxRankTree &other);

    virtual int traceTree();

};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    RootTree(const RootTree &other);

    RootTree &operator=(const RootTree &other);

    virtual Tree *clone() const;

    virtual int traceTree();


};

#endif
