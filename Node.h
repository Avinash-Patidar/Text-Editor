#ifndef NODE_H
#define NODE_H

class Node{
public:
    char data;
    Node* next;
    Node* prev;

    Node(char data){
        this->data=data;
        next=prev=nullptr;
    }
};

#endif