#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	void insertBSTNode();

	// search
	// print
	// delete
};