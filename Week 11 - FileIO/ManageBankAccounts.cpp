// Methods of fstream:
/*
open
read
write
eof
clear
seekp
seekg
tellp
tellg
*/

#include <iostream>
#include <fstream>
#include "ClientData.h"

enum Choices
{
	PRINT = 1,
	UPDATE,
	NEW,
	DELETE,
	END
};

size_t getFileSize(fstream& fs)
{
	fs.seekg(0, ios::end); // ios::beg - from beginning of file, ios::end - from file end
	return fs.tellg();
}

int getAccount(const char* const prompt)
{
	int accountNumber;
	do {
		cout << prompt << " (1 - 100): ";
		cin >> accountNumber;
	} while (accountNumber < 1 || accountNumber > 100);
	return accountNumber;
}

int enterChoice()
{
	cout << "\nEnter your choice" << endl
		<< PRINT << " - store a formatted text file of accounts called \"print.txt\" for printing" << endl
		<< UPDATE << " - update an account" << endl
		<< NEW << " - add a new account" << endl
		<< DELETE << " - delete an account" << endl
		<< END << " - end program\n? ";
	int menuChoice;
	cin >> menuChoice;
	return menuChoice;
}

void printRecord(fstream& creditFl)
{
	ofstream outPrintFile("print.txt");
	if (!outPrintFile)
		throw "File could not be created.\n";

	outPrintFile << "Account" << '\t' << "Name" << '\t' << "Balance\n";

	creditFl.seekg(0);
	ClientData client;
	cout << "tellg() returned: " << creditFl.tellg() << endl;
	cout << "tellp() returned: " << creditFl.tellp() << endl;
	creditFl.read((char*)&client, sizeof(ClientData));
	while (!creditFl.eof())
	{
		if (client.getAccountNumber() != 0)
			outPrintFile << client;
		cout << "tellg() returned: " << creditFl.tellg() << endl;
		cout << "tellp() returned: " << creditFl.tellp() << endl;
		creditFl.read((char*)&client, sizeof(ClientData));
	}
	outPrintFile.close();
}

void updateRecord(fstream& updateFl)
{
	int num = getAccount("Enter account to update");

	updateFl.seekg((num - 1) * sizeof(ClientData));
	cout << "tellg() returned: " << updateFl.tellg() << endl;
	cout << "tellp() returned: " << updateFl.tellp() << endl;
	ClientData client;
	updateFl.read((char*)&client, sizeof(ClientData));
	if (client.getAccountNumber() != 0) {
		cout << client.getName() << '\t';
		cout << client.getBalance() << endl;
		cout << "\nEnter charge (+) or payment (-): ";
		double transaction;
		cin >> transaction;
		double oldBalance = client.getBalance();
		client.setBalance(oldBalance + transaction);
		updateFl.seekp((num - 1) * sizeof(ClientData));
		cout << "tellg() returned: " << updateFl.tellg() << endl;
		cout << "tellp() returned: " << updateFl.tellp() << endl;
		updateFl.write((char*)&client, sizeof(ClientData));
		cout << "tellp() returned: " << updateFl.tellp() << endl;
	}
	else cout << "Account #" << num << " not exist.\n";
}

void deleteRecord(fstream& deleteFromFl)
{
	int num = getAccount("Enter account to delete");
	deleteFromFl.seekg((num - 1) * sizeof(ClientData));
	ClientData client;
	deleteFromFl.read((char*)&client, sizeof(ClientData));
	if (client.getAccountNumber() != 0) {
		ClientData blankClient;
		deleteFromFl.seekp((num - 1) * sizeof(ClientData));
		deleteFromFl.write((char*)&blankClient,
			sizeof(ClientData));
		cout << "Account #" << num << " deleted.\n";
	}
	else cout << "Account #" << num << " is empty.\n";
}

void newRecord(fstream& addToFl)
{
	int num = getAccount("Enter new account number");
	addToFl.seekg((num - 1) * sizeof(ClientData));
	ClientData client;
	addToFl.read((char*)&client, sizeof(ClientData));
	if (client.getAccountNumber() == 0) {
		char name[15]; double balance;
		cout << "Enter name and balance\n? ";
		cin >> name >> balance;
		ClientData client1(num, name, balance);
		addToFl.seekp((num - 1) * sizeof(ClientData));
		addToFl.write((char*)&client1, sizeof(ClientData));
	}
	else
		cout << "Account #" << num << " already exists\n";
}

int main()
{
	fstream inOutCredit("credit.dat", ios::in | ios::out | ios::binary);
	try {
		if (!inOutCredit)
		{
			throw " could not open file.\n";
		}

		cout << "File size: " << getFileSize(inOutCredit) << " bytes (" <<
			getFileSize(inOutCredit) / sizeof(ClientData) << " records)" << endl;

		int choice;
		while ((choice = enterChoice()) != END)
		{
			switch (choice)
			{
			case PRINT:
				try
				{
					printRecord(inOutCredit);
				}
				catch (char* msg)
				{
					cout << msg;
				}
				break;
			case UPDATE: 
				updateRecord(inOutCredit);
				break;
			case NEW: 
				newRecord(inOutCredit);
				break;
			case DELETE: 
				deleteRecord(inOutCredit);
				break;
			default: cout << "Incorrect choice" << endl;
			}
			inOutCredit.clear(); // reset end-of-file indicator
		}
	}
	catch (char* msg)
	{
		cout << msg;
	}

	inOutCredit.close();

	return 0;
}