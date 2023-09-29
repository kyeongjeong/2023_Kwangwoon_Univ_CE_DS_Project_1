#include "Manager.h"

Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    MemberQueue mQueue;
    NameBST nBST;
    TermsLIST tLIST;

    // Run command
    while(!fcmd.eof()) {
        
        string cmd;
        fcmd >> cmd;

        if(cmd == "LOAD") {          
            if(!(LOAD(&mQueue)))
                return;
        }
        else if(cmd == "ADD") {
            if(!ADD(&mQueue))
                return;
        }
        else if(cmd == "QPOP") {
            if(!QPOP(&mQueue, &nBST, &tLIST)) 
                return;
        }
        else if(cmd == "SEARCH") {
            if(!SEARCH(&nBST)) 
                return;
        }
        else if(cmd == "PRINT") {
            if(!PRINT(&nBST, &tLIST))
                return;
        }
        else if(cmd == "DELETE") {
            if(!DELETE(&nBST, &tLIST))
                return;
        }
        else if(cmd == "EXIT") {
            EXIT(&mQueue, &nBST, &tLIST);
            return;
        }
        else {
            PrintErrorCode(1000);
        }
    } 

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
    if(!fdata) {
        PrintErrorCode(100);
    }

    string mName, infoDate, termsType;
    int mAge;
    if(!(*mQueue).empty()) {
        PrintErrorCode(100);
    }

    while(!fdata.eof()) {

        fdata >> mName >> mAge >> infoDate >> termsType;
        if(!(*mQueue).full()) 
            (*mQueue).push(mName, mAge, infoDate, termsType);
        else
            return false;
    }

    MemberQueueNode* curNode = (*mQueue).front();
    
    flog << "===== LOAD =====" << endl; 
    while(curNode != NULL) {

        flog << curNode->getMName() << "/" << curNode->getMAge() << "/" << curNode->getInfoDate() << "/" << curNode->getTermsType() << endl;
        curNode = curNode->getNext();
    }
    flog << "===============" << endl << endl;

    return true;
}

bool Manager::ADD(MemberQueue* mQueue) {
    
    int mAge;
    string mName, infoDate, termsType;
    string mData;

    getline(fcmd, mData);
    stringstream dataStream(mData);
    string token;

    for (int i = 0; i < 4; ++i) {

        dataStream >> token;
        if (!dataStream) {
            PrintErrorCode(200); // 각 필드가 누락된 경우 오류 코드 출력
            return true;
        }

        switch (i) {
            case 0:
                mName = token;
                break;
            case 1:
                try {
                    mAge = stoi(token);
                } 
                catch (const invalid_argument&) {
                    PrintErrorCode(200);
                    return true;
                }
                break;
            case 2:
                infoDate = token;
                break;
            case 3:
                termsType = token;
                break;
        }
    }

    if(!(*mQueue).full()) 
        (*mQueue).push(mName, mAge, infoDate, termsType); 
    else
        return false;

    flog << "===== ADD =====" << endl; 
    flog << mName << "/" << mAge << "/" << infoDate << "/" << termsType << endl;
    flog << "===============" << endl << endl;

    return true;
}

bool Manager::QPOP(MemberQueue* mQueue, NameBST* nBST, TermsLIST* tLIST) {

    if((*mQueue).empty()) {
        PrintErrorCode(300);
        return false;
    }

    MemberQueueNode* curNode = (*mQueue).front();
    while(curNode != NULL) {
        
        curNode = (*mQueue).front();
        if(curNode != NULL) {
            MemberQueueNode popNode = mQueue->pop();
            string expireDate = calculateExpireDate(popNode.getInfoDate(), popNode.getTermsType());
            tLIST->insertListNode(popNode.getMName(), popNode.getMAge(), popNode.getInfoDate(), expireDate, popNode.getTermsType());
            nBST->insertBSTNode(popNode.getMName(), popNode.getMAge(), popNode.getInfoDate(), expireDate, popNode.getTermsType());
        }
    }
    PrintSuccess("QPOP");
    return true;
}

string Manager::calculateExpireDate(string infoDate, string termsType) {

	int year, month, day;
    sscanf(infoDate.c_str(), "%d-%d-%d", &year, &month, &day);

	int monthsToAdd = 0;
    if (termsType == "A") {
        monthsToAdd = 6;
    } else if (termsType == "B") {
        monthsToAdd = 12;
    } else if (termsType == "C") {
        monthsToAdd = 24;
    } else if (termsType == "D") {
        monthsToAdd = 36;
    }

	year += (month + monthsToAdd - 1) / 12;
    month = (month + monthsToAdd - 1) % 12 + 1;

	string expireDate = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-" + (day < 10 ? "0" : "") + to_string(day); 
	return expireDate;
}

bool Manager::SEARCH(NameBST* nBST) {

    string mName;
    fcmd >> mName;

    NameBSTNode* curNode = nBST->searchBSTNode(mName);
    if(curNode == NULL) {
        PrintErrorCode(400);
        return true;
    }
    string searchMemberInfo = curNode->getMName() + "/" + to_string(curNode->getMAge()) + "/" + curNode->getInfoDate() + "/" + curNode->getExpireDate();
    flog << "===== SEARCH =====" << endl; 
    flog << searchMemberInfo << endl;
    flog << "===============" << endl << endl;
    return true;
}

bool Manager::PRINT(NameBST* nBST, TermsLIST* tLIST) {

    string argType;
    fcmd >> argType;

    if(argType == "NAME") {

        if(nBST->getRoot() == NULL) {
            PrintErrorCode(500);
            return true;
        }
        flog << "===== PRINT =====" << endl;
        flog << "Name_BST" << endl;
        nBST->printBSTNode(nBST->getRoot(), &flog);
        flog << "===============" << endl << endl;
    }
    else if((argType == "A") || (argType == "B") || (argType == "C") || (argType == "D")) {

        if((tLIST->getHead() == NULL) || (tLIST->searchListNode(argType) == NULL)) {
            PrintErrorCode(500);
            return true;
        }
        flog << "===== PRINT =====" << endl;
        flog << "Terms_BST " << argType << endl;

        TermsListNode* tListNode = tLIST->searchListNode(argType);
        TermsBST* tBST = tListNode->getTBST();
        tBST->printBSTNode(tBST->getRoot(), &flog);

        flog << "===============" << endl << endl;
    }
    else {
        PrintErrorCode(500);
        return true;
    }
    return true;
}

bool Manager::DELETE(NameBST* nBST, TermsLIST* tLIST) {

    if((nBST->getRoot() == NULL) || (tLIST->getHead() == NULL)) {
        PrintErrorCode(600);
        return true;
    }

    string argType, arg;
    fcmd >> argType >> arg;

    if(argType == "NAME") {
        
        if(!nBST->deleteBSTNode(arg)) {
            PrintErrorCode(600);
            return true;
        }
        if(!tLIST->deleteListNode(argType, arg)) {
            PrintErrorCode(600);
            return true;
        }
    }
    else if(argType == "DATE") {

        if(!nBST->traversalBSTTerms(nBST->getRoot(), arg, false)) {
            PrintErrorCode(600);
            return true;
        }
        if(!tLIST->deleteListNode(argType, arg)) {
            PrintErrorCode(600);
            return true;
        }
    }
    else {
        PrintErrorCode(600);
        return true;
    }

    PrintSuccess("DELETE");
    return true;
}

void Manager::EXIT(MemberQueue* mQueue, NameBST* nBST, TermsLIST* tLIST) {

    ;
}