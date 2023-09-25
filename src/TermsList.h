#pragma once
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();

	// insert
	bool insertNode(string termsType);

	// search
	// delete
};
