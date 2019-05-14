/*
Alexander Eseyin
Program:VendingMachine.h
Due Date: Nov-19-2018
*/

//Coke Machine Class 
#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H
class VendingMachine
{
public:
	std::string getmachinename() const;
	virtual bool incrementInventory(int)=0;
	int getChangeLevel() const;
	int getMaxChangeCapacity() const;
	std::string displayMoney(int) const ;
	bool IncrementChangeLevel(int);
	void setMachineName(std::string);
	virtual int getMaxInventoryCapacity()=0; //added recently
	virtual int getInventoryLevel()=0; //added recently

 /* data memebers*/
private:
	std::string machineName;
	int changeLevel=0;
	int maxChangeCapacity{ 5000 };
};
#endif