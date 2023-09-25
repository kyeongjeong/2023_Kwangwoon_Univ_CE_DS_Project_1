#pragma once
#include "MemberQueueNode.h"
#include <iostream>

class MemberQueue
{
private:
	MemberQueueNode* first;
	MemberQueueNode* rear;
	int size;
	int capacity;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(string mName, int mAge, string infoDate, string termsType);
	MemberQueueNode pop();
	MemberQueueNode* front();
};