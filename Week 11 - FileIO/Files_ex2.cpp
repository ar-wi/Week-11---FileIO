#include <iostream>
#include <fstream>
#include<string>

using namespace std;

int main()
{
	string fname, lname;
	int age;

	ifstream in("grades.txt", ios::in);

	if (!in)
	{
		cout << "could not open file.\n";
		return 0;
	}
	while (in >> fname >> lname >> age)
	{
		cout << fname << ' ' << lname;
		if (age > 20)
			cout << " can work" << endl;
		else
			cout << " can’t work" << endl;
	}
	return 0;
}