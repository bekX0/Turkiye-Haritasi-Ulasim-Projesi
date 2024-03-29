#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

class Node {
public:
    //attributes
    int value;    // node value
    Node* next;    // next node's pointer
    int edgeCost;

    //constructor
    Node(int value);
};

struct CompareNodes {
    bool operator()(const Node* l, const Node* r) const {
        return l->edgeCost > r->edgeCost;
    }
};

class LinkedList {
private:
    Node* head;

public:
    //constructor
    LinkedList();
    LinkedList(const LinkedList&);

    //destructor
    ~LinkedList();

    // insert method
    void insert(int val);

    //remove method
    void remove(int val);

    // display method
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& L);

    //getter for head
    Node* getHead();
};

#endif
