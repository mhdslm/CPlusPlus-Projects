#ifndef STOCKACCOUNT_MAHRAD_H
#define	STOCKACCOUNT_MAHRAD_H

#include<iostream>
#include <string>
#include<iomanip>
#include<fstream>
#include<ctime>																			//time information
#include "Account_Mahrad.h"																//include base class definitions
using namespace std;

class StockAccount: public Account {													//public inheritance
	friend ostream &operator<<(ostream &output, const StockAccount &myStock);
public:

	StockAccount()																			//default constructor
	{
		setSymbol(" ");
		setShares(0);
		setBalance(10000.00);
	}
	StockAccount(const string & mySym, int myShares)										//overloading constructor
		: stock_sym(mySym), num_of_shares(myShares)
	{
		//empty body
	}
	//~StockAccount();																		//destructor

	void display_stock_price(string [],double []);											//display price of stock
	bool buy_shares(string [], double []);													//buy shares
	bool sell_shares(string [], double[]);													//sell shares
	bool alreadyInList(string [],int& );
	void setSymbol(string);																	//set stock symbol
	void setShares(int);																	//set stock shares
	void setPrice(double);
	double getPrice();
	void setTotal(double);
	string getSymbol();
	int getShares();
	double getTotal();
	virtual void setBalance(double);														//set balance
	virtual double getBalance();
	
	void store_account_information(StockAccount myStock);									//store new stock to account file
	void store_transaction(StockAccount myStock, string trans_type);						//store new transaction
	void update_account_information(string [],int [],double [],double l[],int);				//for buy information
	void update_sell_information(string [],int [],double [],double [],int );				//for sell information
																	
	void read_transaction_history(string [],string [], int [], double [],double [], string []);		//read stock transaction history
	void read_account_information(string [], int [], double [],double []);					//read account information
	void setStockInfo();

	void readStockFile(string [], double [], string []);
	

private:
	//utility functions
	int find_linear(string mylist [], int num_in_list, string element);						//linear search (utility function)
	struct tm* getDateTime();																//get current loacal time and date
	string stock_sym;
	int num_of_shares;
	double cash_balance;
	double stock_price;
	double total_value;
	
	
};
// read stock file (results.txt)
void StockAccount::readStockFile(string company_name[], double price_per_share[], string date[])
{
	ifstream stockfile;
	stockfile.open("Results.txt");
	int i=0;
	while(!stockfile.eof())
	{
		stockfile>>company_name[i]>>price_per_share[i]>>date[i];
		i++;
	}
	stockfile.close();
}

//linear search
int StockAccount::find_linear(string mylist [], int num_in_list, string element)
{
	for(int i=0;i<num_in_list;i++)												//searching whole list to find the element
		if(mylist[i]==element)
			return i;
	return -1;																	//if not found return -1
}
//Get Current Date and Time

struct tm* StockAccount::getDateTime()
{
	time_t t=time(0);			//get time now
	struct tm*now=localtime(&t);
	return now;
}

//output operator overloading
ostream &operator<<(ostream &output, const StockAccount &myStock)
{
	output<<myStock.stock_sym<<setw(16)
		  <<myStock.num_of_shares<<setw(12)
		  <<"$"<<myStock.stock_price<<setw(10)
		  <<"$"<<myStock.total_value;
	return output;
}
//~StockAccount();
//set symbol
void StockAccount::setSymbol(string mySym)
{
	stock_sym=mySym;
}
//set shares
void StockAccount::setShares(int myShares)
{
	num_of_shares=myShares;
}
//set stock price
void StockAccount::setPrice(double myPrice)
{
	stock_price=myPrice;
}
//get price
double StockAccount::getPrice()
{
	return stock_price;
}
//set total value
void StockAccount::setTotal(double myTotal)
{
	total_value=myTotal;
}
//get symbol
string StockAccount:: getSymbol()
{
	return stock_sym;
}

//get shares
int StockAccount::getShares()
{
	return num_of_shares;
}
//get total
double StockAccount::getTotal()
{
	return total_value;
}
//set cash balance
void StockAccount::setBalance(double myBalance)
{
	cash_balance=myBalance;
}
//return cash balance
double StockAccount::getBalance()
{
	return cash_balance;
}
//display price of stock
void StockAccount::display_stock_price(string company_name[], double price_per_share[])
{
	
	cout<<"Please enter the stock symbol: ";
	cin>>stock_sym;
	//int index=std::distance(company_name,std::find(company_name,company_name+60,stock_sym));
	int index=find_linear(company_name, 60, stock_sym);

	if(index==-1)
		cout<<"\n\nStock Symbol cannot be found!"<<endl;
	else
	{
	cout<<"\n\nCompany Symbol"<<setw(20)<<"Price per share"<<endl;
	cout<<company_name[index]<<setw(16)<<"$"<<price_per_share[index]<<endl<<endl;
	}
}


//buy shares
bool StockAccount::buy_shares(string company_name[], double price_per_share[])
{
	cout<<"Your balance is: $"<<cash_balance<<endl<<endl;
	
	cout<<"Please enter the stock symbol you wish to purchase: ";
	cin>>stock_sym;
	int index=find_linear(company_name, 60, stock_sym);									//linear search to find index of entered symbol in stock file
	if(index==-1)
	{
		cout<<"\n\nStock is not available!\n"<<endl;
		return false;
	}
	cout<<"\nPlease enter the number of shares: ";
	cin>>num_of_shares;
	double max_amount;
	cout<<"\nPlease enter the maximum amount you are willing to pay per share: ";
	cin>>max_amount;


	stock_price=price_per_share[index];
	total_value=num_of_shares*price_per_share[index];
	
	if((max_amount>=price_per_share[index]) && (max_amount <= cash_balance) && (total_value<=cash_balance))
	{
		cout<<"\n\nYou have purchased "<<num_of_shares<<" shares of "<<company_name[index]<<" at "<<"$"<<price_per_share[index]<<" each for a total of $"<<total_value<<endl<<endl;
		cash_balance-=num_of_shares*price_per_share[index];
		//return true;
	}
	else if(max_amount < price_per_share[index])							//if max amount is less than price per share
	{
		cout<<"\nTransaction failed!\nCost per stock is higher than the entered amount.\n"<<endl;
		return false;
	}
	else if(max_amount > cash_balance)										//if max amount is greater than cash balance
	{
		cout<<"\nTransaction failed!\nEntered amount is higher than your balance.\n"<<endl;
		return false;
	}
	else if(total_value > cash_balance)										//if total purchased value is greater than cash balance
	{
		cout<<"\nTransaction failed!\nTotal purchased value is higher than your balance.\n"<<endl;
		return false;
	}
	return true;
}

//sell shares
bool StockAccount::sell_shares(string account_sym[], double account_price[])
{
	cout<<"Your balance is: $"<<cash_balance<<endl<<endl;
	
	cout<<"Please enter the stock symbol you wish to sell: ";
	cin>>stock_sym;
	int index=find_linear(account_sym, 60, stock_sym);							//linear search to find index of entered symbol in stock file
	if(index==-1)
	{
		cout<<"\n\nStock is not available!\n"<<endl;
		return false;
	}
	cout<<"\nPlease enter the number of shares: ";
	cin>>num_of_shares;
	double min_amount;
	cout<<"\nPlease enter the minimum amount you are willing to sell per share: ";
	cin>>min_amount;


	stock_price=account_price[index];
	total_value=num_of_shares*account_price[index];
	
	if((min_amount<=account_price[index]) && (min_amount <= cash_balance) && (total_value<=cash_balance))
	{
		cout<<"\n\nYou have sold "<<num_of_shares<<" shares of "<<account_sym[index]<<" at "<<"$"<<account_price[index]<<" each for a total of $"<<total_value<<endl<<endl;
		cash_balance-=num_of_shares*account_price[index];
		//return true;
	}
	else if(min_amount > account_price[index])							//if max amount is less than price per share
	{
		cout<<"\nTransaction failed!\nCost per stock is lower than the entered amount.\n"<<endl;
		return false;
	}
	else if(min_amount > cash_balance)										//if max amount is greater than cash balance
	{
		cout<<"\nTransaction failed!\nEntered amount is higher than your balance.\n"<<endl;
		return false;
	}
	else if(total_value > cash_balance)										//if total purchased value is greater than cash balance
	{
		cout<<"\nTransaction failed!\nTotal purchased value is higher than your balance.\n"<<endl;
		return false;
	}
	return true;
}


//check to see if stock is already in account
bool StockAccount::alreadyInList(string account_sym [], int& account_index)
{
	account_index=find_linear(account_sym, 60, stock_sym);
	if(account_index==-1)
		return false;
	else
		return true;
}

//store account information
void StockAccount::store_account_information(StockAccount myStock)
{

	fstream stock_history;
	stock_history.open("account_information.txt", fstream::app);				//writing purchased stock into account information file
	stock_history<<myStock.stock_sym<<setw(17)
				 <<myStock.num_of_shares<<setw(10)
				 <<myStock.stock_price<<setw(12)
				 <<myStock.total_value<<endl;
				 
	stock_history.close();

}

//read account information
void StockAccount::read_account_information(string account_sym[], int account_num[], double account_price[],double account_total[])
{
	ifstream account;
	account.open("account_information.txt");
	int i=0;
	while(!account.eof())
	{
		account>>account_sym[i]>>account_num[i]>>account_price[i]>>account_total[i];		//read the file and write them to corresponding arrays
		i++;
	}
	account_sym[i-1]="END";																	//add "END" after last stock to the array of symols 
	account_num[i-1]=0;
	account_price[i-1]=account_total[i-1]=0;
	account.close();
	
}

//store new transaction
void StockAccount::store_transaction(StockAccount myStock, string trans_type)
{
	struct tm* now=getDateTime();
	
	fstream stock_history;
	stock_history.open("stock_transaction_history.txt", fstream::app);

	stock_history<<trans_type<<setw(17)
				 <<myStock.stock_sym<<setw(17)
				 <<myStock.num_of_shares<<setw(10)
				 <<myStock.stock_price<<setw(12)
				 <<myStock.total_value<<setw(11)
				 <<now->tm_hour<<':'<<now->tm_min<<':'<<now->tm_sec<<endl;

	stock_history.close();

}

//read stock transaction history
void StockAccount::read_transaction_history(string trans_type[],string trans_sym[], int trans_num[], double trans_price[],double trans_total[], string trans_time[])
{
	ifstream StockTransaction;
	StockTransaction.open("stock_transaction_history.txt");
	int i=0;
	while(!StockTransaction.eof())
	{
		StockTransaction>>trans_type[i]>>trans_sym[i]>>trans_num[i]>>trans_price[i]>>trans_total[i]>>trans_time[i];
		i++;
	}
	trans_sym[i-1]=trans_time[i-1]="END";
	trans_num[i-1]=0;
	trans_price[i-1]=trans_total[i-1]=0;
	StockTransaction.close();
	
}

//update account information

void StockAccount::update_account_information(string account_sym[],int account_num[],double account_price[],double account_total[],int account_index)
{
	if(stock_sym==account_sym[account_index])
	{
		account_num[account_index]+=num_of_shares;
		account_total[account_index]+=total_value;						//if the purchased the stock is already in the file
	}																	//just update number of shares and total value

	ofstream account;
	account.open("account_information.txt");
	int i=0;
	while(account_sym[i]!="END")										//write updated information to account_information file
	{
	
		account<<account_sym[i]<<setw(17)
			   <<account_num[i]<<setw(10)
			   <<account_price[i]<<setw(12)
			   <<account_total[i]<<endl;
		i++;
	}

	account.close();
}

//update sell information

void StockAccount::update_sell_information(string account_sym[],int account_num[],double account_price[],double account_total[],int account_index)
{
	if(stock_sym==account_sym[account_index])
	{
		account_num[account_index]-=num_of_shares;
		account_total[account_index]-=total_value;						//if the purchased the stock is already in the file
	}																	//just update number of shares and total value

	ofstream account;
	account.open("account_information.txt");
	int i=0;
	while(account_sym[i]!="END")										//write updated information to account_information file
	{
	
		account<<account_sym[i]<<setw(17)
			   <<account_num[i]<<setw(10)
			   <<account_price[i]<<setw(12)
			   <<account_total[i]<<endl;
		i++;
	}

	account.close();
}

#endif


