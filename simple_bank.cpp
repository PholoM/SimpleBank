#include <iostream>
#include <string>
#include <cstring>


using namespace std;


class Bank {
    
    public:
    string ID;



    private:
    float balance = 100;
    string user = "pholo";
    string PIN = "4444";

    bool checkPIN (string test) {
         return (PIN == test) ? 1: 0;
    }

    bool checkUser (string test_id) {
        return (user == test_id) ? 1: 0;
    }

// ------------------------------------   
bool isNumber(string s)
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
//-----------------------------------------------------------------------------
    

    public:

    void getBalance() {
        cout<<"======= Balance Engquiry ============\n"<<endl;

        cout<<"Your balance is "<< balance <<"." << endl;
        cout<<"\n====== End of Balance Engquiry ==========\n"<<endl;

    }


    void Deposit () {

        cout<<"======= Deposits =============\n"<<endl;

        string input;
        cout<<"Enter the amount you wish to deposit: "<<endl;
        cin>>input;

        if (isNumber (input)) {   
        balance += stof(input);
        cout<<"Transaction successful! "<< input<<" depositted."<<endl;
        cout<<"Your new balance is: "<<this->balance<<endl;
        cout<<"\n======= End of Deposit Transaction ============="<<endl;
        }

        else cout<<"Error! Invalid amount entered!"<<endl;

    }

    void Withdraw () {
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
            cout<<"Transaction successful! "<< output<<" deposited."<<endl;
            cout<<"Your new balance is: "<<this->balance<<endl;
            cout<<"======= End of Withdrawals =============\n"<<endl;

            }

            else {  cout<< "Insufficient balance to complete transaction."<<endl; 
                cout<<"======= End of Withdrawals =============\n"<<endl;
            }
        }

        
    }

   

    Bank ( string user_id) {

//      ===================================================================//
        int i=3;
        while (i> 0) {

            if (checkUser(user_id)) {

                cout<<"Enter Pin for "<<user_id<< ": "<<endl;
                string test_pin;
                cin>>test_pin;

                if (checkPIN(test_pin)) {
                    cout<<"\nAccess granted. Welcome "<< user_id<<"!. \n" <<endl;
                    break;
                    //ask what they wanna do or call menu
                    
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

    ~Bank () {
        cout<<"Ending your session. Please collect your card! \a "<<this->user<<endl;
        cout<<"+++++++++++++ Good day from Bank United +++++++++++++"<<endl;
    }


};


int main () {

    cout<<"\n******************* Log in  ****************"<<endl;

    string user;
    cout<<"Enter your user ID: "<<endl;
    cin>>user;
    //cout<<endl;

    Bank mybank (user);

//function pointers
    void (Bank::* func_ptr[3]) ();  //pointer to functions
    func_ptr[0] = &Bank::getBalance;
    func_ptr[1] = &Bank::Withdraw;
    func_ptr[2] = &Bank::Deposit;


    while (1) {
                
        cout<<"============ MENU ================="<<endl;
        cout<<"CHOOSE FROM THE MENU TO PERFORM TASK"<<endl;
        cout<<  "1   - check balance     \n"
                "2   - Withdraw funds    \n"
                "3   - Deposit funds     \n"
                "4   - finish            \n" <<endl;

        int selection;
        cin>>selection;
    
        if ((selection < 4) && (selection >=1)) (mybank.*func_ptr[selection -1]) ();
        else if (selection == 4) break;
        else cout<<"Choose a valid mode between 1 and 4!\n"<<endl;
    }

      
    //cout<<"\n*********** ## End of Program ##  **************"<<endl;

    return 0;
}

