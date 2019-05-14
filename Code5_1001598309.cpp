/*
Alexander Eseyin
Program:Code3_1001598309.cpp
Due Date: Nov 19th-2018
*/
#include<iostream>
#include<stdexcept>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
#include "CokeMachine.h"
#include "VendingMachine.h"
#include "CokeLib.h"
#include<string>
#include<gtkmm.h>
using namespace std;

				/*Functions*/
void get_command_line_params(int argc,char *argv[], string& infile, string& outfile)
{
	string INPUTFILENAME, OUTPUTFILENAME,cla;
	for (int i = 1; i < argc; i++)
	{
		cla = argv[i];

		if (cla.substr(0, cla.find("=")) == "INPUTFILENAME")
		{
			INPUTFILENAME = cla.substr(cla.find("=")+1, cla.length());
		}
		else if (cla.substr(0, cla.find("=")) == "OUTPUTFILENAME")
		{
			OUTPUTFILENAME = cla.substr(cla.find("=")+1, cla.length());
		}
		else
		{
			throw invalid_argument("Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME=");
		}
		infile=INPUTFILENAME;
		outfile=OUTPUTFILENAME;
		
		
	}
   
}
                /*This function prints out the Coke Menu*/

 /*int CokeMenu(void)
    {
        int choice=0;
            cout << "0.\t Walk away \n";
			cout << "1.\t Buy a Coke \n";
			cout << "2.\t Restock Machine \n";
			cout << "3.\t Add change \n";
			cout << "4.\t Display Machine Info \n";
			cout << "5.\t Update Machine Name \n";
			cout << "6.\t Update Coke Price \n";
			cin>>choice;
        return choice;
     }*/

        /*This function generates a windown that asks user to choose their menu*/
     int CokeMenu(void)
     {
        Gtk::Dialog *AskUser =new Gtk::Dialog(); // creating a new dialog box 
        //AskUser->set_layout(Gtk::HButtonBox);
        AskUser->set_title("Coke Machine");
        //AskUser->set_default_size(10,10);
        vector<string>buttons={"Cancel","Buy A Coke","Restock Machine","Add Change","Display Machine Info","Update Machine Name","Update Coke Price"};
        for(int i=0;i<buttons.size();i++)
        {
            AskUser->add_button(buttons[i],i); // creates a new button and store the contents of the vector in the button and the corresponding index.
        }
        AskUser->set_default_response(0);// sets the default option to zero. 
        Gtk::Label *UserLabel=new Gtk::Label("Please Choose an option"); // creates a text label for the window
        AskUser->get_content_area()->pack_start(*UserLabel);
        UserLabel->show();
       
        int result=AskUser->run();
        AskUser->close();
        delete AskUser;
        return result;
     }
     int Payment(void)
     {
         Gtk::Dialog *getPayment= new Gtk::Dialog();
         getPayment->set_title("payment");
         getPayment->add_button("Cancel",0);
         getPayment->add_button("Ok",1);
         getPayment->set_default_response(1);
         Gtk::Entry *PaymentEntry = new Gtk::Entry();
         PaymentEntry->set_text("Insert payment here");
         PaymentEntry->set_max_length(50);
         PaymentEntry->show();
         getPayment->get_content_area()->pack_start(*PaymentEntry);
         int result=getPayment->run();
         string text=PaymentEntry->get_text();
         result=stoi(text);
         getPayment->close();
         delete getPayment;
        return result;

     }
     int AddCoke(void)
     {
         Gtk::Dialog *getamountToAdd= new Gtk::Dialog();
         getamountToAdd->set_title("Add Coke");
         getamountToAdd->add_button("Cancel",0);
         getamountToAdd->add_button("Ok",1);
         getamountToAdd->set_default_response(1);
         Gtk::Entry *AmountEntry = new Gtk::Entry();
         AmountEntry->set_text("Insert amount to add here");
         AmountEntry->set_max_length(50);
         AmountEntry->show();
         getamountToAdd->get_content_area()->pack_start(*AmountEntry);
         int result=getamountToAdd->run();
         string text=AmountEntry->get_text();
         result=stoi(text);
         getamountToAdd->close();
         delete getamountToAdd;
        return result;

     }
     int AddChange(void)
     {
         Gtk::Dialog *getamountToAdd= new Gtk::Dialog();
         getamountToAdd->set_title("Add change");
         getamountToAdd->add_button("Cancel",0);
         getamountToAdd->add_button("Ok",1);
         getamountToAdd->set_default_response(1);
         Gtk::Entry *AmountEntry = new Gtk::Entry();
         AmountEntry->set_text("Insert amount to add here");
         AmountEntry->set_max_length(50);
         AmountEntry->show();
         getamountToAdd->get_content_area()->pack_start(*AmountEntry);
         int result=getamountToAdd->run();
         string text=AmountEntry->get_text();
         result=stoi(text);
         getamountToAdd->close();
         delete getamountToAdd;
        return result;

     }
     int altCokePrice(void)
     {
         Gtk::Dialog *getPayment= new Gtk::Dialog();
         getPayment->set_title("Enter new Coke Price?");
         getPayment->add_button("Cancel",0);
         getPayment->add_button("Ok",1);
         getPayment->set_default_response(1);
         Gtk::Entry *PaymentEntry = new Gtk::Entry();
         PaymentEntry->set_text("Insert payment here");
         PaymentEntry->set_max_length(50);
         PaymentEntry->show();
         getPayment->get_content_area()->pack_start(*PaymentEntry);
         int result=getPayment->run();
         string text=PaymentEntry->get_text();
         result=stoi(text);
         getPayment->close();
         delete getPayment;
        return result;

     }
    string changeMachineName(void)
    {
         Gtk::Dialog *newName= new Gtk::Dialog();
         newName->set_title("Enter new Coke Name?");
         newName->add_button("Cancel",0);
         newName->add_button("Ok",1);
         newName->set_default_response(1);
         Gtk::Entry *NameEntry = new Gtk::Entry();
         NameEntry->set_text("Insert payment here");
         NameEntry->set_max_length(50);
         NameEntry->show();
         newName->get_content_area()->pack_start(*NameEntry);
         string text=NameEntry->get_text();
         newName->close();
         delete newName;
         string result=text;
        return text;

    }
	
						/* Main Function*/

int main(int argc, char * argv[])
{
    Gtk::Main kit(argc, argv);


   
     
					/*Variable Declarations*/
	char output;
	int payment, action, amountToAdd,newCokePrice,input;
	string change,newMachinename,INPUTFILENAME,OUTPUTFILENAME;
	CokeMachine MyMachine{ "ERB Coke Machine",50, 500, 100 };// New Object created.
	map<string,int>invoice; // A map that prints the Coke reciept
	int invoiceCounter=1; // counter keeps track of the cokes that were bought
	try
		{
			get_command_line_params(argc,argv,INPUTFILENAME,OUTPUTFILENAME); //function call
		}
		catch (invalid_argument& say)// handles the errors if files are missing or cant be open.
		{
			cerr << "Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME=" << say.what() << endl;
			exit(1);
		}
		     /* declarations*/

		ifstream CokeInputFile{INPUTFILENAME};
		ofstream CokeOutputFile{OUTPUTFILENAME,ios::out};
		string CokeMachineLine;
		vector<string>ConstructorValues(4);
		vector<CokeMachine>setOfCokeMachines;

		if(CokeInputFile.is_open())//I need to check this
		{
			cout<<"Opening file..... \n";
			while(getline(CokeInputFile,CokeMachineLine))
			{
				if(ParseCokeLine(CokeMachineLine,ConstructorValues))
				{
					CokeMachine temp{ConstructorValues[0],stoi(ConstructorValues[1]),stoi(ConstructorValues[2]),stoi(ConstructorValues[3])};// creating a temp vector a storing the data passed from the file.
					setOfCokeMachines.push_back(temp);
				}
			}

		}
		else
		{
			cout<<"Could not open file for reading \n";
			exit(1);
		}
		int option=0;
		int choice = 9;
		
		
		do
		{
			int x=0;
			cout<<"Pick a Machine Name \n";
			cout<<"0. Exit\n"; // if user selects 0 , the if statment on line 101 is executed.
			
			/*print menu using Range-Based for-loop*/
			for(auto v:setOfCokeMachines) 
			{
				cout<<++x<<". ";
				cout<<v.getmachinename()<<endl;
			}
		cout<<++x<<". Add a new Coke Machine \n";
		cin>>option;
		if(option==0)// Exits the programm if user selects 0
		{
			CokeInputFile.close();
		if(CokeOutputFile.is_open())
		{
			for (int i=0;i<setOfCokeMachines.size();i++)
			{
				CokeOutputFile<<CreateCokeOutputLine(setOfCokeMachines[i]);
			}
				/* Added the Invoice to the OutputFile*/
				map<string,int>:: iterator print;
				CokeOutputFile<<"Your Coke Reciept \n";
				for(print=invoice.begin();print!=invoice.end();print++)
				CokeOutputFile<<print->first<<":"<<print->second<<endl;


		}
		else
		{
			cout<<"File could not be open \n";
		}
		CokeOutputFile.close();
			map<string,int>:: iterator it;
			cout<<"Your Coke Reciept \n";
			for(it=invoice.begin();it!=invoice.end();it++)
			cout<<it->first<<":"<<it->second<<endl;
			cout<<"Exiting...\n";
			exit(1);
		}
		else if(option==6)// update this so it is not hard coded.
		{
			//CokeMachine(); // calls the default machine Constructor.
			setOfCokeMachines.push_back(CokeMachine());
			//cout<<setOfCokeMachines.at(5).getmachinename()<<endl;
			cout<<"New Machine Added\n";
		}
		else{
		do {
			cout<<"\t  ===============\n";
			cout<<"\t"<<setOfCokeMachines.at(option-1).getmachinename()<<endl;
			cout<<" \t\tMenu\n";
			cout<<"\t  ===============\n\n";
            choice=CokeMenu(); //changed this to a dialog box
            
			
			switch (choice)
			{
			case 0:
				cout << " Have a wonderful Day \n";
                /*Gtk::MessageDialog *done = new Gtk::MessageDialog{"Have a wonderful Day",true,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
                done->run();
                done->close();
                delete done;*/
				break;
			case 1:
				//cout << "Insert Amount \n";
				//cin>>payment;
                payment=Payment();
				setOfCokeMachines[option-1].buyACoke(payment, change, action);

				if (action == 1)
				{
					/*cout << "Coke Price :" << setOfCokeMachines[option-1].getCokePrice() << endl;
					cout << "Payment Inserted :" << setOfCokeMachines[option-1].displayMoney(payment) << endl;
					cout << "Here's your coke \n";
					cout << "Change: " << change << endl;*/
                    Gtk::MessageDialog *processChange= new Gtk::MessageDialog{"Here's your Coke and your Change:",true,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
                    processChange->set_secondary_text(change,true);
                    processChange->run();
                    processChange->close();
                    delete processChange;
				}
				else if (action == 2)
				{
					                /* Insufficient amount Message Dialog box*/

                    Gtk::MessageDialog *outOfCoke= new Gtk::MessageDialog{"Coke is Currently out of stock",true,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
                    outOfCoke->set_secondary_text("returning payment...",true);
                    outOfCoke->run();
                    outOfCoke->close();
                    delete outOfCoke;
				}
				else if (action == 4)
				{
					             /* Insufficient amount Message Dialog box*/

                    Gtk::MessageDialog *insufficientAmount= new Gtk::MessageDialog{"Insufficient amount",true,Gtk::MESSAGE_WARNING,Gtk::BUTTONS_OK,false};
                    insufficientAmount->set_secondary_text("returning payment...",true);
                    insufficientAmount->run();
                    insufficientAmount->close();
                    delete insufficientAmount;

				}
				else if (action == 5)
				{
                                            /*Exact Change Message Dialog Box*/

                    Gtk::MessageDialog *exactAmount= new Gtk::MessageDialog{"Thank you for exact change",true,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
                    exactAmount->set_secondary_text("Here's your Coke",true);
                    exactAmount->run();
                    exactAmount->close();
                    delete exactAmount;
				}
				else
				{
                                        /* Insufficient change Message Dialog box*/

                    Gtk::MessageDialog *insufficientChange= new Gtk::MessageDialog{"insufficient change",true,Gtk::MESSAGE_WARNING,Gtk::BUTTONS_OK,false};
                    insufficientChange->set_secondary_text("returning payment....");
                    insufficientChange->run();
                    insufficientChange->close();
                    delete insufficientChange;
				}
				cout << endl;
				if(setOfCokeMachines[option-1].buyACoke(payment, change, action)==true) // Condition checks to see if user bought a coke before reciept is processed
				{
							                /*Printing the Invoice*/

					if(invoice.count(setOfCokeMachines[option-1].getmachinename()))
					{
						invoiceCounter++;
						invoice[setOfCokeMachines[option-1].getmachinename()]=invoiceCounter;
					}
					else
					{
						invoiceCounter=1;
						invoice[setOfCokeMachines[option-1].getmachinename()]=invoiceCounter;
					}
				}
				else
				{
					cout<<"You didn't buy a coke \n";
				}

				break;
			case 2:
				//cout << "How much product are you adding to the machine? \n";
				//cin>>amountToAdd;
                amountToAdd=AddCoke();
				if (amountToAdd == 0)
				{
					cout << amountToAdd << " is not a valid Entry \n";
				}
				if (setOfCokeMachines[option-1].incrementInventory(amountToAdd) == false)
				{
					cout << "You have exceeded your  machine's max capacity\n";
				}
				else
				{
					cout << "Your Inventory Level is now " << setOfCokeMachines[option-1].getInventoryLevel();
				}
				cout << endl;
				break;
			case 3:
                amountToAdd=AddChange();
				//cin.ignore();

				if (setOfCokeMachines[option-1].IncrementChangeLevel(amountToAdd) == false)
				{
					cout << "Error cannot add Change at this time \n";
				}
				else
				{
					cout << "Change has been Added\n";
					cout << "New  Change Level " << setOfCokeMachines[option-1].getChangeLevel() << endl;
					cout << "Maximum Change Capacity " << setOfCokeMachines[option-1].getMaxChangeCapacity() << endl;
				}
				cout << endl;
				break;
			case 4:
				cout<<setOfCokeMachines[option-1]; // Prints out the inventory for the Coke Machine Selected.
			   /* Gtk::MessageDialog *InfoDisplay= new Gtk::MessageDialog{cout<<setOfCokeMachines[option-1],true,Gtk::MESSAGE_WARNING,Gtk::BUTTONS_OK,false};
                InfoDisplay->run();*/
                break;
			case 5:
				//cout<<"Enter a new Machine name: \n";
				cin.ignore();
                newMachinename=changeMachineName();
				getline(cin, newMachinename);
				//cin>>newMachinename;
				setOfCokeMachines[option-1].setMachineName(newMachinename);
				cout<<"Machine Name has been updated \n";
				cout<<endl;
			break;
			case 6:
				//cout<<"Enter a new Coke Price: \n";
				newCokePrice=altCokePrice();
				setOfCokeMachines[option-1].setCokePrice(newCokePrice);
				cout<<"Coke Price has been updated \n";
				cout<<endl;
			break;
			default:
				cout << "Good Bye \n";
				cout << "Exiting......" << endl;
			}
	} while (choice);

}

		}while(option!=0);

	return 0;
}