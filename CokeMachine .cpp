/*
Alexander Eseyin
Program:CokeMachine.cpp
Due Date: Nov 19th-2018
*/

//Coke Machine cpp file 
#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<stdexcept>
#include"VendingMachine.h"
#include"CokeMachine.h"
using namespace std;
/*Memeber Functions for the CokeMachine Class*/
/* Scope Resolution operator (::) is used to link the functions to the CokeMachine Class*/

CokeMachine::CokeMachine(std::string name, int price, int change, int inventory)
	:CokePrice{price}, inventoryLevel{inventory }
{
	setMachineName(name);
	IncrementChangeLevel(change);
	//incrementInventory(change);

}
/*string CokeMachine::getmachinename() const
{
	return machineName;

}*/
bool CokeMachine::buyACoke(int payment, std::string& change, int& action)
{
	int tempChangeLevel=0;
	tempChangeLevel+=CokePrice;
	IncrementChangeLevel(tempChangeLevel);
	int tempMax=getMaxChangeCapacity();
	if (inventoryLevel == 0)  //Checks if inventory level is 0 and returns a message back to the user
	{
		action = 2;
		return false;
	}
	else if (tempChangeLevel == 0 ||(payment-CokePrice)>tempMax ) // Checks the change level and returns a message if it is = 0 or the changelevel is lower than change expected
	{
		action = 3;
		return false;
	}
	else if (payment < CokePrice)
	{
		action = 4;
		return false;
	}

	else if (payment > CokePrice)
	{
		action = 1;
		inventoryLevel--;
														//=getChangeLevel();
														//changeLevel += payment; //getChangeLevel()
		tempChangeLevel+=CokePrice;
		//incrementInventory(tempChangeLevel);
		//IncrementChangeLevel(tempChangeLevel);
		change = displayMoney(std::stoi(change = std::to_string(payment - CokePrice)));
		tempChangeLevel=tempChangeLevel-(payment - CokePrice);
		//changeLevel = changeLevel - (payment - CokePrice);
		return true;
	}
	else
	{
		action = 5;
		inventoryLevel--;
		tempChangeLevel += CokePrice;
		//incrementInventory(tempChangeLevel);
		IncrementChangeLevel(tempChangeLevel);
		//changeLevel += payment;
		return true;
	}

};
int CokeMachine::getInventoryLevel()
{
	return inventoryLevel;
}
int CokeMachine::getMaxInventoryCapacity()
{
	return maxInventoryCapacity;
}
bool CokeMachine::incrementInventory(int amountToAdd)
{
	if (inventoryLevel == 100)
	{
		return false;
	}
	else if ((inventoryLevel + amountToAdd) > maxInventoryCapacity)
	{
		return false;
	}
	else
	{
		inventoryLevel += amountToAdd;
		return true;
	}

	{
	}
	return true;
}
/*string CokeMachine::getChangeLevel()
{
	return displayMoney(changeLevel);
}*/
/*bool CokeMachine::IncrementChangeLevel(int amountToAdd)
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
}*/
/*string CokeMachine::getMaxChangeCapacity()
{

	return displayMoney(maxChangeCapacity);
}*/
string CokeMachine::getCokePrice()
{

	return displayMoney(CokePrice);
}
/*string CokeMachine::displayMoney(int amount) const 
{
	std::string dollars{ std::to_string(amount / 100) };
	std::string cents{ std::to_string(std::abs(amount % 100)) };
	return  "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}*/
/*void CokeMachine::setMachineName(string newMachinename)
{
	machineName=newMachinename;
}*/
void CokeMachine::setCokePrice(int newCokePrice)
{
	CokePrice=newCokePrice;
}

 		/*Writing to an outputfile*/
string CreateCokeOutputLine(const CokeMachine& read)
{
	 ostringstream createfile;
	 createfile<<read.getmachinename()<<"|"<<read.CokePrice<<"|"<<read.getChangeLevel()<<"|"<<read.inventoryLevel<<endl;
	return createfile.str();
}

						/*Operator Overload*/
ostream& operator<<(ostream& output, const CokeMachine& check)
{
	output << "Current inventory Level: "   << check.inventoryLevel<<endl; //inventoryLevel
	output << "Max Inventory Capacity : "   << check.maxInventoryCapacity<<endl;
	output << "Current Change Level: "   << check.displayMoney(check.getChangeLevel())<<endl;
	
	output << "Maximum Change Capacity: "   << check.displayMoney(check.getMaxChangeCapacity())<<endl;
	//output << "Maximum Change Capacity: "   << check.maxChangeCapacity<<endl;
	output << "Current Coke Price: "   << check.CokePrice<<endl;
	return output;
}
CokeMachine::~CokeMachine()//destructor
{
}
