// LEKGOTHOANE BANK - Command Line Banking System

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const int MAX_USERS = 3;
const int MAX_PIN_ATTEMPTS = 3;

// Parallel arrays
string name[MAX_USERS] = {"Kamogelo", "Thapelo", "Leruwo"};
int accountNums[MAX_USERS] = {1001, 1002, 1003};
int pins[MAX_USERS] = {2468, 1357, 3456};
double balances[MAX_USERS] = {5000.00, 2500.50, 10000.00};

//---------------------------------------------------
// Helper Functions
//---------------------------------------------------

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool readInt(int &value)
{
    if (cin >> value)
        return true;

    clearInput();
    return false;
}

bool readDouble(double &value)
{
    if (cin >> value)
        return true;

    clearInput();
    return false;
}

int findAccount(int accNum)
{
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (accountNums[i] == accNum)
            return i;
    }

    return -1;
}

//---------------------------------------------------
// Login Function
//---------------------------------------------------

int login()
{
    int accNum;

    cout << "\nEnter account number: ";

    if (!readInt(accNum))
    {
        cout << "Invalid input. Account number must contain digits only.\n";
        return -1;
    }

    int index = findAccount(accNum);

    if (index == -1)
    {
        cout << "Account not found.\n";
        return -1;
    }

    for (int attempt = 1; attempt <= MAX_PIN_ATTEMPTS; attempt++)
    {
        int pin;

        cout << "Enter PIN: ";

        if (readInt(pin) && pin == pins[index])
        {
            cout << "\nWelcome, " << name[index] << "!\n";
            return index;
        }

        cout << "Wrong PIN. Attempts left: "
             << (MAX_PIN_ATTEMPTS - attempt) << "\n";
    }

    cout << "Too many failed attempts. Access denied.\n";
    return -1;
}

//---------------------------------------------------
// Menu
//---------------------------------------------------

void displayMenu()
{
    cout << "\n===== LEKGOTHOANE BANK =====\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

//---------------------------------------------------
// Deposit
//---------------------------------------------------

void deposit(int user)
{
    double amount;

    cout << "Enter amount to deposit: R";

    if (!readDouble(amount))
    {
        cout << "Invalid input. Please enter a number.\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Deposit amount must be greater than R0.00\n";
        return;
    }

    balances[user] += amount;

    cout << "Deposit successful.\n";
    cout << "New balance: R" << balances[user] << "\n";
}

//---------------------------------------------------
// Withdraw
//---------------------------------------------------

void withdraw(int user)
{
    double amount;

    cout << "Enter amount to withdraw: R";

    if (!readDouble(amount))
    {
        cout << "Invalid input. Please enter a number.\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Withdrawal amount must be greater than R0.00\n";
        return;
    }

    if (amount > balances[user])
    {
        cout << "Insufficient funds.\n";
        cout << "Current balance: R" << balances[user] << "\n";
        return;
    }

    balances[user] -= amount;

    cout << "Withdrawal successful.\n";
    cout << "New balance: R" << balances[user] << "\n";
}

//---------------------------------------------------
// Send Cash
//---------------------------------------------------

void sendCash(int user)
{
    int recipientAcc;
    double amount;

    cout << "\nEnter recipient account number: ";

    if (!readInt(recipientAcc))
    {
        cout << "Invalid account number.\n";
        return;
    }

    int recipient = findAccount(recipientAcc);

    if (recipient == -1)
    {
        cout << "Recipient account not found.\n";
        return;
    }

    if (recipient == user)
    {
        cout << "You cannot transfer money to your own account.\n";
        return;
    }

    cout << "Recipient Name: " << name[recipient] << "\n";

    cout << "Enter amount to send: R";

    if (!readDouble(amount))
    {
        cout << "Invalid amount entered.\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be greater than R0.00\n";
        return;
    }

    if (amount > balances[user])
    {
        cout << "Insufficient funds.\n";
        cout << "Current balance: R" << balances[user] << "\n";
        return;
    }

    balances[user] -= amount;
    balances[recipient] += amount;

    cout << "\nTransfer successful!\n";
    cout << "R" << amount << " sent to "
         << name[recipient] << "\n";

    cout << "Remaining balance: R"
         << balances[user] << "\n";
}

//---------------------------------------------------
// Check Balance
//---------------------------------------------------

void checkBalance(int user)
{
    cout << "\n===== ACCOUNT DETAILS =====\n";
    cout << "Account Holder : " << name[user] << "\n";
    cout << "Account Number : " << accountNums[user] << "\n";
    cout << "Current Balance: R" << balances[user] << "\n";
}

//---------------------------------------------------
// Main Program
//---------------------------------------------------

int main()
{
    cout << fixed << setprecision(2);

    int user = -1;

    while (user == -1)
    {
        cout << "===== Welcome to LEKGOTHOANE BANK =====\n";

        user = login();

        if (user == -1)
        {
            char again;

            cout << "Try again? (y/n): ";
            cin >> again;

            clearInput();

            if (again != 'y' && again != 'Y')
            {
                cout << "Goodbye!\n";
                return 0;
            }
        }
    }

    int choice = 0;

    while (choice != 5)
    {
        displayMenu();

        if (!readInt(choice))
        {
            cout << "Invalid choice. Enter a number from 1 to 5.\n";
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            deposit(user);
            break;

        case 2:
            withdraw(user);
            break;

        case 3:
            sendCash(user);
            break;

        case 4:
            checkBalance(user);
            break;

        case 5:
            cout << "\nThank you for banking with LEKGOTHOANE BANK.\n";
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Enter a number from 1 to 5.\n";
        }
    }

    return 0;
}
