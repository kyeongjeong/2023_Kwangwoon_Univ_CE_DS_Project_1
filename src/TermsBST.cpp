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

		if(newNode->getExpireDate() < curNode->getExpireDate()) {
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