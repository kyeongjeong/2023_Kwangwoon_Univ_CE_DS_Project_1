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
	NameBSTNode* searchBSTNode(string argType, string arg);
	NameBSTNode* searchPrevBSTNode(NameBSTNode* curNode);
	void printBSTNode(NameBSTNode* curNode, ofstream* flog);
	void deleteBSTNode(string argType, string arg);
};