#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Account_Mahrad.h"
#include <fstream>
using namespace std;

class BankAccount : public Account
{
	friend class StockAccount;
public:

	BankAccount();
	void View_balance();				
	double Deposit(double);
	double Withdraw(double);			
	void Print_history();
	void storeCash();
	//void printBalance();
	virtual double getBalance();
	virtual void setBalance(double myBalance);

private:
	
	double amount;
	double cash_balance;

};

BankAccount::BankAccount()
{
	//StockAccount.setBalance(10000.00);
	setBalance(10000.00);
}
//set cash balance
void BankAccount::setBalance(double myBalance)
{
	cash_balance=myBalance;
}
//return cash balance
double BankAccount::getBalance()
{
	return cash_balance;
}
void BankAccount::View_balance()
{
	cout<<"You have $"<<getBalance()<<" in your bank account."<<std::endl;
}

double BankAccount::Deposit(double myAmount)
{
	amount=myAmount;
	cash_balance += amount;
	time_t now = time(0);
	tm *t = localtime(&now);

	ofstream file;	
	file.open("BA_History.txt",std::ios_base::app);
	file << "Deposit" << setw(9) <<"$" << amount <<setw(9)
		<<1+t->tm_mon<<"/"<<t->tm_mday<<"/"<<1980+t->tm_year << endl;
	return cash_balance;
}

double BankAccount::Withdraw(double myAmount)
{
	
	
	if(amount<=cash_balance){
		amount=myAmount;
		cash_balance -= amount;
	time_t now = time(0);
	tm *t = localtime(&now);
	

	ofstream file;	
	file.open("BA_History.txt",std::ios_base::app);
	file << "Withdraw" << setw(9) <<"$" << amount << setw(9)
		<<1+t->tm_mon<<"/"<<t->tm_mday<<"/"<<1990+t->tm_year<< endl;
	}else
		cout<<"Account balance is not sufficient!"<<endl;
	//Balance -= amount;
	return cash_balance;
}

void BankAccount::Print_history()
{
	string temp;
	ifstream file("BA_History.txt");
	if(file.is_open())
	{
		while( std::getline(file,temp))
		{
			cout<<temp<<"\n";
		}
		file.close();
	}
	else cout<<"Unable to open file";
}


#endif