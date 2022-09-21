#include "Bank.h"

bool Bank::checkPIN (string test) {
    return (PIN == test) ? 1: 0;
}

bool Bank::checkUser (string test_id) {
    return (user == test_id) ? 1: 0;
}

// ------------------------------------   
bool Bank::isNumber(string s)
{
    std::size_t char_pos(0);

    // skip the whilespaces
    char_pos = s.find_first_not_of(' ');
    if (char_pos == s.size()) return false;

    // check the significand
    if (s[char_pos] == '+' || s[char_pos] == '-') ++char_pos; // skip the sign if exist

    int n_nm, n_pt;
    for (n_nm = 0, n_pt = 0; std::isdigit(s[char_pos]) || s[char_pos] == '.'; ++char_pos) {
        s[char_pos] == '.' ? ++n_pt : ++n_nm;
    }
    if (n_pt>1 || n_nm<1) // no more than one point, at least one digit
        return false;

    // skip the trailing whitespaces
    while (s[char_pos] == ' ') {
        ++ char_pos;
    }

    return char_pos == s.size();  // must reach the ending 0 of the string
}

string Bank::time_stamp (int index) {
    
    time_t now =time(0);

    //convert now to string
    char* dt= ctime(&now);
    tm *ltm = localtime(&now);

    int DAY = ltm->tm_mday;
    int MONTH = 1+ ltm->tm_mon;
    int YEAR = 1900 + ltm->tm_year;
    int HOUR =  ltm->tm_hour;         //5+ ltm->tm_hour;
    int MINUTES = ltm->tm_min;     //30 + ltm->tm_min;

    string stamp = to_string(DAY)+"/"+to_string(MONTH)+"/"+to_string(YEAR)+" "+to_string(HOUR)+":"+to_string(MINUTES);

    return stamp;
}

void Bank::getBalance() {
    cout<<"======= Balance Engquiry ============\n"<<endl;
    cout<<"Your balance is "<< balance <<"." << endl;
    cout<<"\n====== End of Balance Engquiry ==========\n"<<endl;
}

void Bank::Deposit () {

        cout<<"======= Deposits =============\n"<<endl;

        string input;
        cout<<"Enter the amount you wish to deposit: "<<endl;
        cin>>input;

        if (isNumber (input)) {   
        balance += stof(input);

        userData << time_stamp(1) <<setw(15)<<"Depositted"<< setw(20)<<input<< setw(20)<<balance<<endl;

        cout<<"Transaction successful! "<< input<<" depositted."<<endl;
        cout<<"Your new balance is: "<<this->balance<<endl;
        cout<<"\n======= End of Deposit Transaction ============="<<endl;
        }

        else cout<<"Error! Invalid amount entered!"<<endl;

}

void Bank::Withdraw () {

        string output;
        cout<<"======= Withdrawals ============="<<endl;
        cout<<"Available funds: "<<this->balance<<endl;
        cout<<"\nEnter the amount you wish to withdraw: "<<endl;
        cin>>output;

        if (!isNumber (output)) { 
            cout<<"Error! Invalid amount entered!\n"<<endl;  
        }

        else {
            if (balance - stof(output) >= 0) {
                balance -= stof(output);

                userData << time_stamp(1) <<setw(15)<<"Withdrawn"<< setw(20)<<output<< setw(20)<<balance<<endl;

                cout<<"Transaction successful! "<< output<<" deposited."<<endl;
                cout<<"Your new balance is: "<<this->balance<<endl;
                cout<<"======= End of Withdrawals =============\n"<<endl;
            }

            else {  cout<< "Insufficient balance to complete transaction."<<endl; 
                cout<<"======= End of Withdrawals =============\n"<<endl;
            }
        }  
}

void Bank::printStatement() {

    string t_instant = time_stamp(1);
    string state_name = t_instant  + "_Bank Statement.txt";
    
    cout<<"======= Mini statement =============\n"<<endl;
    cout<<"Your bankstatement as of "<<t_instant<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<< "Time" <<setw(15)<<"Transaction"<< setw(20)<<"Amount"<< setw(20)<<"Balance"<<endl;
    cout<<"------------------------------------------------------------"<<endl;

    string line;
    userData.seekg(0, ios::beg);    //check if really goes back to start
    while (getline(userData, line)) {
        cout<<line<<endl;
    }

    cout<<"======= End of Mini statement =============\n"<<endl;
        
    }

Bank::Bank ( string user_id) {

    int i=3;
    while (i> 0) {

        if (checkUser(user_id)) {

            cout<<"Enter Pin for "<<user_id<< ": "<<endl;
            string test_pin;
            cin>>test_pin;

            if (checkPIN(test_pin)) {
                userData.open(filename, ios::in | ios::app);

                if (userData.is_open()) {
                    string in_line, temp;

                    while (getline(userData, in_line)) {
                        temp = in_line;
                    }
                    
                    if (Bank::isNumber(temp.substr(66, 5)))  balance = stof(temp.substr(66, 5));
                    else balance = 0;

                    cout<<"\nAccess granted. Welcome "<< user_id<<"!. \n" <<endl;
                    break;
                }
                
                else cout<<"Records Inaccessible at this moment. Try again later"<<endl;
            }

            else {i--; cout<<"User ID and PIN have no match. Number of tries left: "<<i <<endl; }
        }
        

        else {
            cout<<"Invalid user ID! Please enter a valid user ID:" <<endl;
            cin>>user_id; 
        }
    }

    if (i==0) {cout<<"Wrong details. Session ended! \n"<<endl;  exit(2);}

    }

Bank::~Bank () {
    userData.close();
    //close other files
    //encrypt files
    //close

    cout<<"Ending your session. Please collect your card! \a "<<this->user<<endl;
    cout<<"+++++++++++++ Good day from Bank United +++++++++++++"<<endl;
}