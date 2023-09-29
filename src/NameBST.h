#pragma once
#include "NameBSTNode.h"
#include <fstream>
using namespace std;

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	void insertBSTNode(string mName, int mAge, string infoDate, string expireDate, string termsType);
	void printBSTNode(NameBSTNode* curNode, ofstream* flog);
	bool deleteBSTNode(string arg);

	NameBSTNode* searchBSTNode(string mName);
	NameBSTNode* searchPrevBSTNode(NameBSTNode* curNode);
	bool traversalBSTTerms(NameBSTNode* curNode, string expireDate, bool isExist);
};