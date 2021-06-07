#include <iostream>
#include <fstream>

using namespace std;

struct workers 
{
	long id;
	char name[15];
	float hours;
	float salary;
};

int main()
{
	workers worker;
	ifstream f2("workers.txt");
	
	if (!f2) 
	{
		cout << "could not open the file\n";
		return 0;
	}
	
	f2.read((char*)&worker, sizeof(workers));
	while (!f2.eof()) 
	{
		float salary;
		salary = worker.hours * worker.salary;
		if (worker.hours > 45)
			salary += (worker.hours - 45) * 0.5 * worker.salary;
		cout << worker.name << '\t' << worker.id << "\tsalary: " << salary << endl;

		f2.read((char*)&worker, sizeof(workers));
	}
	f2.close();

	return 0;
}