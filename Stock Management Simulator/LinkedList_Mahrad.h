#ifndef LINKEDLIST_MAHRAD_H
#define	LINKEDLIST_MAHRAD_H

#include <iostream>
#include <iomanip>
using namespace std;
//#include <new>

#include "Node_Mahrad.h"								//include Node class definitions

class LinkedList{

public:
	
	LinkedList();										//constructor
	~LinkedList();										//destructor
	void addToStart();									//add to the beginning of the list		
	void addToEnd();									//add to the end of the list
	void printList();									//print the list
	bool removeFromStart();								//remove from beginning of the list
	bool removeFromEnd();								//remove from end of the list
	void removeNodeFromList(int);						//remove from the list by item number
	void removeNodeFromList(string);					//remove from the list by item name
	bool isEmpty() const;								//check to see if the list is empty
private:
	Node *myHead;										//head pointer
	Node *myTail;										//tail pointer
	Node *getNewNode(string&,int);						//function to get new node (name and number)
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
		while(currentPtr!=0) {	//delete remaining nodes
			tempPtr=currentPtr;
			//cout<<tempPtr->(itemName, itemNo);
			currentPtr=currentPtr->next;
			delete tempPtr;										//deallocating the memory for tempPtr
		}
	}
	cout<<"All nodes destroyed\n\n";
}

//getNewNode
Node *LinkedList::getNewNode(string& myName, int myNo)
{
	return new Node(myName,myNo);
}
//Add a new node at the beginning
void LinkedList::addToStart()
{
	int myNo;
	string myName;
	cout<<"Please enter product number to insert at beginning"<<endl;
	cin>>myNo;
	cout<<"Please enter the name for the product"<<endl;
	cin>>myName;
	cout<<"\n\n";
	Node *newPtr=getNewNode(myName,myNo);
	
	if(isEmpty())			//if List is empty
		myHead=myTail=newPtr;
	else
	{
		newPtr->next=myHead;
		myHead=newPtr;
	}
}

//Add a new node at the beginning
void LinkedList::addToEnd()
{
	int myNo;
	string myName;
	cout<<"Please enter product number to insert at beginning"<<endl;
	cin>>myNo;
	cout<<"Please enter the name for the product"<<endl;
	cin>>myName;
	cout<<"\n\n";
	Node *newPtr=getNewNode(myName,myNo);
	
	if(isEmpty())			//if List is empty
		myHead=myTail=newPtr;
	else
	{
		myTail->next=newPtr;
		myTail=newPtr;
	}
}

//Remove the beginning node

bool LinkedList::removeFromStart()
{
	if(isEmpty())			//List is empty
		return false;		//delete unsuccessful
	else
	{
		Node *tempPtr=myHead;
		if(myHead==myTail)
			myHead=myTail=0;
		else
			myHead=myHead->next;
		delete tempPtr;
		return true;		//delete successful
	}
	cout<<"\n\n";
}

//Remove the end node

bool LinkedList::removeFromEnd()
{
	if(isEmpty())			//List is empty
		return false;		//delete unsuccessful
	else
	{
		Node *tempPtr=myTail;
		if(myHead==myTail)
			myHead=myTail=0;
		else
		{
			Node *currentPtr=myHead;

			//locate the second to last element
			while(currentPtr->next !=myTail)
				currentPtr=currentPtr->next;
			myTail=currentPtr;
			currentPtr->next=0;
		}
		delete tempPtr;
		return true;		//delete successful
	}
	cout<<"\n\n";
}

//Remove a node from the list by entering an item number
void LinkedList::removeNodeFromList(int myNo)
{
	Node *tempPtr=0;
	Node *currentPtr=myHead;

	if(myHead==myTail)
		myHead=myTail=0;
	else
	{
		if(currentPtr->itemNo==myNo)
		{
			myHead=currentPtr->next;
			cout<<"\n\n";
			return;
		}
		else
		{
		
		//locate the preceding element
		while(currentPtr->next->itemNo !=myNo && currentPtr->next != myTail)
			currentPtr=currentPtr->next;
		if(myTail->itemNo==myNo)
		{
			myTail=currentPtr;
			currentPtr->next=0;
			cout<<"\n\n";
			return;
		}
		else if(currentPtr->next==myTail)
			cout<<"Item Not Found!\n\n";
		else
		{
		tempPtr=currentPtr->next;
		currentPtr->next=currentPtr->next->next;
		}
		}
	}
	delete tempPtr;
	cout<<"\n\n";
	
}

//Remove a node from the list by entering an item name
void LinkedList::removeNodeFromList(string myName)
{
	Node *tempPtr=0;
	Node *currentPtr=myHead;
	//myTail->next=NULL;

	if(myHead==myTail)
		myHead=myTail=0;
	else
	{
		if(currentPtr->itemName==myName)
		{
			myHead=currentPtr->next;
			cout<<"\n\n";
			return;	
		}
		else
		{
		
		//locate the preceding element
		while(currentPtr->next->itemName !=myName && currentPtr->next != myTail)
			currentPtr=currentPtr->next;
		if(myTail->itemName==myName)
		{
			myTail=currentPtr;
			currentPtr->next=0;
			cout<<"\n\n";
			return;
		}else if(currentPtr->next ==myTail)
			cout<<"Item Not Found!\n\n";
		else
		{
		tempPtr=currentPtr->next;
		currentPtr->next=currentPtr->next->next;
		}
		}
	}
	delete tempPtr;
	cout<<"\n\n";
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
	cout<<"List:\n";
	cout<<"Item No"<<setw(15)<<"Item Name\n";
	while(currentPtr!=0)
	{
		cout<<currentPtr->itemNo<<setw(16)<<currentPtr->itemName<<endl;
		currentPtr=currentPtr->next;
	}

	cout<<"\n\n";
}
#endif

