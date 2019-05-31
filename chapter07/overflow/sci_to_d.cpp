#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <limits>
using namespace std;

string build_int()
{
	char ch;
	string number;
	while (cin.get(ch) && (ch == '-' || isdigit(ch) || ch == '.')) number += ch;
	cin.putback(ch);
	return number;
}

void putback_str(string s)
{
	for (int i = s.size(); i >=0; --i)
		cin.putback(s[i]);
}

string sci_to_d(string s)
{
	putback_str(s);

	string significand;
	char ch;

	significand = build_int();
	cout << "significand= " << significand << "\tsignificand.size()= " << significand.size() << endl;
	cin.get(ch);
	if (ch != 'e') throw runtime_error("sci_to_d(): Expected 'e' for exponential.");
	int exponential;
	cin >> exponential;
	if (!cin) throw runtime_error("sci_to_d(): Invalid input for variable `exponential`.");
	if (exponential == 0) throw runtime_error("sci_to_d(): Illegal: Exponential value is in (-1,1) range.");
	cin.ignore();			// this line is necessary to stop invalid input on next loop.
	cout << "starting exponential= " << exponential << endl;

	int decimal_index = 0;
	bool neg = false;
	if (significand[0] == '-')
	{
		significand.erase(0,1);
		neg = true;
	}
	if (significand[0] == '.') 
	{
		decimal_index = -1;
		significand.erase(0,1);
	}
	if (significand[1] == '.') significand.erase(1,1);
	cout << "significand with no decimal= " << significand << endl;
	while (exponential > 0)
	{
		if (decimal_index == significand.size()-1 && exponential > 0)		
		{
			significand += '0';
			++decimal_index;
			--exponential;
		}
		else if (exponential == 1 && decimal_index < significand.size()-2)
		{
			significand.insert(decimal_index, ".");
			--exponential;
		}
		else
		{
			++decimal_index;
			--exponential;
		}
	}

	
	string ret = significand;
	if (neg) ret = '-' + ret;

	return ret;
}

string to_str_with_precision(double d)
{
	ostringstream out;
	out.precision(15);
	out << d;
	string ret = out.str();
	cout << "to_str_with_precision(): " << ret << endl;
	return ret;
}

int main()
{

	string test;
	while (cin >> test) try
	{
		string res = sci_to_d(test);

		cout << "sci_to_d(" << test << ")= " << res << endl;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
