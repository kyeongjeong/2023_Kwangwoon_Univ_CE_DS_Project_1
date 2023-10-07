#include "MemberQueue.h"

MemberQueue::MemberQueue() {

    this->capacity = 100;
    this->size = -1;
}

MemberQueue::~MemberQueue() {}

bool MemberQueue::empty() { return (this->size == -1); } // Return true if MemberQueue is empty

bool MemberQueue::full() { return (size == (capacity - 1)); } // Return true if MemberQueue is full

void MemberQueue::push(string mName, int mAge, string infoDate, string termsType) {

    MemberQueueNode* newNode = new MemberQueueNode(mName, mAge, infoDate, termsType); // Create a new MemberQueueNode

    if (empty()) {

        this->first = newNode; // If the queue is empty, set the first node to the new node
        this->rear = newNode;  // Also, set the rear node to the new node
        ++size; // Increase the size of the queue
        return; // Return to exit the function
    }

    (this->rear)->setNext(newNode); // If the queue is not empty, set the next pointer of the rear node to the new node
    this->rear = newNode; // Update the rear node to the new node
    ++size; // Increase the size of the queue
}

MemberQueueNode MemberQueue::pop() {

    MemberQueueNode* curNode = first; // Get the front node of the queue
    --size; // Decrease the size of the queue

    if (!empty()) 
        first = first->getNext(); // Move the first pointer to the next node if the queue is not empty
    else 
        first = NULL; // Set the first pointer to NULL if the queue is empty

    MemberQueueNode* tempNode = new MemberQueueNode(curNode->getMName(), curNode->getMAge(), curNode->getInfoDate(), curNode->getTermsType()); // Create a temporary node with the data from the front node
    delete curNode; // Delete the front node
    return *tempNode; // Return the data stored in the temporary node
}

MemberQueueNode* MemberQueue::front() { return first; } // Return the first node of MemberQueue