#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <math.h>
#include <cmath>
#include <iomanip>
using namespace std;

double subtract(int a, int b);

double add(int a, int b)
{
	double ret = 0;
	cout << "in add()" << endl;
	cout << a << "\t" << b << endl;
	if (b < 0)
	{
		ret = subtract(a,-b);
	}
	else if (a > numeric_limits<int>::max() - b)
	{
		throw runtime_error("add(): overflow error.");
	}
	else
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
	else
		ret = a - b;

	return ret;
}

double multiply(int a, int b)
{
	double ret = 0;
	bool neg = false;
	if ((a < 0 && b > 0) || (a > 0 && b < 0))
	{
		neg = true;
		if (a < 0)
			a = -a;
		if (b < 0)
			b = -b;
	}

	for (int i = 0; i < b; ++i)
	{
		if (ret > numeric_limits<int>::max() - b)
		{
			if (neg == true)
				throw runtime_error("multiply(): underflow error.");
			else
				throw runtime_error("multiply(): overflow error.");
		}
		ret += a;
	}

	if (neg == true)
		ret = -ret;
	return ret;
}

// Performs division and returns a vector (a,b)
// where 'a' is the quotient and 'b' is the remainder.
vector<int> divide(int a, int b)
{
	vector<int> ret;
	int temp = a;
	int answer = 0;
	bool neg = false;
	if ((a < 0 && b > 0) || a > 0 && b <0)
		neg = true;
	do	
	{
		if (temp - b >= 0)
		{
			temp -= b;
			answer += 1;
		}
		else
		{
			ret.push_back(answer);
			ret.push_back(a-answer*b);
			temp -= b;
		}
		
	} while (temp >= 0);


	return ret;
}

void putback_str(string s)
{
	for (int i = s.size(); i >=0; --i)
		cin.putback(s[i]);
}

// code is working for some cases now. does not work for
// .123456789. Casting from double to int seems to cause
// problems.
vector<int> remove_decimals(double x)
{
	int decimal_places = 0;
	vector<int> ret;
	double epsilon = .000001;
	bool neg = false;

	if (x < 0)
	{
		neg = true;
		x = -x;
	}

	int temp = x;
	
	while (x - temp > epsilon)
	{
		x *= 10;
		temp = x;		// casting double to int (removing remainder)
		decimal_places += 1;
		cout << "x= " << setprecision(15) << x << endl;
		cout << "temp= " << setprecision(15) << temp << endl;
		cout << "x - temp= " << x-temp << endl;
		cin.get();
	}

	if (neg == true) temp = -temp;

	ret.push_back(temp);
	ret.push_back(decimal_places);

	return ret;
}

double divide_prec(int a, int b)
{
	int decimal_places = 0;
	return 0;
}


int main()
{
// 	double t1 = add(10,2147483647);
// 	double t2 = add(10,-2147483647);
// 	double t3 = subtract(10,5);
// 	double t4 = subtract(10,-200);
// 	// double t5 = subtract(-2147483647,99999999);
// 	double t6 = subtract (9999, -2147483647);
// 	vector<double> answers {t1,t2,t3,t4,t6};
	while (true) try
	{
		double x;
		cout << ">";
		cin >> x;
		if (!cin)
			throw runtime_error("Invalid input.");
		else
		{
			vector<int> res = remove_decimals(x);
			cout << "number= " << res[0] << "\tdecimals removed= " << res[1] << endl;
		}
		// int x, y;
		// cout << ">" << endl;
		// cin >> x >> y;
		// if (!cin)
		// 	throw runtime_error("Invalid input.");
		// else
		// {
		// 	cout << "x= " << x << '\t' << "y= " << y << endl;
		// 	// double ret = add(x,y);
		// 	// double ret2 = subtract(x,y);
		// 	vector<int> ret = divide(x,y);
		// 	cout << "divide: " << ret[0] << '\t' << ret[1] << endl; 
		// }
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
