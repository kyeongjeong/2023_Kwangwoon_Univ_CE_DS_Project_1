#pragma once
#include <iostream>
using namespace std;

class TermsBSTNode
{
private:

	TermsBSTNode*	left;
	TermsBSTNode*	right;
	string mName;
	int mAge;
	string infoDate;
	string expireDate;

public:
	TermsBSTNode(string mName, int mAge, string infoDate, string expireDate) {

		this->mName = mName;
		this->mAge = mAge;
		this->infoDate = infoDate;
		this->expireDate = expireDate;
		this->left = NULL;
		this->right = NULL;
	}
	~TermsBSTNode() {}

	TermsBSTNode*	getLeft()			{ return left; }
	TermsBSTNode*	getRight()			{ return right; }

	void setLeft (TermsBSTNode* left)		{ this->left = left; }
	void setRight(TermsBSTNode* right)		{ this->right = right; }
	void setMName(string mName) 			{ this-> mName = mName; }
	int setMAge(int mAge)					{ this->mAge = mAge; }
	void setInfoDate(string infoDate) 		{ this-> infoDate = infoDate; }
	void setExpireDate(string expireDate) 	{ this-> expireDate = expireDate; }

	string getMName()		{ return mName; }
	int getMAge()			{ return mAge; }
	string getInfoDate()	{ return infoDate; }
	string getExpireDate()	{ return expireDate; }
};