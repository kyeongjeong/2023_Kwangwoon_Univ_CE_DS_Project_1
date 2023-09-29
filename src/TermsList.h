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

	void insertListNode(string mName, int mAge, string infoDate, string expireDate, string termsType);
	TermsListNode* searchListNode(string termsType);
	bool deleteListNode(string argType, string arg);
};
