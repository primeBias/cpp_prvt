#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void putback_str(string s)
{
	for (int i = s.size(); i >= 0; --i)
	{
		cin.putback(s[i]);
	}
}

string to_str_with_precision(double d)
{
	ostringstream out;
	out.precision(15);
	out << d;
	string ret = out.str();
	return ret;
}

int main() 
{
	string res;
	double y = .123456789;
	string test = to_str_with_precision(y);
	cout << "test= " << test << endl;
	char ch;
	while (cin.get(ch) && (isdigit(ch) || ch == '.' || ch == '-'))
	{
		if (ch == '.') { }
		else res += ch;
	}

	cout << "res= " << res << endl;
	putback_str(res);
	int x;
	cin >> x;
	cout << "x= " << x << endl;
}
