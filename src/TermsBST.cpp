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

TermsBSTNode* TermsBST::searchBSTNode(string expireDate) {

	TermsBSTNode* curNode = root;
	while(curNode != NULL) {

		if(expireDate < curNode->getExpireDate()) 
			curNode = curNode->getLeft();

		else if(expireDate > curNode->getExpireDate())	
			curNode = curNode->getRight();

		else 
			return curNode;
	}
	return NULL;
}

TermsBSTNode* TermsBST::searchPrevBSTNode(TermsBSTNode* curNode) {

	if(curNode == root)
		return root;
	
	TermsBSTNode* prevNode = root;
	while(prevNode != NULL) {

		if((prevNode->getLeft() != NULL) && ((prevNode->getLeft())->getExpireDate() == curNode->getExpireDate()) )
			return prevNode;
		else if((prevNode->getRight() != NULL) && ((prevNode->getRight())->getExpireDate() == curNode->getExpireDate()))
			return prevNode;
		else if(prevNode->getExpireDate() > curNode->getExpireDate())
			prevNode = prevNode->getLeft();
			
		else if(prevNode->getExpireDate() < curNode->getExpireDate())
			prevNode = prevNode->getRight();
	}
	return NULL;
}

int TermsBST::traversalBSTTerms(TermsBSTNode* curNode, string argType, string arg) {

	if(curNode != NULL) {

		TermsBSTNode* curLeftNode = curNode->getLeft();
		TermsBSTNode* curRightNode = curNode->getRight();
		
		traversalBSTTerms(curLeftNode, argType, arg);

		if(argType == "NAME") {

			if(curNode->getMName() == arg) {
				deleteBSTNode(curNode->getExpireDate());
				increaseDeleteCount();
			}
		}
		else if(argType == "DATE") {

			if(curNode->getExpireDate() < arg) {
				deleteBSTNode(curNode->getExpireDate());
				increaseDeleteCount();
			}
		}
		traversalBSTTerms(curRightNode, argType, arg);
	}
	return deleteCount;
}

bool TermsBST::deleteBSTNode(string arg) {

	TermsBSTNode *curNode = searchBSTNode(arg);
	if(curNode == NULL) 
		return false;
	TermsBSTNode *prevNode = searchPrevBSTNode(curNode);

	if ((curNode->getLeft() == NULL) && curNode->getRight() == NULL) {

		if (curNode == root)
			root = NULL;

		else if (prevNode->getLeft() == curNode)
			prevNode->setLeft(NULL);

		else if (prevNode->getRight() == curNode)
			prevNode->setRight(NULL);

		delete curNode;
		return true;
	}

	else if (curNode->getLeft() == NULL) {

 		if (curNode == root)
			root = curNode->getRight();

		else if (prevNode->getLeft() == curNode)
			prevNode->setLeft(curNode->getRight());

		else
			prevNode->setRight(curNode->getRight());

		delete curNode;
		return true;
	}

	else if (curNode->getRight() == NULL) {

		if (curNode == root)
			root = curNode->getLeft();

		else if (prevNode->getLeft() == curNode)
			prevNode->setLeft(curNode->getLeft());

		else
			prevNode->setRight(curNode->getLeft());

		delete curNode;
		return true;
	}

	else {

		TermsBSTNode *minNode = curNode->getRight();
		TermsBSTNode *minPrevNode;

		if (minNode->getLeft() != NULL) {
			while (minNode->getLeft()->getLeft() != NULL)
				minNode = minNode->getLeft();
		}

		if (minNode->getLeft() != NULL) {
			minPrevNode = minNode;
			minNode = minNode->getLeft();
		}
		else
			minPrevNode = curNode;

		curNode->setMName(minNode->getMName());
		curNode->setMAge(minNode->getMAge());
		curNode->setInfoDate(minNode->getInfoDate());
		curNode->setExpireDate(minNode->getExpireDate());

		if((minNode->getRight() != NULL) || (curNode != minPrevNode))
			minPrevNode->setLeft(minNode->getRight());
		else if(curNode == minPrevNode)
			minPrevNode->setRight(minNode->getRight());
		else	
			minPrevNode->setRight(NULL);

		delete minNode;
		return true;
	}
}