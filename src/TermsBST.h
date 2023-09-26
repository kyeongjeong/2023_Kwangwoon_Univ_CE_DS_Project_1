#pragma once
#include "TermsBSTNode.h"
#include <iostream>
#include <string>
using namespace std;

class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	void insertBSTNode(TermsBSTNode* newNode, string termsType);

	// print
	void printBSTNode();

	// delete

	string calculateExpireDate(string infoDate, string termsType);
	int compareDate(string dateStr1, string dateStr2);
};