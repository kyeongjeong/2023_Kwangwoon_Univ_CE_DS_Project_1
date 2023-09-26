#pragma once
#include <iostream>
#include "TermsBST.h"
using namespace std;

class TermsListNode
{
private:
	string termsType;
	int mCount;
	TermsListNode* next;
	TermsBST* tBST;

public:
	TermsListNode(string termsType) {

		this->termsType = termsType;
		this->mCount = 0;
		this->next = NULL;

		tBST = new TermsBST();
	}
	~TermsListNode() {}

	TermsListNode* getNext()	{ return next; }
	string getTermsType()		{ return termsType; }
	int getMCount() 			{ return mCount; }
	TermsBST* getTBST() 		{ return tBST; }
 
	void setNext(TermsListNode* next)					{ this->next = next; }
	void setMCount() 									{ ++this->mCount; }
};