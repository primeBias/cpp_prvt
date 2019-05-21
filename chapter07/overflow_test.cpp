#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;

double subtract(int a, int b);

double add(int a, int b)
{
	double ret = 0;
	// cout << a << "\t" << b << endl;
	// cout << numeric_limits<int>::max()<< endl;
	if (b < 0)
		ret = subtract(a,-b);
	else if (a > numeric_limits<int>::max() - b)
	{
		// cout << a << "\t" << b << endl;
		// cout << a+b << endl;
		// cout << numeric_limits<int>::max() - b << endl;
		throw runtime_error("add(): overflow error.");
	}
	ret = a + b;
	
	return ret;
}

double subtract(int a, int b)
{
	double ret = 0;
	if (b < 0)
		ret = add(a,-b);
	else if (a < numeric_limits<int>::min() + b)
		throw runtime_error("subtract(): underflow error.");
	
	return a - b;
}

int main()
{
	double t1 = add(10,200);
	double t2 = add(10,-200);
	double t3 = subtract(10,5);
	double t4 = subtract(10,-200);
	// double t5 = subtract(-2147483647,99999999);
	double t6 = subtract (9999, -2147483647);
	vector<double> answers {t1,t2,t3,t4,t6};

	for (double x : answers)
		cout << x << endl;
}
