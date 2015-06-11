#ifndef LISTNODE_MAHRAD_H
#define LISTNODE_MAHRAD_H

#include<string>
#include "StockAccount_Mahrad.h"

class Node{

	friend class LinkedList;			//declare LinkedList class as friend
	
public:
	Node(StockAccount myStock)
	:stock_info(myStock)
	{
		this->next=NULL;
	}

private:
	StockAccount stock_info;		//each node contains elements and next pointer
	Node *next;
 };

#endif