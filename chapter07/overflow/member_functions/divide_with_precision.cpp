#include <iostream>
#include <stdexcept>
#include <limits>
#include <vector>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "test_framework.h"
using namespace std;

// builds a number fron standard input.
// returns the number in string format.
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
	for (int i = s.size(); i >=0; --i) cin.putback(s[i]);
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

// sci_to_d() subroutine for cases when exponential > 0.
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

// sci_to_d() subroutine for cases when exponential < 0.
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
	cin.get(ch);
	if (ch != 'e') throw runtime_error("sci_to_d(): Expected 'e' for exponential.");
	cin >> exponential;
	if (!cin) throw runtime_error("sci_to_d(): Invalid input for variable `exponential`.");
	if (exponential == 0) throw runtime_error("sci_to_d(): Illegal: Exponential value is in (-1,1) range.");
	cin.ignore();			// this line is necessary to stop invalid input on next loop.
}

// translate double to string with precision
string to_str_with_precision(double d)
{
	ostringstream out;
	out.precision(15);
	out << d;
	string ret = out.str();
	return ret;
}

// Removes trailing zeros from a double that is represented as a string.
string remove_trailing_zero(string temp)
{
	char c_del = '0';
	int index = temp.size();
	bool decimal_found = false;
	for (int i = 0; i < temp.size(); ++i)
		if (temp[i] == '.') decimal_found = true;

	if (!decimal_found) return temp; 	
	while (c_del == '0')
	{
		c_del = temp[index-1];
		if (c_del == '0') temp.erase(index-1);
		--index;
	}

	return temp;
}

// Converts string representation of double from scientific notation to
// standard notation.
string sci_to_d(string s)
{
	putback_str(s);

	string significand;
	int exponential;		// for ticket_1 does this have to be long long int?
	get_significand_exponential(significand, exponential);

	int decimal_index = 0;
	
	vector<bool> preprocessed_significand = remove_dec_significand(significand); 
	
	bool neg = preprocessed_significand[0];
	bool no_int = preprocessed_significand[1];
	if (no_int) decimal_index--;				// necessary adjustment for case of no_int		

	sci_to_d_exp_grtr_zero(decimal_index, exponential, significand);
	++exponential; 		// removing decimal is equivalent to applying factor of 10 in below case.

	sci_to_d_exp_less_zero(decimal_index, exponential, significand);
	string ret = significand;
	if (neg) ret = '-' + ret;

	return ret;
}

bool is_scientific(string s)
{
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == 'e') return true;

	return false;
}

// Returns:
// 	[0]: Number without decimal
// 	[1]: Decimal position
vector<int> remove_decimals(double x)
{
	string temp;
	char ch;
	bool dec_flag = false;
	int dec_places = 0;
	vector<int> ret;
	
	temp = to_str_with_precision(x);
	if (is_scientific(temp)) temp = sci_to_d(temp);	
	temp = remove_trailing_zero(temp);
	putback_str(temp);

	temp = "";

	while (cin.get(ch) && (isdigit(ch) || ch == '.' || ch == '-'))
	{
		if (ch == '.') dec_flag = true; 
		else 
		{
			temp += ch;
			if (dec_flag) dec_places += 1;
		}
	}

	putback_str(temp);
	int res;
	cin >> res;
	ret.push_back(res);
	ret.push_back(dec_places);
	cin.ignore(); // this removes the pause
	return ret;
}

// Divides `a` by `b` and returns a vector of ints.
// Returns:
// [0] = quotient
// [1] = remainder
// [2] = negative number flag
vector<int> divide(int a, int b)
{
	vector<int> ret;
	int temp = a;
	int answer = 0;
	bool neg = false;
	if (b == 0) throw runtime_error("Divide by zero.");
	if ((a < 0 && b > 0) || (a > 0 && b < 0)) neg = true;
	if (a < 0)
	{
		temp = -temp;
		a = -a;
	}
	if (b < 0) b = -b;
	do	
	{
		// may be able to refactor this to be more simple
		if (temp - b >= 0)
		{
			temp -= b;
			if (answer > numeric_limits<int>::max() - 1) throw runtime_error("divide(): Overflow error");
			answer += 1;
		}
		else
		{
			int remainder = a - answer * b;
			ret.push_back(answer);
			ret.push_back(remainder);
			if (neg) ret.push_back(-1);
			else ret.push_back(1);
			temp -= b;
		}

	} while (temp >= 0);

	return ret;
}

double add_decimals(int x, int decimal_places)
{
	double ret = 1.0 * x;
	if (decimal_places >= 0)
		for (int i = 0; i < decimal_places; ++i) ret /= 10;
	else
		for (int i = 0; i > decimal_places; --i) 
		{
			if (ret > numeric_limits<int>::max() / 10) throw runtime_error("add_decimals(): Overflow error.");
			ret *= 10;
		}

	return ret;
}

double divide_with_precision(double a, double b)
{
	int decimal_places = 0;
	int final_res;
	bool neg = false;

	vector<int> temp_a = remove_decimals(a);
	vector<int> temp_b = remove_decimals(b);

	decimal_places = temp_a[1] - temp_b[1];

	vector<int> res = divide(temp_a[0], temp_b[0]);
	final_res = res[0];
	if (res[2] == -1) neg = true;

	for (int i = 0; i < 8; ++i)		// 8 digits of precision
	{
		if (res[1] != 0)			// if remainder is not 0
		{
			res = divide(res[1]*10, temp_b[0]);
			decimal_places += 1;
			final_res *= 10;
			if (final_res > numeric_limits<int>::max() - res[0]) throw runtime_error("divide_with_precision(): Overflow error.");
			final_res += res[0];
		}
	}
	
	if (neg) final_res = -final_res; 	
	return add_decimals(final_res, decimal_places);
}

// Test file function
bool equals(double a, double b)
{
	double epsilon = .00001;
	if (a - b > epsilon) return false;
	return true;
}

int main()
{
	string file_name = "divide_with_precision.cpp";

	// Test 1
	ASSERT_DOUBLE(divide_with_precision(10, 4), 2.5, "Test 1");

	// Test 2
	ASSERT_DOUBLE(divide_with_precision(1, 6), .16666666, "Test 2");
	
	// Test 3
	ASSERT_DOUBLE(divide_with_precision(7, 8), .875, "Test 3");

	// Test 4
	ASSERT_DOUBLE(divide_with_precision(1, .1), 10, "Test 4");

	// Test 5
	ASSERT_DOUBLE(divide_with_precision(10, .1), 100, "Test 5");

	// Test 6
	ASSERT_DOUBLE(divide_with_precision(-4, 3), -1.333333, "Test 6");

	// Test 7
	ASSERT_DOUBLE(divide_with_precision(-4, .02), -200, "Test 7");

	// Test 8
	ASSERT_DOUBLE(divide_with_precision(-7, -12), .583333, "Test 8");

	// Test 9
	ASSERT_DOUBLE(divide_with_precision(-6, -5), 1.2, "Test 9");

	// Test 10
	ASSERT_DOUBLE(divide_with_precision(-90, .3), -300, "Test 10");

	ASSERT_ERROR(divide_by_zero, divide_with_precision(10,0), "Test 11");

	ASSERT_DOUBLE(divide_with_precision(0,10000), 0, "Test 12");

	TEST_SUMMARY(file_name);

}

