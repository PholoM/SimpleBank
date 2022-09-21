#include <iostream>
#include <string>
#include "Bank.h"

#define N 4 //number of functions

using namespace std;

int main () {

    cout<<"\n******************* Log in  ****************"<<endl;

    string user;
    cout<<"Enter your user ID: "<<endl;
    cin>>user;
   
    Bank mybank(user);

//function pointers
    void (Bank::* func_ptr[N]) ();  //pointer to functions
    func_ptr[0] = &Bank::getBalance;
    func_ptr[1] = &Bank::Deposit;
    func_ptr[2] = &Bank::Withdraw;
    func_ptr[3] = &Bank::printStatement;
    


    while (1) {
                
        cout<<"============ MENU ================="<<endl;
        cout<<"CHOOSE FROM THE MENU TO PERFORM TASK"<<endl;
        cout<<  "1   - check balance     \n"
                "2   - Deposit funds     \n"
                "3   - Withdraw funds    \n"
                "4   - Print Statement   \n"
       <<(N+1)<< "   - finish            \n" <<endl;

        int selection;
        cin>>selection;
    
        if ((selection <= N) && (selection >=1)) (mybank.*func_ptr[selection -1]) ();
        else if (selection == (N+1)) break;
        else cout<<"Choose a valid mode between 1 and "<<N<<"!\n"<<endl;
    }

      

    return 0;
}

