#pragma once
#include "TermsBSTNode.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	void insertBSTNode(TermsBSTNode* newNode);
	void printBSTNode(TermsBSTNode* curNode, ofstream* flog);

	// delete

	string calculateExpireDate(string infoDate, string termsType);
};