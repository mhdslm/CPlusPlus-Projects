// Name : Mahrad Salemi
// Date: 08/12/2013
// Course : 16:332:503 , PM for Financial Applications and Numerical Computing.
//Final Project : Account Management System

#include<iostream>														// used for input/output in the C++
#include<conio.h>
#include<cstdlib>														//standard tempplate library


#include "StockAccount_Mahrad.h"										//header file for StockAccount class definitions
#include "BankAccount_Mahrad.h"										//header file for StockAccount class definitions
#include "List_Mahrad.h"												//header file for List class definitions

int main()
{
	int option;
	LinkedList PortfolioList;
	StockAccount stock;
	BankAccount myAccount;
	bool flag1=false;
	bool flag2=false;
	bool already_in_list=false;

	//for transaction file
	string trans_type [60], trans_sym[60], trans_time[60];
	double trans_price[60], trans_total[60];
	int trans_num[60];

	//for results file
	string company_name[60], date[60];
	double price_per_share[60];
	int account_index;
	int k=0, m=0;
	
	//for account information file
	string account_sym[60];
	double account_price[60], account_total[60];
	int account_num[60];

	//for Bank Account
	double myAmount;

	//transaction type
	string type;


	stock.readStockFile(company_name,price_per_share,date);										//read stock file
	stock.read_transaction_history(trans_type,trans_sym,trans_num, trans_price, trans_total,trans_time);	//read transaction history
	stock.read_account_information(account_sym,account_num, account_price, account_total);		//read account information

	double myBalance=PortfolioList.CopyToPortfolioList(PortfolioList,stock,account_sym,account_num, account_price, account_total);	//copy account information to Portfolio List
	
	cout<<"Welcome to the Account Management System.\n\n";

	while(1)
	{
		cout<<"Please select an account to access:"<<endl
			<<"1. Stock Portfolio Account"<<endl
			<<"2. Bank Account"<<endl
			<<"3. Exit"<<endl
			<<"Option: ";
		cin>>option;

		switch(option)
		{
		case 1:																		//Stock Management System
			cout<<"\n\nStock Portfolio Account"<<endl;
			while(1)
			{
				cout<<"Please select an option:"<<endl
					<<"1. Display the price for a stock symbol"<<endl
					<<"2. Display the current portfolio"<<endl
					<<"3. Buy shares"<<endl
					<<"4. Sell shares"<<endl
					<<"5. View transaction history"<<endl
					<<"6. Return to previous menu"<<endl;

				cin>>option;
				if(option==6)																	//return to previous menu
					break;
				switch(option)
				{
				case 1:			
					
					stock.display_stock_price(company_name,price_per_share);					//display stock price
					
					break;
				case 2:
					PortfolioList.~LinkedList();												//clear linked list
					stock.read_account_information(account_sym,account_num, account_price, account_total);	//read account information
					myBalance=PortfolioList.CopyToPortfolioList(PortfolioList,stock,account_sym,account_num, account_price, account_total);	//copy account information to LinkedList
					PortfolioList.SortLinkedList();												//sort the Linked List
					PortfolioList.printList();													//print the Linked List

					break;
				case 3:

					flag1=stock.buy_shares(company_name,price_per_share);						//buy shares
					already_in_list=stock.alreadyInList(account_sym,account_index);				//check to see if the stock is already in list

					if(flag1)																	//if transaction went through
					{
						type="Buy";
						if(already_in_list)														//if in list
						{
							stock.update_account_information(account_sym,account_num,account_price,account_total,account_index); //just update the list(no new entry)
						}
						else																	//if it's not in the list
						{
							stock.store_account_information(stock);								//store the stock in account information
						}
					}
					stock.store_transaction(stock,type);												//store tranaction in file
					break;	
				case 4:
					flag2=stock.sell_shares(account_sym,account_price);						//sell shares
					already_in_list=stock.alreadyInList(account_sym,account_index);			//check to see if the stock is already in list

					if(flag2)																//if transaction went through
					{
						type="Sell";
						stock.update_sell_information(account_sym,account_num,account_price,account_total,account_index); //just update the list
					}
					stock.store_transaction(stock,type);												//store tranaction in file
					break;

				case 5:
					stock.read_transaction_history(trans_type,trans_sym, trans_num, trans_price,trans_total, trans_time);
					cout<<"Event"<<setw(15)<<"Company Symbol"<<setw(9)<<"Number"<<setw(19)<<"Price per share"<<setw(15)<<"Total value"<<setw(11)<<"Time\n";
					while(trans_sym[m]!="END")
					{
						cout<<trans_type[m]<<setw(7)<<trans_sym[m]<<setw(15)<<trans_num[m]<<setw(15)<<trans_price[m]<<setw(19)<<trans_total[m]<<setw(18)<<trans_time[m]<<endl;
						m++;
					}
					m=0;
					cout<<"\n";
					break;
				default:
					cout<<"You entered an invalid number!"<<endl;
					break;
				}
			}
			break;
		case 2:
				//Bank Account
			cout<<"\n\nBank Account"<<endl;
			while(1)
			{
				cout<<"Please select an option:"<<endl
					<<"1. View account balance"<<endl
					<<"2. Deposit Money"<<endl
					<<"3. Withdraw Money"<<endl
					<<"4. Print out history"<<endl
					<<"5. Return to previous menu"<<endl;

				cin>>option;
				if(option==5)																	//return to previous menu
					break;
				switch(option)
				{
				case 1:
					myAccount.View_balance();													//View Balance
					break;
				case 2:
					cout<<"Please enter the amount: "<<endl;
					cin>>myAmount;
					myAccount.Deposit(myAmount);
					break;
				case 3:
					cout<<"Please enter the amount: "<<endl;
					cin>>myAmount;
					myAccount.Withdraw(myAmount);
					break;
				case 4:
					myAccount.Print_history();
					break;
				default:
					cout<<"You entered an invalid number!"<<endl;
					break;
				}
			}
			break;
		case 3:												//exit the program
			exit(0);
		default:
			break;
		}
	}

	return 0;
}