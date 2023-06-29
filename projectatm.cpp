#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;

class account_query
{
private:
    char account_number[20];
    char firstName[10];
    char lastName[10];
    float total_Balance;
    char username[100],rei;
    int password,card;
public:
	void insert_card();
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void edit_rec();
    void deposit();
    void withdrawl();
    void login();
    void mainmenu();
};

void account_query :: insert_card(){
	cout<<"Please Insert your card \n\nPress 1 to Insert : ";
	cin>>card;
	if(card==1){
		system("cls");
		login();
		system("cls");
		mainmenu();
	}
	else{
		system("cls");
		cout<<"\nSORRY !!!!\n\nCard is not working";
		cout<<"\nDo you want to Re-enter the card 'Y/N' : ";
		cin>>rei;
		system("cls");
		if(rei=='Y'||rei=='y'){
			insert_card();
		}
		else{
			cout<<"THANK YOU";
		}
	}
}

void account_query::login(){
	cout<<"Enter Password : ";
	cin>>password;
	if(password==1234){
		cout<<"Welcome";
	}
	else{
		cout<<"Wrong Password "<<endl;
		login();
	}
}
void account_query::read_data()
{
    cout<<"\nEnter Account Number: ";
    cin>>account_number;
    cout<<"Enter First Name: ";
    cin>>firstName;
    cout<<"Enter Last Name: ";
    cin>>lastName;
    cout<<"Enter Balance: ";
    cin>>total_Balance;
    cout<<endl;
}

void account_query::show_data()
{
    cout<<"Account Number: "<<account_number<<endl;
    cout<<"First Name: "<<firstName<<endl;
    cout<<"Last Name: "<<lastName<<endl;
    cout<<"Current Balance: Rs.  "<<total_Balance<<endl;
    cout<<"-------------------------------"<<endl;
}

void account_query::write_rec()
{
    ofstream outfile;
    outfile.open("record.dat", ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}

void account_query::read_rec()
{
    ifstream infile;
    infile.open("record.dat", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_data();
        }
    }
    infile.close();
}

void account_query :: deposit() // Takes bal variable from bank class and keeps it as a constant total, deposit adds to bal
{
   ofstream balance1;
   balance1.open("transaction.txt");
   ofstream outfile;
   outfile.open("record.dat", ios::binary);
   long deposit;
   cout << "Enter how much you would like to deposit: ";
   cin >> deposit;
   total_Balance = deposit+total_Balance;
   outfile.write(reinterpret_cast<char*>(this), sizeof(*this));
   balance1<< total_Balance << endl;
   cout << "You have deposited: $" << deposit << endl;
	balance1.close();
	outfile.close();
}

void account_query :: withdrawl() // Similar to deposit, but subtracts from bal.
{
	ofstream balance1;
	balance1.open("transaction.txt");
    ofstream outfile;
	outfile.open("record.dat", ios::binary);
    long withdraw;
    cout << "Enter how much you would like to withdraw: ";
    cin >> withdraw;
    if (total_Balance > withdraw || total_Balance==withdraw){
    total_Balance= total_Balance - withdraw;
    outfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    balance1<< total_Balance << endl;
    cout << "You have withdrawn: $" << withdraw << endl;
	}
    else if (total_Balance < withdraw)
    cout << "You don't have enough funds to cover your withdraw request!" << endl;
    balance1.close();
    outfile.close();
}

void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.dat", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.dat", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}

void account_query:: mainmenu()
{
    account_query A;
    int choice;
    cout<<"***Acount Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        //cout<<"\n\t1-->Add record";
        cout<<"\n\t1-->Show record";
        cout<<"\n\t2-->Update Record";
        cout<<"\n\t3-->Deposit balance";
        cout<<"\n\t4-->Withdraw balance";
        cout<<"\n\t5-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
        	A.login();
            A.read_rec();
            break;
        case 2:
            A.edit_rec();
            break;
        case 3:
        	A.login();
            A.deposit();
            break;
        case 4:
        	A.login();
            A.withdrawl();
            break;
        case 5:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    //system("pause");
}

int main(){
	account_query a;
	int op1;
	char ch;
	do{
		cout<<"*********************\n";
		cout<<"*    ATM SYSTEM     *\n";
		cout<<"*********************\n";
		cout<<"1. ADD RECORD \n2. INSERT CARD\n";
		cout<<"Enter your choice : ";
		cin>>op1;
		switch(op1){
			case 1:
            	a.write_rec();
				break;
			case 2:
				a.insert_card();
				break;
			default : cout<<"Invalid operator";
		}
		cout<<"Do you want to continue ? ";
		cin>>ch;
		system("cls");
	}while(ch=='y'||ch=='Y');
	if(ch=='n'){
		main();
	}
	
}
