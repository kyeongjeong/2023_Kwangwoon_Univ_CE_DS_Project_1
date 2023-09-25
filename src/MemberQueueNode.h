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

public:

	MemberQueueNode* next;

	MemberQueueNode(string mName, int mAge, string infoDate, string termsType) {

		this->mName = mName;
		this->mAge = mAge;
		this->infoDate = infoDate;
		this->termsType = termsType;
		this->next = NULL;
	}
	
	~MemberQueueNode() {}

	string getmName() {
		return this->mName;
	}

	int getmAge() {
		return this->mAge;
	}

	string getinfoDate() {
		return this->infoDate;
	}

	string gettermsType() {
		return this->termsType;
	}
};