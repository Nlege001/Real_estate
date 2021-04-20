// Naol Legesse
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <unordered_map>
#include <stdio.h>
// this verison prints out all three but as one obj

using namespace std;
// git hub

class Territory {

    public:
        int territoryId;
        string type;
    
    public:
    Territory();

    Territory(int territoryId, string type){
        this -> territoryId = territoryId;
        this -> type = type;
    }
    // setters:
    void setTerritoryId(int territoryId) {
        this -> territoryId = territoryId;
    }
    void setType(string type) {
        this -> type = type;
    }
    // getters:
    int getTerritoryId() {
        return territoryId;
    }
    string getType() {
        return type;
    }

    // function to check if territory is premium or normal - 0 they compare equal
    bool isTerritoryPremium(string type){
        string premiumStr ("PREMIUM");
        if (premiumStr.compare(type) == 0) {
            return true;
        } else {
            return false;
        }
    }

}; // end of Territory class


    
ostream & operator<<(ostream &os, const Territory& t) {
    os << " territoryId: " << t.territoryId << " type: " << t.type << endl;
    return os;
}

map<int, Territory *> mapTerritories;
vector<int> territoryIdVec;
// function that creates a vector of territories from the text file, return the vector
void loadTerritories(ifstream& file) {
    string line; 
    int territoryId;
    char comma;
    string type; 
    int i = 0;
    while(  file >> territoryId >> comma >> type) {
        Territory * t = new Territory(territoryId, type);
        mapTerritories.insert(pair<int ,Territory *> (i, t));
        territoryIdVec.push_back(territoryId);
        i++;
    }

    for (auto i: territoryIdVec) {
        cout << (i) << endl;
    }
}
    
class Transaction {
    
    public:
        int trxId; // transaction id
        int saleRepId;
        int clientId;
        int trxType; // transaction type
        int amount;

   Transaction();

    Transaction(int trxId, int saleRepId, int clientId, int trxType, int amount) {
        this -> trxId = trxId;
        this -> saleRepId = saleRepId;
        this -> clientId = clientId;
        this -> trxType = trxType;
        this -> amount = amount;
    }

    // setters
    void setTrxId() {
        this -> trxId = trxId;
    }
    void setSaleRepId() {
        this -> saleRepId = saleRepId;
    }
    void setClientId() {
        this -> clientId = clientId;
    }
    void setTrxType() { 
        this -> trxType = trxType;
    }
    void setAmount() {
        this -> amount = amount;
    }
    // getters 
    int getTrxId() {
        return trxId;
    }
    int getSaleRepId() {
        return saleRepId;
    }
    int getClientId() {
        return clientId;
    }
    // get transaction type 
    int getTrxType() { 
        return trxType;
    }
    int getAmount() {
        return amount;
    }
}; // end of Transaction class


class Client : public Transaction {

    public:
        Client(int clientId, int amount);

}; // end of Client class
// should it be const?
ostream & operator<<(ostream &os, Transaction& t) {
    os  << t.getTrxId() << ", " << t.getSaleRepId() << ", " << t.getClientId() << ", " << t.getTrxType() << ", " << t.getAmount() << endl;
    return os;
}

map<int, Transaction *> mapTransaction;
vector<int> typeVec;  // test
vector<double> amountVec; // test
vector<int> clientIdVec; // test
void loadTransactions(ifstream& file) {
    // declare variables for Territory
    int trxId1, saleRepId1, clientId1, trxType1, amount1;
    char comma, comma1, comma2, comma3;
    int i = 0;
    // while loop to store objects
    while(file >> trxId1 >> comma >> saleRepId1 >> comma1 >> clientId1 >> comma2 >> trxType1 >> comma3 >> amount1) {
        Transaction * t = new Transaction(trxId1, saleRepId1, clientId1,trxType1, amount1);
        mapTransaction.insert(pair<int, Transaction*> (i, t)); // insert object into map
        typeVec.push_back(trxType1); //test
        amountVec.push_back(amount1); //test
        clientIdVec.push_back(clientId1); // test
        i++; 
    }



} // end of loadTransaction

class SalesRep {

    private:
        int saleRepId;
        int territoryId;
        int amount;
        // variable to store points - for each transaction sale salerep are awared points 
        int points; 
    
    public:
        SalesRep(int saleRepId, int territoryId, int amount) {
            this -> saleRepId = saleRepId;
            this -> territoryId = territoryId;
            this -> amount = amount;
        }

        // getters
        int getSaleRepId() {
            return saleRepId;
        }
        int getTerritoryId() {
            return territoryId;
        }
        int getAmount() {
            return amount;
        }

}; // end of SalesRep class


// should it be const?
ostream & operator<<(ostream &os, SalesRep& sr) {
    os  << sr.getSaleRepId() << ", " << sr.getTerritoryId() << ", " << sr.getAmount() << endl;
    return os;
}

map<int, SalesRep *> mapSaleReps;

void loadSaleReps(ifstream& file) {
    // declare variables for Territory
    int saleRepId, territoryId, amount;
    char comma, comma1;
    // while loop to store objects
    SalesRep * sr;
    int i = 0;
    while(file >> saleRepId >> comma >> territoryId >> comma1 >> amount) {
        // assign values to variable
        sr = new SalesRep(saleRepId, territoryId, amount);
        mapSaleReps.insert(pair<int, SalesRep*> (i, sr)); // insert object into map   
        i++;
    }
    
    map<int, SalesRep*>::iterator it = mapSaleReps.begin();
    while(it != mapSaleReps.end()) {
        int num = it->first;
        SalesRep * saleR = it -> second;
        cout << num << " : " << *saleR << endl;
        it++;
    }
} // end of loadSaleReps


vector<double> clientsVec; // will store clients' amount
vector<double> territoryAmountVec; 
void calcTransaction(vector<int> type, vector<double> amount) {
    // iterate through vectors and calculate the amount depending on type
    double territoryAmount = 0, saleRepAmount = 0, clientsAmount = 0;
    
    for (int i; i< amountVec.size(); i++) {
        if ((type[i] == 1) || (type[i] == 2) || type[i] == 6) {
            territoryAmount = amount[i] * 1.00; // calcualte territory
            saleRepAmount = amount[i] * 1.10; // calculate for salerep
            clientsAmount = amount[i] * 1; // calculate for client
            clientsVec.push_back(clientsAmount);
            territoryAmountVec.push_back(territoryAmount);
        } else if ( type[i] == 3) {
            territoryAmount = amount[i] * 1; // calcualte territory
            saleRepAmount = amount[i] * 1; // calculate for salerep
            clientsAmount = amount[i] * 1; // calculate for client
            clientsVec.push_back(clientsAmount);
            territoryAmountVec.push_back(territoryAmount);
        } else if (type[i] == 4) {
            territoryAmount = amount[i] * 1; // calcualte territory
            saleRepAmount = amount[i] * 1.25; // calculate for salerep
            clientsAmount = amount[i] * 1; // calculate for client
            clientsVec.push_back(clientsAmount);
            territoryAmountVec.push_back(territoryAmount);
        } else if ( type[i] == 5) {
            territoryAmount = amount[i] * 1; // calcualte territory
            saleRepAmount = amount[i] * 0; // calculate for salerep
            clientsAmount = amount[i] * 0; // calculate for client
            clientsVec.push_back(clientsAmount);
            territoryAmountVec.push_back(territoryAmount);
        } else if ( type[i] == 7) {
            territoryAmount = amount[i] * 0; // calcualte territory
            saleRepAmount = amount[i] * .75; // calculate for salerep
            clientsAmount = amount[i] * 0; // calculate for client
            clientsVec.push_back(clientsAmount);
            territoryAmountVec.push_back(territoryAmount);
        }
    }  

    /*
     for (int i = 0; i < territoryAmountVec.size(); i++) {
        cout << "territory amount: " << territoryAmountVec[i] << endl;
    }
   */
}



// direct output to client_output (clientID , client amount)
void clientOutput(vector<int> ci, vector<double> ca) {
    for (int i = 0; i < ci.size(); i++) {
        cout << " client id is:" << ci[i] << " client amount is: " << ca[i] << endl;
    }

}
// TEST 
// territory id and territory amount 
void territoryOutput(vector<int> ti, vector<double> ta) {
    
}


// END TEST
int main () {
    freopen ("client_output.txt","w",stdout);
    ifstream territoryFile("territory.txt");
    ifstream saleRepFile("salerep.txt");
    ifstream trxFile("transaction.txt");
    cout << "load territories :" << endl;
    loadTerritories(territoryFile);
    loadTransactions(trxFile);
    //for (auto i : amountVec)
    //cout << (i) << endl;
    //loadSaleReps(saleRepFile);
    calcTransaction(typeVec, amountVec);
    cout << "client output: " << endl;
    clientOutput(clientIdVec, clientsVec); 

    fclose(stdout);
    return 0;
}