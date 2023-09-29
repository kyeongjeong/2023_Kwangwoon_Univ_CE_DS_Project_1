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
			curNode->increaseMCount();

			TermsBSTNode* newBSTNode = new TermsBSTNode(mName, mAge, infoDate, expireDate);
			curNode->getTBST()->insertBSTNode(newBSTNode);

			return;
		}
		curNode = curNode->getNext();
	}

	TermsListNode* newListNode = new TermsListNode(termsType);
	newListNode->increaseMCount();
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

bool TermsLIST::deleteListNode(string argType, string arg) {

	TermsListNode* curNode = head;
	TermsListNode* prevNode = head;
	int isDelete = 0;

	while(curNode != NULL) {

		TermsBST* curTBST = curNode->getTBST();
		curTBST->initDeleteCount();
		curTBST->traversalBSTTerms(curTBST->getRoot(), argType, arg);
			
		int deleteCount = curTBST->getDeleteCount();
		for(int i = 0; i < deleteCount; i++) {
			curNode->decreaseMCount();
			++isDelete;
		}

		if(curNode->getMCount() == 0) {

			if(curNode == head) {
				if(curNode->getNext() != NULL)
					head == curNode->getNext();
				else
					head = NULL;
			}
			else {
				if(curNode->getNext() != NULL)
					prevNode->setNext(curNode->getNext());
				else
					prevNode->setNext(NULL);
			}
			delete curNode;
		}	
		prevNode = curNode;
		curNode = curNode->getNext();
	}
	if(isDelete == 0)
		return false;
	return true;
}