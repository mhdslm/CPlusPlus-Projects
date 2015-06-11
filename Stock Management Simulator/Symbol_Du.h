#include <string>
#ifndef NODE_DU_H
#define NODE_DU_H

class Node
{
	friend class StockAccount;
private : 
	string symbol;
	int share;
	double price;
	Node *prev; 
	Node *next; 

public : 
	double data; 
	
	Node(string& symbol, int number, double price) : symbol(symbol), share(number), price(price)
	{ 
		//head=tail=NULL; 
		this->next = NULL;
		this->prev = NULL;
	} 

};
#endif