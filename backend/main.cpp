#include <iostream>
using namespace std;
void exitProgram(){
    cout << "Thank you for using our Tracker!" << endl << "See you soon!";
}
void income(){
    double balance = 0.00;
    cout << "Your current balance is " << balance << " $" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1: View Income History" << endl << "2: Add Income" << endl;
    cout << "__________________________________________" << endl;
    cout << "Enter Action(0 to exit): ";
    int act1;
    cin >> act1;
    if(act1 ==0){
        return;
    }
    else if(act1 == 1){

    }
}
int main() {
    int action;
    do{
        cout << "*************** Student Expense Tracker *************** " << endl;
    cout << "Welcome User!" << endl;
    cout << "What would you like to do today?" << endl;
    cout << "1: Check Income" << endl << "2: Check Expenses" << endl;
    cout << "__________________________________________" << endl;
    cout << "Enter Action(0 to exit): ";
    cin >> action;
        if(action == 0){
            exitProgram();
            return 0;
        }
        else if(action == 1){
            income();
        }
    }while(action != 0);
    
    return 0;
}
