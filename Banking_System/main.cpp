#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cstdlib>

#define MIN_BALANCE 500

using namespace std; 

class InsufficientFunds {
};

class Account {
  private:
    string First_name;
    string Last_name;
    long Account_number;
    float Balance;
    static long NextAccountNumber;

  public:
    Account(){}
 
    Account(string First_name, string Last_name, float Balance) {
      NextAccountNumber++;
      Account_number = NextAccountNumber;
      this->First_name = First_name;
      this->Last_name = Last_name;
      this->Balance = Balance;
    }

    long getAccountNumber() {
      return Account_number;
    }

    string getFirst_name() {
      return First_name;
    }

    string getLast_name() {
      return Last_name;
    }

    float getBalance() {
      return Balance;
    }

    void Deposit(float amount) {
        Balance += amount;
    }

    void Withdraw(float amount) {
      if(Balance-amount < MIN_BALANCE) {
        throw InsufficientFunds();
      }
      Balance -= amount;
    }

    static void setLastAccountNumber(long Account_number) {
      NextAccountNumber = Account_number;
    }

    static long getLastAccountNumber() {
      return NextAccountNumber;
    }

    friend ofstream & operator<<(ofstream &ofs, Account &a);
    friend ifstream & operator>>(ifstream &ifs, Account &a);
    friend ostream & operator<<(ostream &os, Account &a);
};

ofstream & operator<<(ofstream &ofs,Account &a) {
    ofs<<a.Account_number<<endl;
    ofs<<a.First_name<<endl;
    ofs<<a.Last_name<<endl;
    ofs<<a.Balance<<endl;
    return ofs;
}

ifstream & operator>>(ifstream &ifs, Account &a) {
    ifs>>a.Account_number>>a.First_name>>a.Last_name>>a.Balance;
    return ifs;
}

ostream & operator<<(ostream &os, Account &a) {
    os<<"First Name : "<<a.First_name<<endl;
    os<<"Last Name : "<<a.Last_name<<endl;
    os<<"Account Number : "<<a.Account_number<<endl;
    os<<"Balance : "<<a.Balance<<endl;
    return os;
}

long Account::NextAccountNumber = 0;

class Bank {

  private:
    map <long,Account> accounts;

  public:
    Bank();
    Account OpenAccount(string First_name, string Last_name, float Balance);
    Account BalanceEnquiry(long Account_number);
    Account Deposit(long Account_number, float amount);
    Account Withdraw(long Account_number, float amount);
    void CloseAccount(long Account_number);
    void ShowAllAccount();
    ~Bank();
};

Bank::Bank() {
  Account account;
  ifstream ifs;
  ifs.open("Bank.data");
  if(!ifs) {
    cout << "Error in opening the file!!! " <<endl;
    return;
  }
  while(!ifs.eof()) {
    ifs>>account;
      accounts.insert(pair<long, Account>(account.getAccountNumber(),account));

  }
  Account::setLastAccountNumber(account.getAccountNumber());

  ifs.close();
}

Account Bank::OpenAccount(string First_name, string Last_name, float Balance) {
  ofstream outfile;
  Account account(First_name,Last_name,Balance);
    accounts.insert(pair<long, Account>(account.getAccountNumber(),account));

  outfile.open("Bank.data", ios::trunc);

  map<long,Account>::iterator itr;

    for(itr=accounts.begin(); itr!=accounts.end(); itr++) {
    outfile<<itr->second;
  }

  outfile.close();
  return account;

}

Account Bank::BalanceEnquiry(long accountNumber) {
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    return itr->second;
}

Account Bank::Deposit(long accountNumber,float amount) {
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}

Account Bank::Withdraw(long accountNumber,float amount) {
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}

void Bank::CloseAccount(long accountNumber) {
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    cout<<"Account Deleted"<<itr->second;
    accounts.erase(accountNumber);
}

void Bank::ShowAllAccount() {
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
        cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
    }
}

Bank::~Bank() {
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
    outfile<<itr->second;
    }
    outfile.close();
}

int main() {
    
}
