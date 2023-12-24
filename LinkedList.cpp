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
    Node *current = head;
    Node *pre = nullptr;

    while (current != nullptr && current->value != val){
        pre = current;
        current = current->next;
    }

    if (current == nullptr){
        std::cout << "Value " << val << " not found!" << std::endl;
        return;
    }

    if (pre == nullptr){
        head = current->next;
    }else{
        pre->next = current->next;
    }

    delete current;
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

Node* LinkedList::getTail(){
    Node* current = head;
    if(current == nullptr) return head;
    while (current->next != nullptr){
        current = current->next;
    }
    return current;
}