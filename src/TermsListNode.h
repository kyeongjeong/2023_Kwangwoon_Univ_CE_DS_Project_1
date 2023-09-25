#pragma once
#include <iostream>
#include "TermsBSTNode.h"
using namespace std;

class TermsListNode
{
private:
	string termsType;
	int mCount;
	TermsBSTNode* pTermsBSTNode;
	TermsListNode* next;


public:
	TermsListNode(string termsType) {

		this->termsType = termsType;
		this->mCount = 0;
		this->pTermsBSTNode = NULL;
		this->next = NULL;
	}
	~TermsListNode() {}

	TermsListNode* getNext() { return next; }
	string getTermsType() { return termsType; }
	int getMCount() { return mCount; }

	void setNext(TermsListNode* next)	 { this->next = next; }
	void setMCount() { ++this->mCount; }
};