#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ctime>

#define N 4 //number of functions


using namespace std;

/*
Functions
1. CheckBalance
2. Withdraw
3. Deposit
4. Mini statement


*/

class Bank {
    
    public:
    string ID;

    private:
    float balance;
    string user = "pholo";
    string PIN = "4444";
    string filename = user + ".txt";  
    fstream userData;

    bool checkPIN (string test); 

    bool checkUser (string test_id);

    bool isNumber(string s);

    public:
    string time_stamp (int index);

    void getBalance();

    void Deposit ();

    void Withdraw (); 

    void printStatement();

    Bank ( string user_id); 

    ~Bank (); 

};

#endif