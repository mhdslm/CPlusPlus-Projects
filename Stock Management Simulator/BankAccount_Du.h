#include "Symbol_Du.h"
#include "Account_Du.h"

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

class BankAccount : public Account
{
	friend class StockAccount;

public:

	BankAccount();
	void View_balance();				
	void Deposit(double);
	double Withdraw(double);			
	void Print_history();
	void storeCash();
	//void printBalance();

private:
	
	double amount;	
};
#endif