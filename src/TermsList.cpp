#include "TermsList.h"

TermsLIST::TermsLIST(): head(nullptr)
{

}
TermsLIST::~TermsLIST()
{

}

TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
bool TermsLIST::insertNode(string termsType) {

	TermsListNode* curNode = head;
	while(curNode != NULL) {

		if(curNode->getTermsType() == termsType) {
			curNode->setMCount();
			return true;
		}
		curNode = curNode->getNext();
	}

	TermsListNode* newNode = new TermsListNode(termsType);
	newNode->setMCount();

	if(head == NULL) {
		head = newNode;
		return true;
	}

	curNode = head;
	while(curNode->getNext() != NULL)
		curNode = curNode->getNext();
	curNode->setNext(newNode);

	return true;
}

// search

// delete