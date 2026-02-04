#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    void* data; // can be of any type
    Node* next;

    Node(void* d, Node* n);
    Node(void* d);
};

class LinkedList {
public:
    Node* head;
    Node* tail;
    int size;
    
    // Basic operations
    LinkedList();
    ~LinkedList();
    
    // Move Semantics
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;
    
    // Delete Copy Semantics to prevent accidental shallow copies that cause double free
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void addNode(void* data);
    void removeNode(void* data);
    Node* findNode(void* data);
    void printList();
    void clear();
};

#endif