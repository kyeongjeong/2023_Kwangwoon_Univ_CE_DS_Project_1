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

		if((prevNode->getLeft() != NULL) && ((prevNode->getLeft())->getMName() == curNode->getMName()) )
			return prevNode;
		else if((prevNode->getRight() != NULL) && ((prevNode->getRight())->getMName() == curNode->getMName()))
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

bool NameBST::traversalBSTTerms(NameBSTNode* curNode, string expireDate, bool isExist) {

	if(curNode != NULL) {
		traversalBSTTerms(curNode->getLeft(), expireDate, isExist);
		if(curNode->getExpireDate() < expireDate) {
			
			deleteBSTNode(curNode->getMName());
			isExist = true;
		}
		if(curNode != NULL)
			traversalBSTTerms(curNode->getRight(), expireDate, isExist);
	}
	return isExist;
}

bool NameBST::deleteBSTNode(string arg) {

	NameBSTNode *curNode = searchBSTNode(arg);
	if(curNode == NULL) 
		return false;
	NameBSTNode *prevNode = searchPrevBSTNode(curNode);

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

		NameBSTNode *minNode = curNode->getRight();
		NameBSTNode *minPrevNode;

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
		curNode->setTermsType(minNode->getTermsType());

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