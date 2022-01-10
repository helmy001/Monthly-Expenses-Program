#include<iostream>
#include<vector>
#include<map>
#include<stdlib.h>
#include<fstream>
using namespace std;

struct Wallet
{
    string name;
    int cash;
};

struct Date
{
    int day;
    int month;
    int year;
};

struct Monthly_Expenses
{
    Date buyDate;
    string name;
    string category;
    int amount;
    int price;
    Wallet wallet;
};

//Function to store date into a file (monthly expences file)
void read(vector<Monthly_Expenses>& expenses, int& Monthly_income)
{
    ifstream file;
    file.open("Monthly_Expences.txt", ios::in);

    bool firstLine = true; // a boolian to know if its the first line of the file.

    //retreving information from the file.
    while (!file.eof()) {
        Monthly_Expenses expence;       // a variable of the type monthly expences to store the date from the file into.
        if (firstLine) {
            file >> Monthly_income;
        }

        file >> expence.name >> expence.buyDate.day >> expence.buyDate.month >> expence.buyDate.year >> expence.category >> expence.amount >> expence.price >> expence.wallet.name;

        // storing the new variable in the vector;
        expenses.push_back(expence);

        // cahnging the boolian to false becasue the first line is over;
        firstLine = false;
    }

}

//Function to store date into a file (wallets file)
void read(map<string, int>& wallets)
{
    ifstream file;
    file.open("Wallets.txt", ios::in);
    wallets.clear();
    //retreving information from the file.
    Wallet wallet;
    while (file >> wallet.name >> wallet.cash) {
        // storing the new variable in the vector;
        wallets[wallet.name] = wallet.cash;
    }

}

//Function to write into the file (monthly expences file)
void write(vector<Monthly_Expenses>& expenses, int& Monthly_income) {
    ofstream file;
    file.open("Monthly_Expences.txt", ios::out);
    int cnt = 0;
    file << Monthly_income << endl;
    for (int i = 0; i < expenses.size(); i++) {
        file << expenses[i].name << endl << expenses[i].buyDate.day << endl << expenses[i].buyDate.month << endl << expenses[i].buyDate.year << endl << expenses[i].category << endl << expenses[i].amount << endl << expenses[i].price << endl << expenses[i].wallet.name;
        if (cnt < expenses.size() - 1) {
            file << endl;
        }
        cnt++;
    }
    file.close();
}
//Function to write into the file (wallets file)
void write(map<string, int>& wallets) {
    ofstream file;
    file.open("Wallets.txt", ios::out);
    int cnt = 0;
    for (auto i : wallets) {
        file << i.first << endl << i.second;
        if (cnt < wallets.size() - 1) {
            file << endl;
        }
        cnt++;
    }
    file.close();
}
void welcom_page()
{

    cout << "1- Add a wallet." << endl;
    cout << "2- Add expenses" << endl;
    cout << "3- Expences information" << endl;
    cout << "4- Wallets' information" << endl;
}
void wallet(map<string, int>& wallets, int& Monthly_income)
{
    string walletName;
    int walletCash;
    cout << "Enter wallet name!" << endl;
    cin >> walletName;
    cout << "Enter the amount of cash!" << endl;
    cin >> walletCash;
    //Checking if the current income is enough to add another wallet
    if (walletCash <= Monthly_income) {
        // Deducing the the new wallet's balance from the totoal income
        Monthly_income -= walletCash;
        wallets[walletName] = walletCash;
        system("CLS");
    }
    else {
        system("CLS");
        cout << "Your current balance is insufficient!" << endl;
    }

    welcom_page();
}
void addExpenses(vector<Monthly_Expenses>& expenses, map<string, int>& wallets)
{
    // Taking expence information and adding it to the list
    Monthly_Expenses expence;
    cout << "Enter Name:" << endl;
    cin >> expence.name;
    cout << "Enter Day:" << endl;
    cin >> expence.buyDate.day;
    cout << "Enter Month:" << endl;
    cin >> expence.buyDate.month;
    cout << "Enter Year:" << endl;
    cin >> expence.buyDate.year;
    cout << "Enter Category:" << endl;
    cin >> expence.category;
    cout << "Enter Amount:" << endl;
    cin >> expence.amount;
    cout << "Enter Total Price:" << endl;
    cin >> expence.price;
    cout << "Enter Used Wallet's Name:" << endl;
    cin >> expence.wallet.name;
    expenses.push_back(expence);

    //Finding the used wallet in the map and deducing the expence price from it
    wallets[expence.wallet.name] -= expence.price;
    system("CLS");
    welcom_page();
}
void expencesInformation(vector<Monthly_Expenses>& expenses) {
    cout << "Name" << "  " << "Category" << "  " << "Amount" << "  " << "Price" << "  " << "Wallet" << endl;
    for (int i = 1; i < expenses.size(); i++) {
        cout << expenses[i].name << "  " << expenses[i].category << "  " << expenses[i].amount << "  " << expenses[i].price << "  " << expenses[i].wallet.name << endl;
    }

}
void walletInformation(map<string, int> wallets) {
    cout << "Name" << "  " << "Balance" << endl;
    //Iterating through the map and displaying the name and balance of each wallet
    for (auto i : wallets) {
        cout << i.first << "  " << i.second << endl;
    }
}




int main() {
    map<string, int> wallets;
    vector<Monthly_Expenses> expenses;
    
    int monthly_Income;
    int choice;
    read(expenses, monthly_Income);
    read(wallets);
    if (monthly_Income == -1) {
        cout << "Welcom!" << endl;
        cout << "Enter you monthly income: " << endl;
        cin >> monthly_Income;
    }
    system("CLS");
    welcom_page();
    while (true) {
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("CLS");
            wallet(wallets, monthly_Income);
            break;
        case 2:
            system("CLS");
            addExpenses(expenses, wallets);
            break;
        case 3:
            system("CLS");
            expencesInformation(expenses);
            break;
        case 4:
            system("CLS");
            walletInformation(wallets);
            break;
        case 5:
            write(expenses, monthly_Income);
            write(wallets);
            break;
        default:
            break;
        }
    }
}