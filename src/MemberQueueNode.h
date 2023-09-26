#pragma once
#include <iostream>
using namespace std;

class MemberQueueNode
{
private:
	string mName;
	int mAge;
	string infoDate;
	string termsType;
	MemberQueueNode* next;

public:

	MemberQueueNode(string mName, int mAge, string infoDate, string termsType) {

		this->mName = mName;
		this->mAge = mAge;
		this->infoDate = infoDate;
		this->termsType = termsType;
		this->next = NULL;
	}
	~MemberQueueNode() {}

	string getMName() 			{ return mName; }
	int getMAge() 				{ return mAge; }
	string getInfoDate() 		{ return infoDate; }
	string getTermsType() 		{ return termsType; }
	MemberQueueNode* getNext() 	{ return next; }

	void setNext(MemberQueueNode* next)	{ this->next = next; }
};