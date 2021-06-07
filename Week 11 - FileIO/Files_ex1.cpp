#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
	ifstream f1; 
	ofstream f2;
	char name[10]; 
	float grade;
	
	f1.open("students.txt");	
	if (!f1) 
	{
		cout << "File could not be opened.\n";
		return 0;
	}
	
	f2.open("grades.txt");
	if (!f2) 
	{
		cout << "File could not be opened.\n";
		return 0;
	}

	do 
	{
		f1 >> name;
		cout << "enter " << name << "'s grade ";
		cin >> grade;
		f2 << name << '\t' << grade << endl;
	} while (!f1.eof());
	
	f1.close(); 
	f2.close();

	return 0;
}