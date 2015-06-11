#ifndef NODE_MAHRAD_H
#define NODE_MAHRAD_H

#include<string>


class Node{

	friend class LinkedList;			//declare LinkedList class as friend
public:
	Node(string& name, int no)
	:itemName(name), itemNo(no)
	{
		this->next=NULL;
	}

private:
	string itemName;		//each node contains elements and next pointer
	int itemNo;
	Node *next;
 };
#endif