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
	NameBSTNode() {
		this->mName = mName;
		this->mAge = mAge;
		this->infoDate = infoDate;
		this->expireDate = expireDate;
	
	}
	~NameBSTNode() {}

	NameBSTNode*	getLeft()			{ return left; }
	NameBSTNode*	getRight()			{ return right; }

	void setLeft(NameBSTNode* left)						{ this->left = left; }
	void setRight(NameBSTNode* right)					{ this->right = right; }
};