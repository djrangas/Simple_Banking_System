#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Account {
    int accountNumber;
    string accountHolder;
    float balance;
};

// Function prototypes
void createAccount();
void deposit();
void withdraw();
void checkBalance();
int getLastAccountNumber();

int main() {
    system("clear");
    int choice;
    do {
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void createAccount() {
    Account acc;
    acc.accountNumber = getLastAccountNumber() + 1;
    cout << "Enter account holder's name: ";
    cin.ignore();
    getline(cin, acc.accountHolder);
    acc.balance = 0.0;

    ofstream outFile("accounts.txt", ios::app);
    if (outFile) {
        outFile << acc.accountNumber << " " << acc.accountHolder << " " << acc.balance << "\n";
        cout << "Account created successfully!\n";
        cout << "Your account number is: " << acc.accountNumber << "\n";
    } else {
        cout << "Error opening file!\n";
    }
    outFile.close();
}

void deposit() {
    int accNumber;
    float amount;
    cout << "Enter account number: ";
    cin >> accNumber;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");
    if (!inFile || !tempFile) {
        cout << "Error opening file!\n";
        return;
    }

    Account acc;
    bool found = false;
    while (inFile >> acc.accountNumber >> ws) {
        getline(inFile, acc.accountHolder, ' ');
        inFile >> acc.balance;
        if (acc.accountNumber == accNumber) {
            found = true;
            acc.balance += amount;
            cout << "Deposited " << amount << " successfully.\n";
        }
        tempFile << acc.accountNumber << " " << acc.accountHolder << " " << acc.balance << "\n";
    }

    inFile.close();
    tempFile.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        cout << "Account number not found!\n";
    }
}

void withdraw() {
    int accNumber;
    float amount;
    cout << "Enter account number: ";
    cin >> accNumber;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");
    if (!inFile || !tempFile) {
        cout << "Error opening file!\n";
        return;
    }

    Account acc;
    bool found = false;
    while (inFile >> acc.accountNumber >> ws) {
        getline(inFile, acc.accountHolder, ' ');
        inFile >> acc.balance;
        if (acc.accountNumber == accNumber) {
            found = true;
            if (acc.balance >= amount) {
                acc.balance -= amount;
                cout << "Withdrawn " << amount << " successfully.\n";
            } else {
                cout << "Insufficient balance!\n";
            }
        }
        tempFile << acc.accountNumber << " " << acc.accountHolder << " " << acc.balance << "\n";
    }

    inFile.close();
    tempFile.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        cout << "Account number not found!\n";
    }
}

void checkBalance() {
    int accNumber;
    cout << "Enter account number: ";
    cin >> accNumber;

    ifstream inFile("accounts.txt");
    if (!inFile) {
        cout << "Error opening file!\n";
        return;
    }

    Account acc;
    bool found = false;
    while (inFile >> acc.accountNumber >> ws) {
        getline(inFile, acc.accountHolder, ' ');
        inFile >> acc.balance;
        if (acc.accountNumber == accNumber) {
            found = true;
            cout << "Account Holder: " << acc.accountHolder << "\n";
            cout << "Balance: " << acc.balance << "\n";
        }
    }

    inFile.close();

    if (!found) {
        cout << "Account number not found!\n";
    }
}

int getLastAccountNumber() {
    ifstream inFile("accounts.txt");
    if (!inFile) return 0;

    Account acc;
    int lastAccNumber = 0;
    while (inFile >> acc.accountNumber >> ws) {
        getline(inFile, acc.accountHolder, ' ');
        inFile >> acc.balance;
        lastAccNumber = acc.accountNumber;
    }

    inFile.close();
    return lastAccNumber;
}
