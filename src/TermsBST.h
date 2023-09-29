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
	int deleteCount;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	void insertBSTNode(TermsBSTNode* newNode);
	void printBSTNode(TermsBSTNode* curNode, ofstream* flog);
	bool deleteBSTNode(string arg);

	int traversalBSTTerms(TermsBSTNode* curNode, string argType, string arg);
	TermsBSTNode* searchBSTNode(string mName);
	TermsBSTNode* searchPrevBSTNode(TermsBSTNode* curNode);

	void increaseDeleteCount() { ++this->deleteCount; }
	void initDeleteCount() { this->deleteCount = 0; }
	int getDeleteCount() { return deleteCount; }
};