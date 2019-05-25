#include <iostream>
using namespace std;

int main()
{
	while (true) try
	{
		// cin operations
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
