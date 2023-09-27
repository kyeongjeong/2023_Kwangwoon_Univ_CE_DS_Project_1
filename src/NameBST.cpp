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

NameBSTNode* NameBST::searchBSTNode(string argType, string arg) {

	NameBSTNode* curNode = root;

	if(argType == "NAME") {

		while(curNode != NULL) {

			if(arg < curNode->getMName()) 
				curNode = curNode->getLeft();
			else if(arg > curNode->getMName())	
				curNode = curNode->getRight();
			else 
				return curNode;
		}
		return NULL;
	}	

	if(argType == "DATE") {

		while(curNode != NULL) {

			if(arg < curNode->getMName()) 
				curNode = curNode->getLeft();
			else if(arg > curNode->getMName())	
				curNode = curNode->getRight();
			else 
				return curNode;
		}
		return NULL;
	}
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
		;
	}
	else if(argType == "NAME") {

		NameBSTNode* curNode = searchBSTNode(argType, arg);
		NameBSTNode* prevNode = searchPrevBSTNode(curNode);

		if((curNode->getLeft() == NULL) && curNode->getRight() == NULL) {

			if(curNode == root) 
				root = NULL;

			else if(prevNode->getLeft() == curNode)
				prevNode->setLeft(NULL);

			else if(prevNode->getRight() == curNode)
				prevNode->setRight(NULL);
		}
		else if(curNode->getLeft() == NULL) {

			if(curNode == root)
				root = curNode->getRight();
			
			else if(prevNode->getLeft() == curNode)
				prevNode->setLeft(curNode->getRight());

			else
				prevNode->setRight(curNode->getRight());
		}
		else if(curNode->getRight() == NULL) {
			
			if(curNode == root)
				root = curNode->getLeft(); 
			
			else if(prevNode->getLeft() == curNode)
				prevNode->setLeft(curNode->getLeft());

			else
				prevNode->setRight(curNode->getLeft());
		}
		else {

			NameBSTNode* minNode = curNode->getRight();
			NameBSTNode* minPrevNode;

			if(minNode->getLeft() != NULL) {
				while(minNode->getLeft()->getLeft() != NULL)
					minNode = minNode->getLeft();
			}

			if(minNode->getLeft() != NULL) {
				minPrevNode = minNode;
				minNode = minNode->getLeft();
			}
			else
				minPrevNode = curNode;
			
			if(curNode == root)
				root = minNode;
			else {

				if(prevNode->getLeft() == curNode)
					prevNode->setLeft(minNode);
				else
					prevNode->setRight(minNode);
				
				if((minNode->getRight() != NULL) && (curNode != minPrevNode)) {

					if(minNode -> getRight() != NULL) {

						minPrevNode->setRight(minNode->getRight());
						minPrevNode->setLeft(NULL);
						minNode->setRight(minPrevNode);
					}
				}
			}
			minNode->setLeft(curNode->getLeft());
			delete curNode;
		}
	}
	return;
}