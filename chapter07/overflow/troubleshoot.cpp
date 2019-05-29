#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <math.h>
#include <cmath>
#include <iomanip>
using namespace std;



// code is working for decimals with less than 5 digit of precision.
// more precision than that leads to incorrect calculation of the
// while conditional: what should be 0 is instead evaluated as a 
// small fraction.
vector<int> remove_decimals(double x)
{
	int decimal_places = 0;
	vector<int> ret;
	int temp = x;
	double a = 12345;
	int b = 12345;
	cout << a << "-" << b << "= " << a-b << endl;
	while (x - temp != 0)
	{
		x *= 10;
		temp = x;		// casting double to int (removing remainder)
		decimal_places += 1;
		cout << "x= " << setprecision(15) << x << endl;
		cout << "temp= " << setprecision(15) << temp << endl;
		cout << "x - temp= " << x-temp << endl;
		cin.get();
	}


	ret.push_back(temp);
	ret.push_back(decimal_places);

	return ret;
}

int main()
{
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
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
