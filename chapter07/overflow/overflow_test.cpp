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


string to_str_with_precision(double d)
{
	ostringstream out;
	out.precision(15);
	out << d;
	string ret = out.str();
	return ret;
}

string remove_trailing_zero(string temp)
{
	char c_del = '0';
	int index = temp.size();
	while (c_del == '0')
	{
		c_del = temp[index-1];
		cout << "c_del= " << c_del << endl;
		if (c_del == '0')
			temp.erase(index-1);
		cout << "temp= " << temp << endl;
		--index;
	}

	return temp;
}

vector<int> remove_decimals(double x)
{
	string temp;
	char ch;
	bool dec_flag = false;
	int dec_places = 0;
	vector<int> ret;
	
	temp = to_str_with_precision(x);
	temp = remove_trailing_zero(temp);
	putback_str(temp);

	temp = "";

	while (cin.get(ch) && (isdigit(ch) || ch == '.' || ch == '-'))
	{
		if (ch == '.') { dec_flag = true; }
		else 
		{
			temp += ch;
			if (dec_flag)
				dec_places += 1;
		}
	}

	putback_str(temp);
	int res;
	cin >> res;
	cout << "res= " << res << endl;
	cout << "temp= " << temp << endl;
	ret.push_back(res);
	ret.push_back(dec_places);

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return ret;
}

double add_decimals(int x, int decimal_places)
{
	double ret = 1.0 * x;
	for (int i = 0; i < decimal_places; ++i)
	{
		ret /= 10;
	}

	return ret;
}

double divide_with_precision(double a, double b)
{
	int decimal_places = 0;
	int final_res;

	vector<int> temp_a = remove_decimals(a);
	vector<int> temp_b = remove_decimals(b);

	decimal_places = temp_a[1] - temp_b[1];

	vector<int> res = divide(temp_a[0], temp_b[0]);
	final_res = res[0];

	for (int i = 0; i < 8; ++i)		// 8 digits of precision
	{
		if (res[1] != 0)			// if remainder is not 0
		{
			res = divide(res[1]*10, temp_b[0]);
			decimal_places += 1;
			final_res *= 10;
			final_res += res[0];
		}
	}

	return add_decimals(final_res, decimal_places);
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
		double d = add_decimals(1234567, 4);
		cout << "d= " << setprecision(15) << d << endl;
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
