#include <iostream>
#include <stdexcept>
#include <limits>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;


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
	bool decimal_found = false;
	for (int i = 0; i < temp.size(); ++i)
	{
		if (temp[i] == '.') decimal_found = true;
	}

	if (!decimal_found) return temp; 	// no trailing zeros to remove
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

// problem: for doubles with a large amount of precision,
// the '.' character is not being recognized.
// solution: the problem has to do with to_str_with_precision. 
// more specifically, doubles get translated to scientific
// notation when put to a string. Easiest thing to do would
// be able to parse and translate the scientific notation
// into an equivalent string.
vector<int> remove_decimals(double x)
{
	string temp;
	char ch;
	bool dec_flag = false;
	int dec_places = 0;
	vector<int> ret;
	
	temp = to_str_with_precision(x);
	temp = remove_trailing_zero(temp);
	cout << "temp= " << setprecision(15) << temp << endl;
	putback_str(temp);

	temp = "";

	while (cin.get(ch) && (isdigit(ch) || ch == '.' || ch == '-'))
	{
		if (ch == '.') { cout << "decl_flag= true" << endl; dec_flag = true; }
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
	cout << "dec_places= " << dec_places << endl;
	// cin.clear();
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return ret;
}

// Divides `a` by `b` and returns a vector of ints.
// Returns:
// [1] = quotient
// [2] = remainder
// [3] = negative number flag
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
		if (temp - b >= 0)
		{
			temp -= b;
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
		for (int i = 0; i > decimal_places; --i) ret *= 10;

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

	cout << "temp_a= " << temp_a[0] << "\ttemp_b= " << temp_b[0] << endl;
	vector<int> res = divide(temp_a[0], temp_b[0]);
	final_res = res[0];
	if (res[2] == -1) neg = true;
	cout << "division result..." << endl;
	cout << res[0] << 'r' << res[1] << endl;

	for (int i = 0; i < 8; ++i)		// 8 digits of precision
	{
		if (res[1] != 0)			// if remainder is not 0
		{
			res = divide(res[1]*10, temp_b[0]);
			cout << "division result..." << endl;
			cout << res[0] << 'r' << res[1] << endl;
			decimal_places += 1;
			final_res *= 10;
			if (final_res > numeric_limits<int>::max() - res[0]) throw runtime_error("divide_with_precision(): Overflow error.");
			final_res += res[0];
		}
	}
	
	cout << "decimal_places= " << decimal_places << endl;	
	if (neg) final_res = -final_res; 	
	return add_decimals(final_res, decimal_places);
}

int main()
{
	while (true) try
	{
		double a, b;
		cout << ">";
		cin >> a >> b;
		if (!cin)
			throw runtime_error("Invalid input.");
		cout << "dividing..." << endl;
		cout << setprecision(15) << a << " / " << b << "= " << divide_with_precision(a, b) << endl;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
