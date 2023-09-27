#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{

}
TermsBST::~TermsBST()
{

}


TermsBSTNode* TermsBST::getRoot()
{
	return root;
}

void TermsBST::insertBSTNode(TermsBSTNode* newNode) {
	
	if(root == NULL) {
		root = newNode;
		return;
	}

	TermsBSTNode* curNode = root;
	while(curNode != NULL) {

		//if(newNode->getExpireDate() < curNode->getExpireDate()) {
		if(compareDate(newNode->getExpireDate(), curNode->getExpireDate()) < 0) {
			if(curNode->getLeft() == NULL) {
				curNode->setLeft(newNode);
				return;
			}
			curNode = curNode->getLeft();
		}
		else {
			if(curNode->getRight() == NULL) {
				curNode->setRight(newNode);
				return;
			}
			curNode = curNode->getRight();
		}
	}
}

void TermsBST::printBSTNode(TermsBSTNode* curNode, ofstream* flog) {

	string memberInfo;
	if(curNode != NULL) {

		printBSTNode(curNode->getLeft(), flog);
		memberInfo = curNode->getMName() + "/" + to_string(curNode->getMAge()) + "/" + curNode->getInfoDate() + "/" + curNode->getExpireDate();
		(*flog) << memberInfo << endl;
		printBSTNode(curNode->getRight(), flog);
	}
}

int TermsBST::compareDate(string dateStr1, string dateStr2) {

	int year1 = stoi(dateStr1.substr(0, 4));
	int month1 = stoi(dateStr1.substr(5, 2));
    int day1 = stoi(dateStr1.substr(8, 2));

	int year2 = stoi(dateStr2.substr(0, 4));
	int month2 = stoi(dateStr2.substr(5, 2));
    int day2 = stoi(dateStr2.substr(8, 2));

    if (year1 != year2) {
        return (year1 < year2) ? -1 : 1;
    } else if (month1 != month2) {
        return (month1 < month2) ? -1 : 1; 
    } else if (day1 != day2) {
        return (day1 < day2) ? -1 : 1;
    }
}