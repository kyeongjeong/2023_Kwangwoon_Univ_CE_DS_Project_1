#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
    this->capacity = 100;
    this->size = -1;
}

MemberQueue::~MemberQueue()
{

}

bool MemberQueue::empty()
{
    return (this->size == -1);
}

bool MemberQueue::full()
{
    return (size == (capacity - 1));
}

void MemberQueue::push(string mName, int mAge, string infoDate, string termsType)
{
    MemberQueueNode* newNode =  new MemberQueueNode(mName, mAge, infoDate, termsType);

    if(empty()) {

        this->first = newNode;
        this->rear = newNode;
        ++size;
        return;
    }

    (this->rear)->setNext(newNode);
    this->rear = newNode;
    ++size;
}

MemberQueueNode MemberQueue::pop()
{
    MemberQueueNode* curNode = first;
    --size;

    if(!empty()) 
        first = first->getNext(); 
    else 
        first = NULL; 

    MemberQueueNode* tempNode = new MemberQueueNode(curNode->getMName(), curNode->getMAge(), curNode->getInfoDate(), curNode->getTermsType());
    delete curNode;
    return *tempNode;
}

MemberQueueNode* MemberQueue::front()
{
    return first;
}