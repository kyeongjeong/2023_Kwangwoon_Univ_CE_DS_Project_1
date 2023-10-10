#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr) {}
TermsBST::~TermsBST() {}

TermsBSTNode* TermsBST::getRoot() { return root; }

void TermsBST::insertBSTNode(TermsBSTNode* newNode) {
	
	if (root == NULL) {
		root = newNode; // If the tree is empty, make the new node the root
		return;
	}

	TermsBSTNode* curNode = root;
	while (curNode != NULL) {
		if (newNode->getExpireDate() < curNode->getExpireDate()) {
			if (curNode->getLeft() == NULL) {
				curNode->setLeft(newNode); // If the left child is empty, insert the new node here
				return;
			}
			curNode = curNode->getLeft(); // Move to the left child
		}
		else {
			if (curNode->getRight() == NULL) {
				curNode->setRight(newNode); // If the right child is empty, insert the new node here
				return;
			}
			curNode = curNode->getRight(); // Move to the right child
		}
	}
}

void TermsBST::printBSTNode(TermsBSTNode* curNode, ofstream* flog) { // Recursively traverses and prints the nodes of the Terms BST in an inorder fashion.

	string memberInfo; // String to store member information

	if (curNode != NULL) { // Check if the current node exists
		printBSTNode(curNode->getLeft(), flog); // Recursively visit and print the left subtree
		memberInfo = curNode->getMName() + "/" + to_string(curNode->getMAge()) + "/" + curNode->getInfoDate() + "/" + curNode->getExpireDate(); // Create a string with member information
		(*flog) << memberInfo << endl; // Write the member information to the log file
		printBSTNode(curNode->getRight(), flog); // Recursively visit and print the right subtree
	}
}

TermsBSTNode* TermsBST::searchBSTNode(string expireDate) { // Searches for a node in the Terms BST based on the given expiration date.

	TermsBSTNode* curNode = root; // Initialize the current node as the root of the BST

	while (curNode != NULL) { // Continue searching while the current node is not NULL

		if (expireDate < curNode->getExpireDate())
			curNode = curNode->getLeft(); // If the target date is smaller, move to the left subtree
		
		else if (expireDate > curNode->getExpireDate())
			curNode = curNode->getRight(); // If the target date is larger, move to the right subtree
		
		else
			return curNode; // If the target date matches the current node's date, return the current node
	}
	return NULL; // If the target date is not found in the BST, return NULL
}

TermsBSTNode* TermsBST::searchPrevBSTNode(TermsBSTNode* curNode) { // Searches for the previous node of a given node in the Terms BST.

	if (curNode == root)
		return root; // If the given node is the root, there is no previous node.

	TermsBSTNode* prevNode = root; // Initialize the previous node as the root of the BST

	while (prevNode != NULL) { // Continue searching while the previous node is not NULL

		if ((prevNode->getLeft() != NULL) && ((prevNode->getLeft())->getExpireDate() == curNode->getExpireDate()))
			return prevNode; // If the left child of the previous node has the same expiration date as the given node, return the previous node
		
		else if ((prevNode->getRight() != NULL) && ((prevNode->getRight())->getExpireDate() == curNode->getExpireDate()))
			return prevNode; // If the right child of the previous node has the same expiration date as the given node, return the previous node
		
		else if (prevNode->getExpireDate() > curNode->getExpireDate())
			prevNode = prevNode->getLeft(); // If the expiration date of the previous node is greater than the given node's date, move to the left subtree
		
		else if (prevNode->getExpireDate() < curNode->getExpireDate())
			prevNode = prevNode->getRight(); // If the expiration date of the previous node is less than the given node's date, move to the right subtree
	}
	return NULL; // If no previous node is found, return NULL
}

int TermsBST::traversalBSTTerms(TermsBSTNode* curNode, string argType, string arg) {

    if (curNode != NULL) {

        TermsBSTNode* curLeftNode = curNode->getLeft(); // Reference to the current node's left child
        TermsBSTNode* curRightNode = curNode->getRight(); // Reference to the current node's right child

        traversalBSTTerms(curLeftNode, argType, arg); // Recursively traverse the left subtree
        traversalBSTTerms(curRightNode, argType, arg); // Recursively traverse the right subtree

        if (argType == "NAME") { // If the argument type is "NAME"
            if (curNode->getMName() == arg) { // If the current node's name matches the argument

                deleteBSTNode(curNode->getExpireDate()); // Delete the node
                increaseDeleteCount(); // Increment the delete count
                return deleteCount; // Return the updated delete count
            }
        }
        else if (argType == "DATE") { // If the argument type is "DATE"
            if (curNode->getExpireDate() < arg) { // If the current node's expiration date is less than the argument

                deleteBSTNode(curNode->getExpireDate()); // Delete the node
                increaseDeleteCount(); // Increment the delete count
            }
        }
    }
    return deleteCount; // Return the delete count
}

bool TermsBST::deleteBSTNode(string arg) {
    
    TermsBSTNode* curNode = searchBSTNode(arg); // Find the node to be deleted
    if (curNode == NULL)
        return false; // Return false if the node to be deleted is not found

    TermsBSTNode* prevNode = searchPrevBSTNode(curNode); // Find the previous node of the node to be deleted

    if ((curNode->getLeft() == NULL) && (curNode->getRight() == NULL)) { // Case 1: Node to be deleted is a leaf node
        
		if (curNode == root)
            root = NULL; // If the node to be deleted is the root node, set the root to NULL
        
		else if (prevNode->getLeft() == curNode)
            prevNode->setLeft(NULL); // Remove the reference to the node to be deleted
        
		else if (prevNode->getRight() == curNode)
            prevNode->setRight(NULL); // Remove the reference to the node to be deleted

        delete curNode; // Delete the node
        return true; // Return true to indicate successful deletion
    }
    else if (curNode->getLeft() == NULL) { // Case 2: Node to be deleted has a right child only

        if (curNode == root)
            root = curNode->getRight(); // If the node to be deleted is the root node, update the root
        
		else if (prevNode->getLeft() == curNode)
            prevNode->setLeft(curNode->getRight()); // Update the previous node's reference to the node to be deleted
        
		else
            prevNode->setRight(curNode->getRight()); // Update the previous node's reference to the node to be deleted

        delete curNode; // Delete the node
        return true; // Return true to indicate successful deletion
    }
    else if (curNode->getRight() == NULL) { // Case 3: Node to be deleted has a left child only

        if (curNode == root)
            root = curNode->getLeft(); // If the node to be deleted is the root node, update the root

        else if (prevNode->getLeft() == curNode)
            prevNode->setLeft(curNode->getLeft()); // Update the previous node's reference to the node to be deleted

        else
            prevNode->setRight(curNode->getLeft()); // Update the previous node's reference to the node to be deleted

        delete curNode; // Delete the node
        return true; // Return true to indicate successful deletion
    }
    else { // Case 4: Node to be deleted has both left and right children

        TermsBSTNode* minNode = curNode->getRight();
        TermsBSTNode* minPrevNode;

        if (minNode->getLeft() != NULL) { // Find the minimum node in the right subtree
            while (minNode->getLeft()->getLeft() != NULL)
                minNode = minNode->getLeft();
        }

        if (minNode->getLeft() != NULL) {
            minPrevNode = minNode;
            minNode = minNode->getLeft();
        }
        else
            minPrevNode = curNode;

        // Copy the data of the minimum node to the current node
        curNode->setMName(minNode->getMName());
        curNode->setMAge(minNode->getMAge());
        curNode->setInfoDate(minNode->getInfoDate());
        curNode->setExpireDate(minNode->getExpireDate());

        // Update the previous node's left child to point to the minimum node's right child
        if ((minNode->getRight() != NULL) || (curNode != minPrevNode))
            minPrevNode->setLeft(minNode->getRight());		
        else if (curNode == minPrevNode)
            minPrevNode->setRight(minNode->getRight());
        else
            minPrevNode->setRight(NULL);

        delete minNode; // Delete the minimum node
        return true; // Return true to indicate successful deletion
    }
}