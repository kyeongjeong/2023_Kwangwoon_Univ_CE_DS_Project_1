#include "NameBST.h"

NameBST::NameBST() : root(nullptr) {}
NameBST::~NameBST() {}

NameBSTNode* NameBST::getRoot() { return root; }

void NameBST::insertBSTNode(string mName, int mAge, string infoDate, string expireDate, string termsType) {

    NameBSTNode* newNode = new NameBSTNode(mName, mAge, infoDate, expireDate, termsType); // Create a new NameBSTNode with the provided data

    if (root == NULL) {
        root = newNode; // If the tree is empty, set the root to the new node
        return; // Return to exit the function
    }

    NameBSTNode* curNode = root; // Start from the root node for traversal
    while (curNode != NULL) {

        if (newNode->getMName() < curNode->getMName()) {
            if (curNode->getLeft() == NULL) {
                curNode->setLeft(newNode); // If the new node's name is smaller, go left and insert if left child is empty
                return; // Return to exit the function
            }
            curNode = curNode->getLeft(); // Move to the left child
        }
        else {
            if (curNode->getRight() == NULL) {
                curNode->setRight(newNode); // If the new node's name is larger or equal, go right and insert if right child is empty
                return; // Return to exit the function
            }
            curNode = curNode->getRight(); // Move to the right child
        }
    }
}

NameBSTNode* NameBST::searchBSTNode(string mName) {

    NameBSTNode* curNode = root; // Start the search from the root node
    while (curNode != NULL) {

        if (mName < curNode->getMName()) 
            curNode = curNode->getLeft(); // If the target name is smaller, go left
        
        else if (mName > curNode->getMName()) 
            curNode = curNode->getRight(); // If the target name is larger, go right
        
        else 
            return curNode; // If the target name matches the current node's name, return the current node
    }
    return NULL; // If the target name is not found in the tree, return NULL
}

NameBSTNode* NameBST::searchPrevBSTNode(NameBSTNode* curNode) {

    if (curNode == root)
        return root; // If the current node is the root, there is no previous node, so return the root

    NameBSTNode* prevNode = root; // Initialize the previous node as the root
    while (prevNode != NULL) {

        if ((prevNode->getLeft() != NULL) && ((prevNode->getLeft())->getMName() == curNode->getMName()))
            return prevNode; // If the left child of the previous node matches the current node's name, return the previous node

        else if ((prevNode->getRight() != NULL) && ((prevNode->getRight())->getMName() == curNode->getMName()))
            return prevNode; // If the right child of the previous node matches the current node's name, return the previous node

        else if (prevNode->getMName() > curNode->getMName())
            prevNode = prevNode->getLeft(); // If the previous node's name is greater than the current node's name, move left

        else if (prevNode->getMName() < curNode->getMName())
            prevNode = prevNode->getRight(); // If the previous node's name is less than the current node's name, move right
    }
    return NULL; // If no previous node is found, return NULL
}

void NameBST::printBSTNode(NameBSTNode* curNode, ofstream* flog) {

    string memberInfo; // Initialize a string to store member information
    if (curNode != NULL) {

        printBSTNode(curNode->getLeft(), flog); // Recursively print the left subtree first
        memberInfo = curNode->getMName() + "/" + to_string(curNode->getMAge()) + "/" + curNode->getInfoDate() + "/" + curNode->getExpireDate(); // Construct member information string
        (*flog) << memberInfo << endl; // Write the member information to the log file
        printBSTNode(curNode->getRight(), flog); // Recursively print the right subtree
    }
}

bool NameBST::traversalBSTTerms(NameBSTNode* curNode, string expireDate, bool isExist) {

    if (curNode != NULL) {
        traversalBSTTerms(curNode->getLeft(), expireDate, isExist); // Recursively traverse the left subtree
        traversalBSTTerms(curNode->getRight(), expireDate, isExist); // Recursively traverse the right subtree
        
        if (curNode->getExpireDate() < expireDate) { // Check if the current node's expiration date is earlier than the specified date
            
            deleteBSTNode(curNode->getMName()); // If it is, delete the current node from the tree
            isExist = true; // Set the flag to indicate that a node was deleted
        }
    }
    return isExist; // Return the flag indicating whether any nodes were deleted during traversal
}

bool NameBST::deleteBSTNode(string arg) {

    NameBSTNode* curNode = searchBSTNode(arg); // Search for the node with the given name
    if (curNode == NULL) 
        return false; // If the node does not exist, return false

    NameBSTNode* prevNode = searchPrevBSTNode(curNode); // Find the previous node of the current node

    if ((curNode->getLeft() == NULL) && curNode->getRight() == NULL) { // Case 1: Node has no children

        if (curNode == root)
            root = NULL; // If it's the root node, set root to NULL

        else if (prevNode->getLeft() == curNode)
            prevNode->setLeft(NULL); // If it's a left child, set left child to NULL
        
		else if (prevNode->getRight() == curNode)
            prevNode->setRight(NULL); // If it's a right child, set right child to NULL

        delete curNode; // Delete the current node
        return true; // Return true to indicate successful deletion
    }

    else if (curNode->getLeft() == NULL) { // Case 2: Node has only a right child

        if (curNode == root)
            root = curNode->getRight(); // If it's the root node, update root to the right child
        
		else if (prevNode->getLeft() == curNode)
            prevNode->setLeft(curNode->getRight()); // If it's a left child, set left child to right child
        
		else
            prevNode->setRight(curNode->getRight()); // If it's a right child, set right child to right child

        delete curNode; // Delete the current node
        return true; // Return true to indicate successful deletion
    }

    else if (curNode->getRight() == NULL) { // Case 3: Node has only a left child

        if (curNode == root)
            root = curNode->getLeft(); // If it's the root node, update root to the left child
        
		else if (prevNode->getLeft() == curNode)
            prevNode->setLeft(curNode->getLeft()); // If it's a left child, set left child to left child
        
		else
            prevNode->setRight(curNode->getLeft()); // If it's a right child, set right child to left child

        delete curNode; // Delete the current node
        return true; // Return true to indicate successful deletion
    }

    else { // Case 4: Node has both left and right children

        NameBSTNode* minNode = curNode->getRight(); // Find the minimum node in the right subtree
        NameBSTNode* minPrevNode;

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

        // Copy the data of the minimum node to the current node
        curNode->setMName(minNode->getMName());
        curNode->setMAge(minNode->getMAge());
        curNode->setInfoDate(minNode->getInfoDate());
        curNode->setExpireDate(minNode->getExpireDate());
        curNode->setTermsType(minNode->getTermsType());

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