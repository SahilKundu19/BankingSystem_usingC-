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

long Account::NextAccountNumber = 0;

int main() {
    
}
