#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include<sstream>
#include <conio.h>

using namespace std;
class Node
{
private:
	int SMS;
	int calls;
	int price;
	int serial;
	int othernetworkminutes;
	string name;
	string data;
	string validity;
	string obj;
	Node* next;
	Node* prev;
	Node* nextnode;


public:
	void setname(string N)
	{
		name = N;
	}
	void setdata(string D)
	{
		data = D;
	}
	void setSMS(int S)
	{
		SMS = S;
	}
	void setserial(int serial)
	{
		this->serial = serial;
	}
	void setcalls(int c)
	{
		calls = c;
	}
	void setothernetworkminutes(int ONM)
	{
		othernetworkminutes = ONM;
	}
	void setprice(int p)
	{
		price = p;
	}
	void setvalidity(string v)
	{
		validity = v;
	}
	void setnext(Node* n)
	{
		next = n;
	}
	void setprev(Node* p)
	{
		prev = p;
	}
	string getname()
	{
		return name;
	}
	string getdata()
	{
		return data;
	}
	int getSMS()
	{
		return SMS;
	}
	int getserial()
	{
		return serial;
	}
	int getcalls()
	{
		return calls;
	}
	int getothernetworkminutes()
	{
		return othernetworkminutes;
	}
	int getprice()
	{
		return price;
	}
	string getvalidity()
	{
		return validity;
	}
	Node* getnext()
	{
		return next;
	}
	Node* getprev()
	{
		return prev;
	}
	void set(string obj)
	{
		this->obj = obj;
	}
	string get()
	{
		return obj;
	}
	void setNext(Node* nextnode)
	{
		this->nextnode = nextnode;
	}
	Node* getNext()
	{
		return nextnode;
	}
};

class sim
{
private:
	Node* head;
	Node* current;
	Node* lastCurrent;
	Node* last;
	int size;
	int cb;
	int r;
	Node* front;
	Node* rear;
	int p1, p2, p3, p4, total;

public:
	sim()
	{
		head = NULL;
		current = NULL;
		lastCurrent = NULL;
		last = NULL;
		front = NULL;
		rear = NULL;
		size = 0;
	}
	void Add(int serial, string N, string D, int S, int C, int ONM, int p, string v)
	{
		Node* temp = new Node;
		temp->setserial(serial);
		temp->setname(N);
		temp->setdata(D);
		temp->setSMS(S);
		temp->setcalls(C);
		temp->setothernetworkminutes(ONM);
		temp->setprice(p);
		temp->setvalidity(v);
		if (head == NULL)
		{
			head = temp;
			current = temp;
			lastCurrent = temp;
			last = temp;
			last->setnext(NULL);
			last->setprev(NULL);

		}
		else
		{
			current->setnext(temp);
			temp->setprev(current);
			current = temp;
			last = temp;
			lastCurrent = current->getprev();
			last->setnext(NULL);
		}
		size++;
	}

	void update()
	{
		int target_serial;
		int sms,onNetMin,offNetMin,price;
		string name,validity,mbs;
		cout << "Enter Package Serial you want to edit:" << endl;
		cin>>target_serial;
		cin.ignore();
		current = head;
		for (int i = 0; i < size; i++)
		{
			if (target_serial== current->getserial())
			{
				cout << "Enter new name:" << endl;
				getline(cin, name);
				current->setname(name);
				cout << "Enter no of mbs: " << endl;
				getline(cin, mbs);
				current->setdata(mbs);
				cout << "enter amount of sms: " << endl;
				cin >> sms;
				current->setSMS(sms);
				cout << "enter amount of local call minutes: " << endl;
				cin >> onNetMin;
				current->setcalls(onNetMin);
				cout << "enter amount of other network minutes: " << endl;
				cin >> offNetMin;
				current->setothernetworkminutes(offNetMin);
				cout << "enter validity of the package:" << endl;
				cin.ignore();
				getline(cin, validity);
				current->setvalidity(validity);
				cout << "Enter new price for this package: " << endl;
				cin >> price;
				current->setprice(price);
				break;
			}
			current = current->getnext();
		}
		// Open the file in input mode
	  	ifstream fin("Packages List.txt");
		string line;
	  	bool found = false;
	  	int count=0;
		while (getline(fin, line)) {
		    if (line.find("Package Serial:") != string::npos) {
		      int serial;
		      sscanf(line.c_str(), "Package Serial: %d", &serial);
		      if (serial == target_serial && !found) {
		        found = true;
		      }
		    } 
			else if (line.find("Package Name:") != string::npos && found&&count<7) {
		      line = "Package Name: "+name;
		      count++;
		    } 
			else if (line.find("Data:") != string::npos && found&&count<7) {
		      count++;
			  line = "Data: "+mbs+" mbs";
		    }
		    else if (line.find("validity:") != string::npos && found&&count<7) {
		      count++;
			  line = "validity: "+validity;
		    }
			else if (line.find("sms:") != string::npos && found&&count<7) {
				stringstream ss;ss<<sms;string s;ss>>s;
		     	line = "sms: "+s;
		      	count++;
		    } 
			else if (line.find("local call minutes:") != string::npos && found&&count<7) {
		      count++;
		      stringstream ss;ss<<onNetMin;string s;ss>>s;
			  line = "local call minutes: "+s;
		    } 
			else if (line.find("other network minutes:") != string::npos && found&&count<7) {
		      count++;
		      stringstream ss;ss<<offNetMin;string s;ss>>s;
			  line = "other network minutes: "+s;
		    } 
			else if (line.find("price:") != string::npos && found&&count<7) {
		      count++;
		      stringstream ss;ss<<price;string s;ss>>s;
			  line = "price: "+s;
		    }
			
		    // Write the updated data to a temporary file
		    ofstream fout("Packages_Temp.txt", ios::app);
		    fout << line << endl;
		    fout.close();
		  }
		  // Close the ifstream object
		  fin.close();
		  remove("Packages List.txt");
		  rename("Packages_Temp.txt", "Packages List.txt");
		  
		  if(!found){
		  	cout<<"No Package Found with this Serial Number, Try Again Later\n"<<endl;
		  }
		  
		  
	}

	void adminmenu()
	{
		cout << "Please select any option: " << endl;
		cout << "1) Add new offers " << endl;
		cout << "2) Delete offers " << endl;
		cout << "3) Update offers " << endl;
		cout << "4) Display offer list" << endl;
		cout << "5) Suggesstion centre" << endl;
		cout << "6) Exit " << endl;
		cout << "=> ";
	}
	void loginmenu()
	{	
		cout << "------------------    MENU   ----------------------\n";
		cout << "    Welcome to User Login and Registration page    \n";
		cout << "---------------------------------------------------\n";
		cout << "                                                 \n\n";
		cout << "Press 1 to login               " << endl;
		cout << "Press 2 to Register            " << endl;
		cout << "Press 3 to Reset Password      " << endl;
		cout << "Press 4 to exit                " << endl;
		cout << "\nplease enter your choice";

		cout << "=> ";
	}
	void customermenu()
	{
		cout << endl<<endl;
		cout << "Please select any option: " << endl;
		cout << "1) Current balance " << endl;
		cout << "2) Recharge balance " << endl;
		cout << "3) Avail offer " << endl;
		cout << "4) Customize package " << endl;
		cout << "5) Feedback " << endl;
		cout << "0) Exit" << endl;
		cout << "=>";
	}

	void balance(string name)
	{		
		string fileName = name + ".txt";
		ifstream file(fileName.c_str());
		file>>cb;
		file.close();
		cout<<"Your Current Balance is: "<<cb;
	}
	
	void updateBalance(string name)
	{	
		string fileName = name + ".txt";
		ofstream bal(fileName.c_str());
		bal << cb;
		bal.close();
	}

	void recharge(string file)
	{
		cout << endl;
		cout << "Enter amount you want to recharge: ";
		cin >> r;
		cb = cb + r;
		cout << endl << "balance after recharging is: ";
		cout << cb << endl;
		updateBalance(file);
		
	}
	void del()
	{
		int k = size;
		int s;
		bool del = false;
		Node* temp = head;
		current = head;
		if (current == NULL)
		{
			cout << "List for delete is Empty" << endl;
		}
		else
		{
			cout << "Enter The serial that you want to Delete : ";
			cin >> s;

			if (s == current->getserial() && current->getprev() == NULL)
			{
				lastCurrent = current;
				current = current->getnext();
				delete lastCurrent;
				current->setprev(NULL);
				head = current;
				cout << "\n deleted \n";
				del = true;
			}
			else
			{
				for (int i = 0; i < size; i++)
				{

					if (s == current->getserial() && current->getnext() == NULL)
					{
						lastCurrent = current->getprev();
						lastCurrent->setnext(NULL);
						delete current;
						cout << "Deleted successfully" << endl;
						size--;
						del = true;
					}

					else if (s == current->getserial())
					{
						temp = current->getnext();
						lastCurrent = current->getprev();
						lastCurrent->setnext(current->getnext());
						temp->setprev(lastCurrent);
						delete current;

						cout << "Deleted successfully" << endl;
						size--;
						del = true;
					}


					current = current->getnext();


				}

			}
			if (!del)
			{
				cout << "\n no such offer exists. \n";
				cout << endl;
			}
		}
			int count=0;
		  ifstream fin("Packages List.txt");
		  string line;
		  bool found = false;
		  
		  while (getline(fin, line)) {
		    if (line.find("Package Serial:") != string::npos) {
			      int serial;
			      sscanf(line.c_str(), "Package Serial: %d", &serial);
			      if (serial == s) 
				  {
			        found = true;
			      } 
				  else 
				  {
			        // Write the data to the temporary file
			        ofstream fout("packages_temp.txt", ios::app);
			        fout << line << endl;
			      }
		    } else if (found && count<8) {
		      	count++;
		    } else {
		      // Write the data to the temporary file
		      ofstream fout("packages_temp.txt", ios::app);
		      fout << line << endl ;
		    }
		  }
		
		  // Close the input file
		  fin.close();
		
		  // Replace the original file with the temporary file
		  remove("Packages List.txt");
		  rename("packages_temp.txt", "Packages List.txt");

	}


	void Display_List()
	{
		Node* temp = new Node;
		temp = head;
		if (head != NULL)
		{
			cout << endl;
			cout << "\n\t\t\t Offers are: \n\n";
			do
			{
				cout << "\t\t\t  ............  " << endl;
				cout << "package serial: " << temp->getserial() << endl;
				cout << "package name: " << temp->getname() << endl;
				cout << "data: " << temp->getdata() << endl;
				cout << "sms: " << temp->getSMS() << endl;
				cout << "local call minutes: " << temp->getcalls() << endl;
				cout << "other network minutes: " << temp->getothernetworkminutes() << endl;
				cout << "validity: " << temp->getvalidity() << endl;
				cout << "price: " << temp->getprice() << endl;
				temp = temp->getnext();
			} while (temp->getnext() != NULL);
			
			cout << "\t\t\t  ............  " << endl;
			cout << "package serial: " << temp->getserial() << endl;
			cout << "package name: " << temp->getname() << endl;
			cout << "data: " << temp->getdata() << endl;
			cout << "sms: " << temp->getSMS() << endl;
			cout << "local call minutes: " << temp->getcalls() << endl;
			cout << "other network minutes: " << temp->getothernetworkminutes() << endl;
			cout << "validity: " << temp->getvalidity() << endl;
			cout << "price: " << temp->getprice() << endl;
			temp = temp->getnext();
		}
		else
		{
			cout << "\n\t\t\tYour List is Empty\n";
		}
		cout << endl << endl;
	}
	
	void calculate(int offer,string number)
	{
		bool flag;
		bool test;
		int a;
		balance(number);
		Node* temp = head;

		if (head == NULL)
		{
			cout << "Empty List" << endl;
		}
		else
			for (int i = 0; i < size; i++)
			{
				if (offer == temp->getserial())
				{
					flag = true;

					if (cb >= temp->getprice())
					{
						cout << "\ncongratulations, offer availed... ";
						cout << "\n\noffer Name  : " << temp->getname();
						a = temp->getprice();
						cb = cb - a;
						cout << "\nRemaining balance: " << cb << endl;
						updateBalance(number);
						test = true;
					}
					else
					{
						test = true;
						cout << "Insufficient balance, please recharge it.." << endl;
					} 
				}
				else flag = false;


				temp = temp->getnext();
			}

		if (!flag && !test)
		{
			cout << "\n Invalid Subscription Serial.\n";
		}

	}


	void mainmenu()
	{
		cout << " ****************************************************************** " << endl;
		cout << "                          Sim Packages System                         " << endl;
		cout << " ****************************************************************** " << endl<<endl;
		cout << " Select an Option \n"<< endl;
		cout << " 1) Admin Section " << endl;
		cout << " 2) Customer Section " << endl;
		cout << " 3) Exit " << endl;
		cout << " => ";
		
	}


	void equeue(string obj,int a)
	{
		
		Node* newnode = new Node();
		newnode->set(obj);
		if (front == NULL)
		{
			newnode->setNext(NULL);

			front = newnode;

			rear = newnode;
			if(a==1)
			cout<<"Thank you for your valueable feedback\n";
		}
		else {
			newnode->setNext(NULL);

			rear->setNext(newnode);

			rear = newnode;
			if(a==1)
			cout<<"Thank you for your valueable feedback\n";
		}
		
		if (a==1){
			ofstream feed("Feedbacks.txt",ios::app);
			feed<<obj<<endl;
			feed.close();
			cout<<"We appreciate it."<<endl;
		}
		
		
	}

	void dequeue()

	{
		if (front != NULL)
		{

			string obj = front->get();
			
			Node* p = front;
			if (front->getNext() != NULL)
				front = front->getNext();
			else
				cout << "No more feedback to dequeue now..." << endl;
			
			delete p;

			cout << "feedback dequeued.." << endl;
			cout << "dequeued: " << obj << endl;
		}
		else
			cout << "no feedback to dequeue..." << endl;
		
		ifstream fin("Feedbacks.txt");
		string line;
		bool read = true;
		while (getline(fin, line)) {
		if (read) {
		    read = false;
		}
		else
		{
		    ofstream fout("feed_temp.txt", ios::app);
		    fout << line << endl;
		}
		}
		fin.close();
		remove("Feedbacks.txt");
		rename("feed_temp.txt", "Feedbacks.txt");
	}

	void display()
	{	
		int count=0;
		Node* temp = front;
		while (temp != NULL)
		{	count++;
			cout << count<<". " <<temp->get() << endl;
			temp = temp->getNext();
		}

	}
	
	void customize(int data, int SMS, int calls, int othernetworkminutes, int validity,string number)
	{
		p1 = data * 3;
		p2 = SMS * 2;//10
		p3 = calls * 10;//50
		p4 = calls * 20;
		int subscribe;
		if (validity = 1)
		{
			total = p1 + p2 + p3 + p4;
		}
		if (validity = 7)
		{
			total = (p1 + p2 + p3 + p4) + 50;
		}
		else if (validity = 15)
		{
			total = (p1 + p2 + p3 + p4) + 100;
		}
		else if (validity = 30)
		{
			total = (p1 + p2 + p3 + p4) + 150;
		}
		
		cout<<"This offer costs : "<<total<<endl;
		cout<<"To subscribe Enter 1 |or| To exit Enter 0 => ";
		cin>>subscribe;
		
		while(subscribe<0||subscribe>1){
			cout<<"Wrong Input, Press 1 to Subscribe and 0 to Exit =>";
			cin>>subscribe;
		}
		
		if (cb >= total && subscribe==1)
		{
			cout << "\nCongratulations! Offer Subscribed Successfully." << endl;
			cb = cb - total;
			cout << "Current Balance: " << cb;
			updateBalance(number);
		}
		else if (cb<total && subscribe==1){
			cout << "\nInsufficient Balance... Please Recharge your Account." << endl;
		}
	}
};

void readPackagesList(sim& s){
	ifstream file("Packages List.txt");
	string line;
	string pkg_name,data,validity;
	int serial,sms,onNetMin,offNetMin,price;
	int count=0;
	while(getline(file,line)){
		size_t pos = line.find(':');
		if(pos!=string::npos){
			string value = line.substr(pos+2);
			count=0;
			if(line.find("Package Serial")==0){
				serial = atoi(value.c_str());
			}
			else if(line.find("sms")==0){
				sms = atoi(value.c_str());
			}
			else if(line.find("local call minutes")==0){
				onNetMin = atoi(value.c_str());
			}
			else if(line.find("other network minutes")==0){
				offNetMin = atoi(value.c_str());
			}
			else if(line.find("price")==0){
				price = atoi(value.c_str());
			}
			else if(line.find("Package Name")==0){
				pkg_name = value;
			}
			else if(line.find("Data")==0){
				data = value+" mbs";
			}
			else if(line.find("validity")==0){
				validity = value;
			}	
		}
		else if(count<1){
			s.Add(serial,pkg_name,data,sms,onNetMin,offNetMin,price,validity);
			count++;
		}
		
		
	}
	file.close();
}

void readFeedbacks(sim& s){
	ifstream feed("Feedbacks.txt");
	string line;
	while(getline(feed,line)){
		s.equeue(line,0);
	}
	feed.close();	
}

void customerPage(sim s,string number){
	int option1;
	int offer;
	string f;
	string Da, Na, v;
	int S, Sa, Ca, ONMa, p;
	int net; int days;
		while (1)
			{	
				
				s.customermenu();
				cin >> option1;
				cin.clear();
				cin.ignore();
				system("cls");
				if (option1 == 0)
					break;
	
				switch (option1)
				{
				case 1:
					s.balance(number);
					break;
				case 2:
					s.recharge(number);
					break;
				case 3:
				{
					s.Display_List();
					cout << "Enter The subscription serial that you want to avail : ";
					cin >> offer;
					s.calculate(offer,number);
					break;
				}
				case 4:
					cout << "ENTER THE DATA:" << endl;
					cin >> net;
					cout << "ENTER THE SMS:" << endl;
					cin >> Sa;
					cout << "ENTER THE ON-NET-MINUTES:" << endl;
					cin >> Ca;
					cout << "ENTER THE OTHER-NETWORK:" << endl;
					cin >> ONMa;
					cout << "ENTER VALIDITY OF THE PACKAGE as per day:" << endl;
					cin >> days;
					s.customize(net, Sa, Ca, ONMa, days,number);
					break;
					
				case 5:
				{
					cout << "please give your feedback: " << endl;
					getline(cin, f);
					s.equeue(f,1);
					break;
				}
				
				default:
					cout << "Invalid input!Please enter a valid input." << endl;
					break;
				}
					
			}
}

bool authenticate(string number, string password) {
  ifstream file("credentials.txt");
  string num,pass,skip;
  size_t Pos;
  while (getline(file, num)&&getline(file,pass)&&getline(file,skip)) {
    Pos = num.find(":");
    num = num.substr(Pos + 2,8);
    Pos = pass.find(":");
    pass = pass.substr(Pos + 2);	
    pass = pass.substr(0, pass.find_last_not_of(" ") + 1);
    if (num == number && pass == password) {
      return true;
    }
  }
  return false;
}

bool checkRegistered(string number){
	ifstream file("credentials.txt");
	string num,pass,skip;
	size_t Pos;
  	while (getline(file, num)&&getline(file,pass)&&getline(file,skip)) {
    Pos = num.find(":");
    num = num.substr(Pos+2);
    num = num.substr(0, num.find_last_not_of(" ") + 1);
    if (num == number) {
    	file.close();
      return false;
    }
  }
  file.close();
  return true;
}

bool resetPassword(string number,string password){
	ifstream file("credentials.txt");
	bool found;
	string num,pass,skip;
	size_t Pos;
  	while (getline(file, num)&&getline(file,pass)&&getline(file,skip)) {
    Pos = num.find(":");
    string num1 = num.substr(Pos+2);
    num1 = num1.substr(0, num1.find_last_not_of(" ") + 1);
    if (num1 == number) {
    	found=true;
    	ofstream out("cred_temp.txt",ios::app);
    	out<<"Number: "<<number<<endl;
    	out<<"Password: "<<password<<endl<<endl;
    	out.close();
    }
    else {
    	ofstream out("cred_temp.txt",ios::app);
    	out<<num<<endl<<pass<<endl<<endl;
    	out.close();
	}	
  }
  
  file.close();
  remove("credentials.txt");
  rename("cred_temp.txt","credentials.txt");
  return found;
}


int main()
{
	sim s;
	int flag = 0;	int offer;
	int cb, r;
	string f;
	string Da, Na, v;
	int S, Sa, Ca, ONMa, p;
	int net; int days;
	string myPhone,myPass;
	
	readPackagesList(s);
	readFeedbacks(s);
	
	while (1)
	{
		cout << "\n\t    ***** Welcome to Sim Packages Application *****" << endl << endl;
		s.mainmenu();
		int choice;
		cin >> choice;
		while(choice>3||choice<1)
		{
			cout << "Wrong input! Please enter valid input" << endl;
			cout<<"=>";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		
		system("cls");
			
		switch (choice)
		{
			case 1:
			{
				while (1)
				{
					string pass;
					cout <<endl<< "Please Enter Password to Login to Admin Portal " << endl<<"=> ";
					char ch;
  					while ((ch = getch()) != '\r') {  // '\r' represents the Enter key
    					pass += ch;
    					cout<<"*";
  					}
					system("cls");
					
					if (pass == "0000")
					{	
						
						int w = 786;
						string N, D;
						string name;
						int S, C, ONM;
						int option;
						char ch;
						while (1)
						{
							s.adminmenu();
							cin >> option;
							cin.clear();
							cin.ignore();
							
							system("cls");
							if (option == 6)
							{	
								flag=1;
								break;
							}	
	
							switch (option)
							{
							case 1:
							{
								ofstream outfile("Packages List.txt",ios_base::app);
								cout << "ENTER SERIAL NO:" << endl;
								cin >> S;
								outfile<<"Package Serial: "<<S<<endl;
								cout << "ENTER THE NAME:" << endl;
								cin.ignore();
								getline(cin, Na);
								outfile<<"Package Name: "<<Na<<endl;
								cout << "ENTER THE DATA:" << endl;
								cin >> Da;
								outfile<<"Data: "<<Da<<endl;
								cout << "ENTER THE SMS:" << endl;
								cin >> Sa;
								outfile<<"sms: "<<Sa<<endl;
								cout << "ENTER THE ON-NET-MINUTES:" << endl;
								cin >> Ca;
								outfile<<"local call minutes: "<<Ca<<endl;
								cout << "ENTER THE OTHER-NETWORK:" << endl;
								cin >> ONMa;
								outfile<<"other network minutes: "<<ONMa<<endl;
								cout << "ENTER THE PRICE OF THIS PACKAGE:" << endl;
								cin >> p;
								outfile<<"price: "<<p<<endl;
								cout << "ENTER VALIDITY OF THE PACKAGE:" << endl;
								cin.ignore();
								getline(cin, v);
								outfile<<"validity: "<<v<<endl;
								outfile<<endl;
								outfile.close();
								s.Add(S,Na,Da,Sa,Ca,ONMa,p,v);
								break;
							}
							case 2:
							{
								s.del();
	
								break;
							}
							case 3:
							{
								s.update();
								break;
							}
	
							case 4:
							{
								s.Display_List();
								break;
							}
							case 5:
							{
								int feed;
								cout << "feedback by customers:" << endl;
								s.display();
								cout << "Press 1 for eliminating the feedback notification: " << endl;
								cout<<" Enter 0 to exit\n";
								cin >> feed;
								if (feed == 1)
								{
									s.dequeue();
									cout<<endl<<endl;
								}
								if (feed !=1)
									system("cls");
								break;
							}
	
							default:
								cout << "Wrong input. Please enter valid input \n" << endl;
								break;
							}
						}
					}
					else if (pass != "0000" && pass != "0")
						cout << "Wrong Password... Try again or Enter 0 to exit" << endl;
					else 
						break;
					if (flag == 1)
						break;
				}
				break;
			}
			case 2:
			{
				while(1)
				{
					string phone;
					string pass;
					int select;
					string key;					
					do{	
						system("cls");
						s.loginmenu();
						cin>>select;
						cin.clear();
						cin.ignore();
					}while(select<1||select>4);
						
						if(select==4){
							break;
						}
					switch(select){
						case 1:
						{
							while(1){
								cout<<"Enter Phone No : 0200-";
								cin>>phone;
								cout<<"Enter your password : ";
								pass="";
								char ch;
			  					while ((ch = getch()) != '\r') {  // '\r' represents the Enter key
			    					pass += ch;
			    					cout<<"*";
			  					}
			  					cout<<"\nPassword Entered: "<<pass<<endl;
								bool found = authenticate(phone,pass);
								if(found){
									system("cls");
									customerPage(s,phone);
									key="0";
								}
								else{
									cout<<"\nUser or Password Not Matched\n";
									cout<<"\nEnter 1 to Re-Try or 0 to Exit=>";
									cin>>key;
								}
								system("cls");
								if(key=="0")
									break;
							}
						}
							break;
						case 2:
						{	
							while(1){
								bool set = true;
								string tempPhone;
								do{	
									set = true;
									cout<<"\nEnter Phone No.: 0200-";
									cin>>tempPhone;
									if(tempPhone.length()!=7){
										cout<<"Length must be 7-Digits";
										set = false;
									}
									else
										for(int i=0;i<tempPhone.length();i++){
											char c = tempPhone[i];
											if(c<48||c>57){
												cout<<"Entered Number is Not Valid";
												set = false;
											}		
										}
								}
								while(!set);
								
								myPhone=tempPhone;
								
								set=checkRegistered(myPhone);
								
								if(set){
									cout<<"Enter Password: ";
									cin>>myPass;
									ofstream file("credentials.txt",ios::app);
									file<<"Number: "<<myPhone<<endl;
									file<<"Password: "<<myPass<<endl<<endl;
	
									cout<<"User Creation Successfull"<<endl;
									string fileName = myPhone + ".txt";
									ofstream bal(fileName.c_str());
									bal<<50;
									bal.close();
									cout<<"Rs.50 Reward Balance added to Your account"<<endl;
									cout<<"\nEnter 1 to add new user and 0 to exit=>";
									cin>>key;
									if(key=="0")
										break;
								}
								else
									cout<<"User Already Registered"<<endl;
							}
							system("cls");
						}
							break;
						case 3:
							string tempPhone,newPass;
							cout<<"Enter your Phone No.: 0200-";
							cin>>tempPhone;
							cout<<"Enter New Password: ";
							cin>>newPass;							
							bool found = resetPassword(tempPhone,newPass);
							
							if(found){
								
								cout<<"Password Updated Successfully"<<endl;
							}
							else{
								cout<<"User Not Found";
								cout<<"\nEnter 1 to Re-Try or 0 to Exit=>";
							}
							
							if(found)
								cout<<"Enter 0 to Exit=>";
							cin>>key;
							system("cls");
							if(key=="0")
								break;
					}
				}
				break;
			}
			case 3:
			{
				cout << "Thank You" << endl;
				return 0;
			}
		}
	}
}
 


