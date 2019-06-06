#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <limits>
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
	out.precision(20);
	out << d;
	string ret = out.str();
	cout << "to_str_with_precision(): " << ret << endl;
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

int main()
{
	string temp;
	char ch;
	bool dec_flag = false;
	int dec_places = 0;
	vector<int> ret;
	double x = .000000000000001;	
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
			if (dec_flag)
				dec_places += 1;
		}
	}

	cout << "dec_places= " << dec_places << endl;
}
