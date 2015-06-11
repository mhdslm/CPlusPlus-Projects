#ifndef LIST_MAHRAD_H
#define	LIST_MAHRAD_H

#include <iostream>
#include <iomanip>
using namespace std;
//#include <new>

#include "Listnode_Mahrad.h"								//include Node class definitions
//#include "StockAccount_Mahrad.h"

class LinkedList{

public:
	
	LinkedList();											//constructor
	~LinkedList();											//destructor
	void addToStart(StockAccount);							//add to the beginning of the list		
	bool isEmpty() const;									//check to see if the list is empty
	void SortLinkedList();									//sort the linked list using bubble sort algorithm
	void printList();		
	double CopyToPortfolioList(LinkedList&,StockAccount&,string [], int [], double [],double []);	//copy account_formation.txt to linked list at the start of program
	
	
private:
	Node *myHead;											//head pointer
	Node *myTail;											//tail pointer
	Node *getNewNode(StockAccount &);						//function to get new node (name and number)
 };

//default constructor
LinkedList::LinkedList()
:myHead(0),myTail(0)
{
	//empty body
}//end LinkedList constructor

//destructor
LinkedList::~LinkedList()
{
	if(!isEmpty())
	{
		Node *currentPtr=myHead;
		Node *tempPtr;
		while(currentPtr!=0) {									//delete remaining nodes
			tempPtr=currentPtr;
		
			currentPtr=currentPtr->next;
			delete tempPtr;										//deallocating the memory for tempPtr
		}
	}
	//cout<<"All nodes destroyed\n\n";
	myHead=myTail=0;
}

//getNewNode
Node *LinkedList::getNewNode(StockAccount& myStock )
{
	return new Node(myStock);
}
//Add a new node at the beginning
void LinkedList::addToStart(StockAccount myStock)
{
	
	Node *newPtr=getNewNode(myStock);
	
	if(isEmpty())												//if List is empty
		myHead=myTail=newPtr;
	else
	{
		newPtr->next=myHead;
		myHead=newPtr;
	}
}

//is List empty? 
bool LinkedList::isEmpty() const
{
	return myHead==0;
}
//print list
void LinkedList::printList()
{
	
	if(isEmpty())
	{
		cout<<"The list is empty\n\n";
		return;
	}
	Node *currentPtr=myHead;
	cout<<"Cash balance = $"<<currentPtr->stock_info.getBalance()<<endl;
	cout<<"Portfolio List is:\n";
	cout<<"Company Symbol"<<setw(10)<<"Number"<<setw(19)<<"Price per share"<<setw(15)<<"Total value\n";
	double total_portfolio_value=currentPtr->stock_info.getBalance();
	while(currentPtr!=0)
	{
		cout<<currentPtr->stock_info<<endl;
		total_portfolio_value+=currentPtr->stock_info.getTotal();
		currentPtr=currentPtr->next;
	}
	cout<<"\n\n";
	cout<<"Total portfolio value: $"<<fixed<<setprecision(2)<<total_portfolio_value<<endl<<endl;
}
//sorting the LinkedList (bubble sort)
void LinkedList::SortLinkedList()
{

	Node *currentPtr=myHead;

	int cnt=0;
	string temp_sym;
	int temp_num;
	double temp_price, temp_total;

	while(currentPtr!=0)
	{
		currentPtr=currentPtr->next;
		cnt++;
	}
	currentPtr=myHead;
	for(int i=0; i<cnt-1;i++)
	{
		while(currentPtr->next)
		{
			if(currentPtr->stock_info.getTotal() < currentPtr->next->stock_info.getTotal())			//bubble sort list according to total(changing the data elements)
			{
				//swaping symbols
				temp_sym=currentPtr->stock_info.getSymbol();
				currentPtr->stock_info.setSymbol(currentPtr->next->stock_info.getSymbol());
				currentPtr->next->stock_info.setSymbol(temp_sym);

				//swaping number of shares
				temp_num=currentPtr->stock_info.getShares();
				currentPtr->stock_info.setShares(currentPtr->next->stock_info.getShares());
				currentPtr->next->stock_info.setShares(temp_num);
				
				//swaping price per share
				temp_price=currentPtr->stock_info.getPrice();
				currentPtr->stock_info.setPrice(currentPtr->next->stock_info.getPrice());
				currentPtr->next->stock_info.setPrice(temp_price);
				
				//swaping total values
				temp_total=currentPtr->stock_info.getTotal();
				currentPtr->stock_info.setTotal(currentPtr->next->stock_info.getTotal());
				currentPtr->next->stock_info.setTotal(temp_total);

			}
			currentPtr=currentPtr->next;
		}
		currentPtr=myHead;
	}

}

//copy account information to LinkedList
double LinkedList::CopyToPortfolioList(LinkedList& PortfolioList,StockAccount& stock,string account_sym[], int account_num[], double account_price[],double account_total[])
{
	int j=0;
	double myBalance=0.0;
	stock.setBalance(10000.00);

	while(account_sym[j]!="END")									//copy account information to portfolio list
	{
		stock.setSymbol(account_sym[j]);
		stock.setShares(account_num[j]);
		stock.setPrice(account_price[j]);
		stock.setTotal(account_total[j]);
		myBalance=stock.getBalance();
		stock.setBalance(myBalance-account_total[j]);
		if(account_num[j]!=0)
			PortfolioList.addToStart(stock);
		j++;
	}
	j=0;
	return myBalance;
}
#endif

