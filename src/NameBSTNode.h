#pragma once
#include <iostream>
using namespace std;

class NameBSTNode
{
private:
	string mName;
	int mAge;
	string infoDate;
	string expireDate;
	string termsType;

	NameBSTNode*	left;
	NameBSTNode*	right;
	

public:
	NameBSTNode(string mName, int mAge, string infoDate, string expireDate, string termsType) {
		this->mName = mName;
		this->mAge = mAge;
		this->infoDate = infoDate;
		this->expireDate = expireDate;
		this->termsType = termsType;
	}
	~NameBSTNode() {}

	NameBSTNode* getLeft()	{ return left; }
	NameBSTNode* getRight()	{ return right; }
	string getMName()		{ return mName; }
	int getMAge()			{ return mAge; }
	string getInfoDate()	{ return infoDate; }
	string getExpireDate()	{ return expireDate; }
	string getTermsType()	{ return termsType; }

	void setLeft(NameBSTNode* left)		{ this->left = left; }
	void setRight(NameBSTNode* right)	{ this->right = right; }
};