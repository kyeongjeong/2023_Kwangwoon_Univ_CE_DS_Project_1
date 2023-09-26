#include "NameBST.h"

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()
{
	return root;
}

void NameBST::insertBSTNode(string mName, int mAge, string infoDate, string expireDate, string termsType) {

	NameBSTNode* newNode = new NameBSTNode(mName, mAge, infoDate, expireDate, termsType);
	if(root == NULL) {
		root = newNode;
		return;
	}

	NameBSTNode* curNode = root;
	while(curNode != NULL) {

		if(newNode->getMName() < curNode->getMName()) {
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

NameBSTNode* NameBST::searchBSTNode(string mName) {

	NameBSTNode* curNode = root;
	while(curNode != NULL) {

		if(mName < curNode->getMName()) 
			curNode = curNode->getLeft();

		else if(mName > curNode->getMName())	
			curNode = curNode->getRight();

		else 
			return curNode;
	}
	return NULL;	
}

NameBSTNode* NameBST::searchPrevBSTNode(NameBSTNode* curNode) {

	if(curNode == root)
		return root;
	
	NameBSTNode* prevNode = root;
	while(prevNode != NULL) {

		if(prevNode->getLeft()->getMName() == curNode->getMName() || prevNode->getRight()->getMName() == curNode->getMName())
			return prevNode;

		else if(prevNode->getMName() > curNode->getMName())
			prevNode = prevNode->getLeft();
			
		else if(prevNode->getMName() < curNode->getMName())
			prevNode = prevNode->getRight();
	}
	return NULL;
}

void NameBST::printBSTNode(NameBSTNode* curNode, ofstream* flog) {

	string memberInfo;
	if(curNode != NULL) {

		printBSTNode(curNode->getLeft(), flog);
		memberInfo = curNode->getMName() + "/" + to_string(curNode->getMAge()) + "/" + curNode->getInfoDate() + "/" + curNode->getExpireDate();
		(*flog) << memberInfo << endl;
		printBSTNode(curNode->getRight(), flog);
	}
}

void NameBST::deleteBSTNode(string argType, string arg) {
	
	if(argType == "DATE") {

	}
	else if(argType == "NAME") {

		NameBSTNode* curNode = searchBSTNode(arg);
		NameBSTNode* prevNode = searchPrevBSTNode(curNode);

		if((curNode->getLeft() == NULL) && curNode->getRight() == NULL) {

			if(curNode == root) 
				root = NULL;

			else if(prevNode->getLeft() == curNode)
				prevNode->setLeft(NULL);

			else if(prevNode->getRight() == curNode)
				prevNode->setRight(NULL);
		}
		else if((curNode->getLeft() == NULL) || curNode->getRight() == NULL) {
			;
		}
	}
	return;
}