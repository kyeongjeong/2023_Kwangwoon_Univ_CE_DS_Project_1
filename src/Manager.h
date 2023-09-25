#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class Manager
{
private:
	ifstream	fcmd;
	ofstream	flog;

public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	bool LOAD(MemberQueue* mQueue);
	bool ADD(MemberQueue* mQueue);
	bool QPOP(MemberQueue* mQueue, NameBST* nBST, TermsLIST* tLIST,TermsBST* tBST);

	// SEARCH
	// PRINT
	// DELETE
};
