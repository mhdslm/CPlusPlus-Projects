#ifndef ACCOUNT_MAHRAD_H
#define	ACCOUNT_MAHRAD_H

//Account class is abstarct base class
class Account {
public:
	//Account();																//constructor
	virtual double getBalance()=0;												//get balance(pure virtual function)
	virtual void setBalance(double)=0;											//set balance(pure virtual function)

};


#endif