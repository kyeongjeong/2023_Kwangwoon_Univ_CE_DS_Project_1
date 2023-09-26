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

void TermsLIST::insertListNode(string mName, int mAge, string infoDate, string expireDate, string termsType) {

	TermsListNode* curNode = head;
	while(curNode != NULL) {

		if(curNode->getTermsType() == termsType) {
			curNode->setMCount();

			TermsBSTNode* newBSTNode = new TermsBSTNode(mName, mAge, infoDate, expireDate);
			curNode->getTBST()->insertBSTNode(newBSTNode);

			return;
		}
		curNode = curNode->getNext();
	}

	TermsListNode* newListNode = new TermsListNode(termsType);
	newListNode->setMCount();
	TermsBSTNode* newBSTNode = new TermsBSTNode(mName, mAge, infoDate, expireDate);

	if(head == NULL) {
		head = newListNode;
		head->getTBST()->insertBSTNode(newBSTNode);
		return;
	}

	curNode = head;
	while(curNode->getNext() != NULL)
		curNode = curNode->getNext();
	
	curNode->setNext(newListNode);
	curNode = curNode->getNext();
	curNode->getTBST()->insertBSTNode(newBSTNode);

	return;
}

TermsListNode* TermsLIST::searchListNode(string termsType) {

	TermsListNode* curNode = head;
	while(curNode != NULL) {
		if(curNode->getTermsType() == termsType)
			return curNode;
		curNode = curNode->getNext();
	}
	return NULL;
}

// delete