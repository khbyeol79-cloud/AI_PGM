#include<iostream>
using namespace std;


int main() {
	int a = 5, b = 10, c;
	cout <<"a + b / 3 * 3 = "<< (a + b / 3 * 3) << "\n";
	cout <<"b << 2 = " <<(b << 2) << "\n";
	cout << "a != b = " <<(a != b) << "\n";
	cout << "b % a = " <<(b % a) << "\n";
	cout << "(a > b) ? a : b = " <<((a > b) ? a : b) << "\n";
	cout << "sizeof(a) = " << (sizeof(a)) << "\n";
	cout << "c = a++ = " <<(c = a++) << "\n"; //이후의 c 값
	cout << "a += b = " <<(a += b) << "\n"; //이후의 a 값
	cout << "a & b = " <<(a & b) << "\n";
	cout << "c = (a + b, a - b) = " << (c = (a + b, a - b));
}