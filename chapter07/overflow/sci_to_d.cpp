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

// Prepocess the significand by removing the decimal and negative signs if any.
// Returns flags for if the significand was negative or had no integer value.
vector<bool> remove_dec_significand(string& significand)
{
	vector<bool> ret;
	bool neg = false;
	bool no_int = false;
	if (significand[0] == '-')
	{
		significand.erase(0,1);
		neg = true;
	}
	if (significand[0] == '.') 
	{
		no_int = true;
		significand.erase(0,1);
	}
	if (significand[1] == '.') significand.erase(1,1);

	ret.push_back(neg);
	ret.push_back(no_int);

	return ret;
}

void sci_to_d_exp_grtr_zero(int& decimal_index, int& exponential, string& significand)
{
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
}

void sci_to_d_exp_less_zero(int& decimal_index, int& exponential, string& significand)
{
	while (exponential < 0)
	{
		significand = '0' + significand;
		++exponential;
	}
	
	if (exponential == 0) significand = '.' + significand;
}

void get_significand_exponential(string& significand, int& exponential)
{
	char ch;
	significand = build_int();
	cout << "significand= " << significand << "\tsignificand.size()= " << significand.size() << endl;
	cin.get(ch);
	if (ch != 'e') throw runtime_error("sci_to_d(): Expected 'e' for exponential.");
	cin >> exponential;
	if (!cin) throw runtime_error("sci_to_d(): Invalid input for variable `exponential`.");
	if (exponential == 0) throw runtime_error("sci_to_d(): Illegal: Exponential value is in (-1,1) range.");
	cin.ignore();			// this line is necessary to stop invalid input on next loop.
}

string sci_to_d(string s)
{
	putback_str(s);

	string significand;
	int exponential;
	get_significand_exponential(significand, exponential);

	cout << "starting exponential= " << exponential << endl;

	int decimal_index = 0;
	
	vector<bool> preprocessed_significand = remove_dec_significand(significand); 
	
	bool neg = preprocessed_significand[0];
	bool no_int = preprocessed_significand[1];
	if (no_int) decimal_index--;		// necessary adjustment for case of no_int		
	cout << "significand with no decimal= " << significand << endl;

	sci_to_d_exp_grtr_zero(decimal_index, exponential, significand);
	++exponential; 		// removing decimal is equivalent to applying factor of 10 in below case.

	sci_to_d_exp_less_zero(decimal_index, exponential, significand);
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
