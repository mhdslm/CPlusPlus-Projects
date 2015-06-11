#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <string>
#include "time.h"
using namespace std;
#include "BankAccount_Du.h"

BankAccount::BankAccount()
{
	ofstream myfile;
	myfile.open("BankHistory.txt");
	myfile<<"Event"<<setw(10)<<"Amount"<<setw(10)<<"Date"<<endl;
	myfile.close();
	//Balance = 10000;

	std::ifstream file;
	file.open("Cash.txt",std::ios::in);
	file>>Balance;
	file.close();
	
	if(Balance < 0) Balance = 10000;
}

void BankAccount::Deposit(double amount)
{
	Balance += amount;
	time_t now = time(0);
	tm *t = localtime(&now);

	ofstream file;	
	file.open("BA_History.txt",std::ios_base::app);
	file << "Deposit" << setw(9) <<"$" << amount <<setw(9)
		<<1+t->tm_mon<<"/"<<t->tm_mday<<"/"<<1980+t->tm_year << endl;
}

double BankAccount::Withdraw(double amount)
{
	Balance -= amount;
	time_t now = time(0);
	tm *t = localtime(&now);

	ofstream file;	
	file.open("BA_History.txt",std::ios_base::app);
	file << "Withdraw" << setw(9) <<"$" << amount << setw(9)
		<<1+t->tm_mon<<"/"<<t->tm_mday<<"/"<<1990+t->tm_year<< endl;
	Balance -= amount;
	return Balance;
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

void BankAccount::View_balance()
{
	std::cout<<"You have $"<<Balance<<" in your bank account."<<std::endl;
}

void BankAccount::storeCash()
{
	std::ofstream myfile;
	myfile.open("Cash.txt");
	myfile<<Balance;
	myfile.close();
}