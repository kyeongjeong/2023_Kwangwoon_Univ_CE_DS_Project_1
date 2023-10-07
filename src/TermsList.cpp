#include "TermsList.h"

TermsLIST::TermsLIST(): head(nullptr) {}
TermsLIST::~TermsLIST() {}

TermsListNode* TermsLIST::getHead() { return head; }

void TermsLIST::insertListNode(string mName, int mAge, string infoDate, string expireDate, string termsType) {

    TermsListNode* curNode = head; // Initialize a pointer to traverse the linked list starting from the head

    while (curNode != NULL) { // Traverse the linked list to find a node with matching termsType

        if (curNode->getTermsType() == termsType) { // If a matching node is found
           
		    curNode->increaseMCount(); // Increment the match count for the node
            TermsBSTNode* newBSTNode = new TermsBSTNode(mName, mAge, infoDate, expireDate); // Create a new BST node with the provided data
            curNode->getTBST()->insertBSTNode(newBSTNode); // Insert the new BST node into the termsBST associated with the current node
            return; // Exit the function as the insertion is complete
        }
        curNode = curNode->getNext(); // Move to the next node in the linked list
    }

    TermsListNode* newListNode = new TermsListNode(termsType); // If no matching node is found, create a new TermsListNode
    newListNode->increaseMCount(); // Increment the match count for the new node

    TermsBSTNode* newBSTNode = new TermsBSTNode(mName, mAge, infoDate, expireDate); // Create a new BST node with the provided data
    if (head == NULL) { // If the linked list is empty, set the new node as the head
        head = newListNode;
        head->getTBST()->insertBSTNode(newBSTNode);
        return;
    }

    curNode = head; // Traverse to the end of the linked list to add the new node
    while (curNode->getNext() != NULL)
        curNode = curNode->getNext();

    curNode->setNext(newListNode); // Add the new node as the next node in the linked list
    curNode = curNode->getNext(); // Move to the newly added node
    curNode->getTBST()->insertBSTNode(newBSTNode); // Insert the new BST node into the termsBST associated with the new node
    return; // Exit the function after insertion
}

TermsListNode* TermsLIST::searchListNode(string termsType) {

    TermsListNode* curNode = head; // Initialize a pointer to traverse the linked list starting from the head

    while (curNode != NULL) { // Traverse the linked list to find a node with matching termsType

        if (curNode->getTermsType() == termsType) // If a node with matching termsType is found, return the node
            return curNode;
        curNode = curNode->getNext(); // Move to the next node in the linked list
    }
    return NULL; // Return NULL if no matching node is found
}

bool TermsLIST::deleteListNode(string argType, string arg) {

    TermsListNode* curNode = head; // Initialize a pointer to traverse the linked list starting from the head
    TermsListNode* prevNode = head; // Initialize a pointer to keep track of the previous node
    int isDelete = 0; // Counter to track the number of deletions

    while (curNode != NULL) { // Traverse the linked list

        TermsBST* curTBST = curNode->getTBST(); // Get the TermsBST associated with the current node
        curTBST->initDeleteCount(); // Initialize the delete count in the TermsBST
        curTBST->traversalBSTTerms(curTBST->getRoot(), argType, arg); // Traverse the BST and mark nodes for deletion

        int deleteCount = curTBST->getDeleteCount(); // Get the delete count from the TermsBST
        for (int i = 0; i < deleteCount; i++) {
            curNode->decreaseMCount(); // Decrease the match count for the current node
            ++isDelete; // Increment the deletion counter
        }

        if (curNode->getMCount() == 0) { // If the match count becomes zero

            if (curNode == head) { // If the current node is the head of the linked list
                
				if (curNode->getNext() != NULL)
                    head = curNode->getNext(); // Update the head to the next node
                else
                    head = NULL; // Set the head to NULL if there are no more nodes
            }
            else {
                
				if (curNode->getNext() != NULL)
                    prevNode->setNext(curNode->getNext()); // Link the previous node to the next node
                else
                    prevNode->setNext(NULL); // Set the next of the previous node to NULL if there are no more nodes
            }
            delete curNode; // Delete the current node
        }
        prevNode = curNode; // Update the previous node to the current node
        curNode = curNode->getNext(); // Move to the next node in the linked list
    }
    if (isDelete == 0)
        return false; // Return false if no deletions occurred
    return true; // Return true if deletions were performed
}