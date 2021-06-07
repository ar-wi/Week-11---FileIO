#include <iostream>
#include <fstream>
#include "ClientData.h"

using namespace std;

int main()
{
	try {
		ofstream createFile("credit.dat", ios::binary);
		if (!createFile)
			throw "File could not be created.\n";

		ClientData client;
		for (int i = 0; i < 100; i++)
			createFile.write((char*)&client, sizeof(ClientData));
		
		createFile.close();
	}
	catch (char* msg)
	{
		cout << msg;
	}
}
