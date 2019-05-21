#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> res {1,1,1};	
	for (int i = 0; i < 2; ++i)
	{
		res[0] = i;
		for (int j = 0; j < 2; ++j)
		{
			res[1] = j;
			for (int k = 0; k < 2; ++k)
			{
				res[2] = k;
				for (int x : res)
					cout << x << '\t';
				cout << endl;
			}
		}
	}
}
