/*
Alexander Eseyin
Program:VendingMachine.cpp
Due Date: Nov 19th-2018
*/

//Vending Machine cpp file 
#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<stdexcept>
#include"VendingMachine.h"
using namespace std;
/*Memeber Functions for the VendingMachine Class*/
string VendingMachine::getmachinename() const
{
	return machineName;

}


int VendingMachine::getChangeLevel() const
{
	return changeLevel;
}
bool VendingMachine::IncrementChangeLevel(int amountToAdd)
{
	if (changeLevel > maxChangeCapacity)
	{
		return false;
	}
	else if (changeLevel + amountToAdd > maxChangeCapacity)
	{
		return false;
	}
	else
	{

		changeLevel = changeLevel + amountToAdd;
		return true;
	}
}
int VendingMachine::getMaxChangeCapacity() const
{

	return maxChangeCapacity;
}

string VendingMachine::displayMoney(int amount) const 
{
	std::string dollars{ std::to_string(amount / 100) };
	std::string cents{ std::to_string(std::abs(amount % 100)) };
	return  "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}
void VendingMachine::setMachineName(string newMachinename)
{
	machineName=newMachinename;
}
