#include "Manager.h"

Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open the command & log file
    fcmd.open(command); // Open the command.txt file
    flog.open("log.txt"); // Open the log.txt file
    if (!fcmd) // If the file doesn't exist or cannot be opened
    {
        flog << "Fail to open the command file" << endl;
        exit(-1);
    }

    MemberQueue mQueue;
    NameBST nBST;
    TermsLIST tLIST;

    // Run commands
    while (!fcmd.eof()) { // Repeat until the end of the command.txt file is reached

        string cmd;
        fcmd >> cmd; // Read the command

        if (cmd == "LOAD") { // If the command is LOAD
            if (!(LOAD(&mQueue))) // If the LOAD function returns false, exit the program
                break;
        }
        else if (cmd == "ADD") { // If the command is ADD
            if (!ADD(&mQueue)) // If the ADD function returns false, exit the program
                break;
        }
        else if (cmd == "QPOP") { // If the command is QPOP
            if (!QPOP(&mQueue, &nBST, &tLIST)) // If the QPOP function returns false, exit the program
                break;
        }
        else if (cmd == "SEARCH") { // If the command is SEARCH
            if (!SEARCH(&nBST)) // If the SEARCH function returns false, exit the program
                break;
        }
        else if (cmd == "PRINT") { // If the command is PRINT
            if (!PRINT(&nBST, &tLIST)) // If the PRINT function returns false, exit the program
                break;
        }
        else if (cmd == "DELETE") { // If the command is DELETE
            if (!DELETE(&nBST, &tLIST)) // If the DELETE function returns false, exit the program
                break;
        }
        else if (cmd == "EXIT") { // If the command is EXIT
            break; // Exit the program after executing the EXIT function
        }
        else { // If the command is invalid
            PrintErrorCode(1000);
        }
    }

    EXIT(&mQueue, &nBST, &tLIST); // Execute the EXIT function
    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

bool Manager::LOAD(MemberQueue* mQueue) {

    ifstream fdata;
    fdata.open("data.txt");
    if (!fdata) {
        PrintErrorCode(100); // Error: Unable to open data file
        return true; // Return true to indicate an error
    }

    string mName, infoDate, termsType;
    int mAge;
    if (!(*mQueue).empty()) { // if mQueue is not empty
        PrintErrorCode(100); // Error: The queue is not empty before loading data
        return true; // Return true to indicate an error
    }

    while (!fdata.eof()) {

        fdata >> mName >> mAge >> infoDate >> termsType;
        if (!(*mQueue).full()) //if mQueue is not full
            (*mQueue).push(mName, mAge, infoDate, termsType); //push values to mQueue
        else {
            PrintErrorCode(100); // Error: The queue is full, unable to load more data
            return false; // Return false to indicate an error
        }
    }

    MemberQueueNode* curNode = (*mQueue).front(); 
    
    flog << "===== LOAD =====" << endl; 
    while (curNode != NULL) {

        flog << curNode->getMName() << "/" << curNode->getMAge() << "/" << curNode->getInfoDate() << "/" << curNode->getTermsType() << endl;
        curNode = curNode->getNext();
    }
    flog << "===============" << endl << endl;

    return true; // Return true to indicate success
}

bool Manager::ADD(MemberQueue* mQueue) {
    
    int mAge;
    string mName, infoDate, termsType;
    string mData;

    getline(fcmd, mData); // Read a line of data from the command file
    stringstream dataStream(mData); // Create a stringstream to parse the data
    string token;

    for (int i = 0; i < 4; ++i) {

        dataStream >> token; // Extract the next token from the stringstream
        if (!dataStream) {
            PrintErrorCode(200); // Error: Missing fields in the data
            return true; // Return true to indicate an error
        }

        switch (i) {
            case 0:
                mName = token; // Assign the first token to mName
                break;
            case 1:
                try {
                    mAge = stoi(token); // Convert the second token to an integer and assign it to mAge
                } 
                catch (const invalid_argument&) {
                    PrintErrorCode(200); // Error: Invalid age format
                    return true; // Return true to indicate an error
                }
                break;
            case 2:
                infoDate = token; // Assign the third token to infoDate
                break;
            case 3:
                termsType = token; // Assign the fourth token to termsType
                break;
        }
    }

    dataStream >> token; // Try to read one more token
    if (dataStream) {
        PrintErrorCode(200); // Error: Extra fields in the data
        return true; // Return true to indicate an error
    }

    if (!(*mQueue).full()) 
        (*mQueue).push(mName, mAge, infoDate, termsType); // Push the parsed data to the queue
    else {
        PrintErrorCode(200); // Error: The queue is full, unable to add more data
        return false; // Return false to indicate an error
    }

    flog << "===== ADD =====" << endl; 
    flog << mName << "/" << mAge << "/" << infoDate << "/" << termsType << endl;
    flog << "===============" << endl << endl;

    return true; // Return true to indicate success
}

bool Manager::QPOP(MemberQueue* mQueue, NameBST* nBST, TermsLIST* tLIST) {

    if ((*mQueue).empty()) {
        PrintErrorCode(300); // Error: Queue is empty, cannot perform QPOP
        return false; // Return false to indicate an error
    }

    MemberQueueNode* curNode = (*mQueue).front(); // Get the front node of the queue
    while (curNode != NULL) {
        
        curNode = (*mQueue).front(); // Get the front node again (might have changed during processing)
        if (curNode != NULL) {
            MemberQueueNode popNode = mQueue->pop(); // Pop the front node from the queue
            string expireDate = calculateExpireDate(popNode.getInfoDate(), popNode.getTermsType()); // Calculate the expiration date
            tLIST->insertListNode(popNode.getMName(), popNode.getMAge(), popNode.getInfoDate(), expireDate, popNode.getTermsType()); // Insert data into the TermsLIST
            nBST->insertBSTNode(popNode.getMName(), popNode.getMAge(), popNode.getInfoDate(), expireDate, popNode.getTermsType()); // Insert data into the NameBST
        }
    }
    PrintSuccess("QPOP"); // Print a success message for QPOP
    return true; // Return true to indicate success
}

string Manager::calculateExpireDate(string infoDate, string termsType) {
    
    int year, month, day;
    sscanf(infoDate.c_str(), "%d-%d-%d", &year, &month, &day); // Parse the information date string into year, month, and day

    int monthsToAdd = 0; // Determine the number of months to add based on the terms type
    if (termsType == "A") {
        monthsToAdd = 6;
    } else if (termsType == "B") {
        monthsToAdd = 12;
    } else if (termsType == "C") {
        monthsToAdd = 24;
    } else if (termsType == "D") {
        monthsToAdd = 36;
    }

    // Calculate the year and month components of the expiration date
    year += (month + monthsToAdd - 1) / 12;
    month = (month + monthsToAdd - 1) % 12 + 1;

    // Create a formatted string for the expiration date
    string expireDate = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-" + (day < 10 ? "0" : "") + to_string(day); 

    return expireDate; // Return the calculated expiration date as a string
}

bool Manager::SEARCH(NameBST* nBST) {

    string mName;
    fcmd >> mName; // Read the member name to be searched from the command file

    NameBSTNode* curNode = nBST->searchBSTNode(mName); // Search for the member in the NameBST
    if (curNode == NULL) {
        PrintErrorCode(400); // Error: Member not found in the NameBST
        return true; // Return true to indicate an error
    }

    // Create a formatted string with the member information
    string searchMemberInfo = curNode->getMName() + "/" + to_string(curNode->getMAge()) + "/" + curNode->getInfoDate() + "/" + curNode->getExpireDate();

    flog << "===== SEARCH =====" << endl; 
    flog << searchMemberInfo << endl; // Log the searched member's information
    flog << "===============" << endl << endl;

    return true; // Return true to indicate success
}

bool Manager::PRINT(NameBST* nBST, TermsLIST* tLIST) {

    string argType;
    fcmd >> argType; // Read the argument type ("NAME", "A", "B", "C", or "D") from the command file

    if (argType == "NAME") {

        if (nBST->getRoot() == NULL) {
            PrintErrorCode(500); // Error: NameBST is empty, cannot print
            return true; // Return true to indicate an error
        }

        flog << "===== PRINT =====" << endl;
        flog << "Name_BST" << endl;
        nBST->printBSTNode(nBST->getRoot(), &flog); // Print the NameBST
        flog << "===============" << endl << endl;
    }
    else if ((argType == "A") || (argType == "B") || (argType == "C") || (argType == "D")) {

        if ((tLIST->getHead() == NULL) || (tLIST->searchListNode(argType) == NULL)) {
            PrintErrorCode(500); // Error: TermsBST with the specified term type is empty or not found
            return true; // Return true to indicate an error
        }

        flog << "===== PRINT =====" << endl;
        flog << "Terms_BST " << argType << endl;

        TermsListNode* tListNode = tLIST->searchListNode(argType); // Search for the specified term type in TermsLIST
        TermsBST* tBST = tListNode->getTBST();
        tBST->printBSTNode(tBST->getRoot(), &flog); // Print the specified TermsBST

        flog << "===============" << endl << endl;
    }
    else {
        PrintErrorCode(500); // Error: Invalid argument type
        return true; // Return true to indicate an error
    }

    return true; // Return true to indicate success
}

bool Manager::DELETE(NameBST* nBST, TermsLIST* tLIST) {

    if ((nBST->getRoot() == NULL) || (tLIST->getHead() == NULL)) {
        string temp1, temp2;
        fcmd >> temp1 >> temp2;
        PrintErrorCode(600); // Error: NameBST or TermsLIST is empty, cannot perform DELETE
        return true; // Return true to indicate an error
    }

    string argType, arg;
    fcmd >> argType >> arg; // Read the argument type ("NAME" or "DATE") and the argument value from the command file

    if (argType == "NAME") {

        if (!nBST->deleteBSTNode(arg)) {
            PrintErrorCode(600); // Error: Failed to delete the specified member from NameBST
            return true; // Return true to indicate an error
        }
        if (!tLIST->deleteListNode(argType, arg)) {
            PrintErrorCode(600); // Error: Failed to delete the specified member from TermsLIST
            return true; // Return true to indicate an error
        }
    }
    else if (argType == "DATE") {

        if (!nBST->traversalBSTTerms(nBST->getRoot(), arg, false)) {
            PrintErrorCode(600); // Error: No members with the specified term date found in NameBST
            return true; // Return true to indicate an error
        }
        if (!tLIST->deleteListNode(argType, arg)) {
            PrintErrorCode(600); // Error: Failed to delete members with the specified term date from TermsLIST
            return true; // Return true to indicate an error
        }
    }
    else {
        PrintErrorCode(600); // Error: Invalid argument type
        return true; // Return true to indicate an error
    }

    PrintSuccess("DELETE"); // Print a success message for DELETE
    return true; // Return true to indicate success
}

bool Manager::EXIT(MemberQueue* mQueue, NameBST* nBST, TermsLIST* tLIST) {

    if (!mQueue->empty()) {

        MemberQueueNode* curNode = (*mQueue).front(); // Get the front node of the MemberQueue
        while (curNode != NULL) {         
            curNode = (*mQueue).front(); // Get the front node again (might have changed during processing)
            if (curNode != NULL)
                mQueue->pop(); // Pop the front node from the MemberQueue
        }
    }
    
    PrintSuccess("EXIT"); // Print a success message for EXIT
    return false; // Return false to indicate the program should exit
}