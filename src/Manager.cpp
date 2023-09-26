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

        }
        else if(cmd == "PRINT") {

        }
        else if(cmd == "DELETE") {

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

// QPOP
bool Manager::QPOP(MemberQueue* mQueue, NameBST* nBST, TermsLIST* tLIST) {

    if((*mQueue).empty()) {
        PrintErrorCode(300);
        return false;
    }

    MemberQueueNode* curNode;
    while(curNode != NULL) {
        
        curNode = (*mQueue).front();
        if(curNode != NULL) {
            MemberQueueNode popNode = mQueue->pop();
            string expireDate = calculateExpireDate(popNode.getInfoDate(), popNode.getTermsType());
            tLIST->insertListNode(popNode.getMName(), popNode.getMAge(), popNode.getInfoDate(), expireDate, popNode.getTermsType());
            nBST->insertBSTNode();
        }
    }

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

// SEARCH

// PRINT

// DELETE