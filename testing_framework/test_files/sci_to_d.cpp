#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <assert.h>
#include "../test_framework.h"
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


int main()
{
	string file_name = "sci_to_d.cpp";
	bool exception_thrown = false;
	int x = 1;
	ASSERT(sci_to_d("1e10"), "10000000000", "Test 1");

	ASSERT(sci_to_d("1.23e5"), "123000", "Test 2");

	ASSERT_ERROR(test_3, sci_to_d(".234e.5"), "Test 3");
	
	ASSERT(sci_to_d(".234e4"), "2340", "Test 4");

	ASSERT(sci_to_d("-2e6"), "-2000000", "Test 5");

	ASSERT(sci_to_d("-2.34e4"), "-23400", "Test 6");

	ASSERT(sci_to_d("-.402e9"), "-402000000", "Test 7");

	ASSERT(sci_to_d("1e-1"), ".1", "Test 8");

	ASSERT(sci_to_d("-2e-3"),  "-.002", "Test 9");

	ASSERT(sci_to_d("2.432e-6"), ".000002432", "Test 10");	

	ASSERT(sci_to_d(".632156e-9"), ".00000000632156", "Test 11");

	ASSERT_ERROR(test_4, sci_to_d(".24e-.4"), "Test 12");
	
	ASSERT(sci_to_d("1e-100"), ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", "Test 13");

	TEST_SUMMARY(file_name);
}
