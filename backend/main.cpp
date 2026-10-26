#include <iostream>
#include <vector>
using namespace std;

vector<double> incomes;
vector<double> expenses;
double balance = 0.00;

void exitProgram()
{
    cout << "Thank you for using our Tracker!" << endl
         << "See you soon!";
}
void expense()
{
    int act1 = -1;
    do
    {
        cout << "Your current balance is " << balance << " $" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1: View Expense History" << endl
             << "2: Add Expense" << endl;
        cout << "__________________________________________" << endl;
        cout << "Enter Action (0 to return): ";
        cin >> act1;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input" << endl;
            act1 = -1;
            continue;
        }
        if (act1 == 1)
        {
            if (expenses.empty())
            {
                cout << "No expense history yet." << endl;
            }
            else
            {
                cout << "Expense History:" << endl;
                double totalExpenses = 0.00;
                for (int i = 0; i < expenses.size(); i++)
                {
                    cout << i + 1 << ": " << expenses[i] << " $" << endl;
                    totalExpenses += expenses[i];
                }
                cout << "Total expenses: " << totalExpenses << " $" << endl;
            }
        }
        else if (act1 == 2)
        {
            double amount;
            cout << "Enter expense amount: ";
            cin >> amount;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input" << endl;
            }
            else if (amount <= 0)
            {
                cout << "Expense amount must be greater than 0." << endl;
            }
            else if (amount > balance)
            {
                cout << "You do not have enough money for this expense." << endl;
            }
            else
            {
                expenses.push_back(amount);
                balance -= amount;
                cout << "Expense added successfully." << endl;
            }
        }
        else if (act1 != 0)
        {
            cout << "Invalid action. Please try again." << endl;
        }
    } while (act1 != 0);
}
void income()
{
    int act1 = -1;
    do
    {
        cout << "Your current balance is " << balance << " $" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1: View Income History" << endl
             << "2: Add Income" << endl;
        cout << "__________________________________________" << endl;
        cout << "Enter Action (0 to return): ";
        cin >> act1;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input" << endl;
            act1 = -1;
            continue;
        }
        if (act1 == 1)
        {
            if (incomes.empty())
            {
                cout << "No income history yet." << endl;
            }
            cout << "Income History:" << endl;
            double totalIncome = 0.00;
            for (int i = 0; i < incomes.size(); i++)
            {
                cout << i + 1 << ": " << incomes[i] << " $" << endl;
                totalIncome += incomes[i];
            }
            cout << "Total income: " << totalIncome << " $" << endl;
        }
        else if (act1 == 2)
        {
            double amount;
            cout << "Enter income amount: ";
            cin >> amount;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input" << endl;
            }
            else if (amount > 0)
            {
                incomes.push_back(amount);
                balance += amount;
                cout << "Income added successfully." << endl;
            }
            else
            {
                cout << "Income amount must be greater than 0." << endl;
            }
        }
        else if (act1 != 0)
        {
            cout << "Invalid action. Please try again." << endl;
        }
    } while (act1 != 0);
}

int main()
{
    int action = -1;
    do
    {
        cout << "*************** Student Expense Tracker *************** " << endl;
        cout << "Welcome User!" << endl;
        cout << "Your current balance is: " << balance << "$" << endl;
        cout << "What would you like to do today?" << endl;
        cout << "1: Check Income" << endl
             << "2: Check Expenses" << endl;
        cout << "__________________________________________" << endl;
        cout << "Enter Action(0 to exit): ";
        cin >> action;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input" << endl;
            action = -1;
            continue;
        }
        if (action == 0)
        {
            exitProgram();
            return 0;
        }
        else if (action == 1)
        {
            income();
        }
        else if (action == 2)
        {
            expense();
        }
        else
        {
            cout << "Invalid action. Please try again." << endl;
        }
    } while (action != 0);

    return 0;
}
