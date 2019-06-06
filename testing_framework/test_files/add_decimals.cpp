#include <iostream>
#include <iomanip>
using namespace std;


double add_decimals(int x, int decimal_places)
{
	double ret = 1.0 * x;
	cout << "x= " << x << endl;
	cout << "ret before changes= " << ret << endl;
	for (int i = 0; i < decimal_places; ++i)
	{
		ret /= 10;
	}

	return ret;
}

int main() 
{
	double d = add_decimals(1234566, 2);
	cout << "d= "<< setprecision(10) << d << endl;
}
