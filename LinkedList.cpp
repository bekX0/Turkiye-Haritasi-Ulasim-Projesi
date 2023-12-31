#include "LinkedList.h"

// construttor
Node::Node(int value) : value{value}, edgeCost{0}, next{nullptr} {};

// constructor
LinkedList::LinkedList() : head{nullptr} {};
LinkedList::LinkedList(const LinkedList& L) : head{L.head} {};

// destructor
LinkedList::~LinkedList(){
    while (head != nullptr){
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

// insert method
void LinkedList::insert(int val)
{
    Node *newNode = new Node(val);

    if (head == nullptr){
        head = newNode;
    }else{
        Node *current = head;
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
    }
}

// remove method
void LinkedList::remove(int val){
    Node* current = head;
    
    if(!current) return;

    while(current->next && current->next->value != val){
        current = current->next;
    }

    if(!current->next){
        std::cout << "City with code " << val << " is not exists!"<< std::endl;
    }else{
        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
    }
}

// display  method
std::ostream &operator<<(std::ostream &os, const LinkedList &L){
    Node* current = L.head;
    while (current->next != nullptr){
        os << current->value << "(" << current->edgeCost << ")" << "->";
        current = current->next;
    }
    return os;
}

Node* LinkedList::getHead(){
    return head;
}