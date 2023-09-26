#pragma once
#include "TermsListNode.h"
#include "TermsBST.h"

class TermsLIST
{
private:
	TermsListNode* head;

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();

	// insert
	void insertListNode(string mName, int mAge, string infoDate, string expireDate, string termsType);

	// search
	// delete
};
