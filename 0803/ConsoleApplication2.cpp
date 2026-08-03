#include <iostream>
using namespace std;

class circle {
public:
	int radius;
	double getArea();
};

double circle::getArea() {
	return 3.14 * radius * radius;
}

int main(){
	circle donut;
	donut.radius = 1;
	double area = donut.getArea();
	cout << "donut 면적은 " << area << endl;

	circle pizza;
	pizza.radius = 30;
	area = pizza.getArea();
	cout << "pizza 면적은 " << area << endl;
}