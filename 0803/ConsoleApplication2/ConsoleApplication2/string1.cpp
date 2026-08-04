#include<iostream>

using namespace std;

int main() {
	string stdname[3];
	int stdnum[3];

	for (int i = 0; i < 3 ; i++)
	{
		cout << "name : ";
		cin >> stdname[i];

		cout << "stdnum : ";
		cin >> stdnum[i]
			;
	}

	for (int j = 0; j < 3; j++)
	{
		cout << stdname[j] << " - " << stdnum[j] << endl;
	}
}
