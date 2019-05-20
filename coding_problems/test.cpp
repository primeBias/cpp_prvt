#include <vector>
#include <iostream>
using namespace std;

void print_answers(vector<vector<int> > answers);

void print_vector(vector<int> answer)
{
	for (int i = 0; i < answer.size(); ++i)
	{
		cout << answer[i] << '\t';
	}
	cout << endl;
}

void binary_rep(int level, vector<int>& substr, vector<vector<int> >& answers)
{
	for (int i = 0; i < 2; ++i)
	{
		// cout << "LEVEL: " << level << endl;
		substr[level] = i;
		if (level == substr.size() - 1)
		{
			answers.push_back(substr);
			// print_vector(substr);	
		}
		else
			binary_rep(level+1, substr, answers);
	}
}

vector<int> generate_substr(int size)
{
	vector<int> ret;
	for (int i = 0; i < size; ++i)
		ret.push_back(0);
	return ret;
}

void print_answers(vector<vector<int> > answers)
{
	for (int i = 0; i < answers.size(); ++i)
	{
		cout << "[" << i << "]\t";
		for (int j = 0; j < answers[i].size(); ++j)
			cout << answers[i][j] << '\t';
		cout << endl;
	}
}

vector<char> str_to_vec(string s)
{
	vector<char> ret;
	for (int i = 0; i < s.length(); ++i)
	{
		ret.push_back(s[i]);	
	}
	return ret;
}

string create_substr(string s, vector<int> bin_rep)
{
	string ret;
	for (int i = 0; i < bin_rep.size(); ++i)
	{
		if (bin_rep[i] == 0) { }
		else if (bin_rep[i] == 1)
			ret += s[i];
	}
	return ret;
}
vector<string> get_substr(string s, vector<vector<int> > answers)
{
	vector<string> ret;
	// for each answer in answers
	for (int i = 0; i < answers.size(); ++i)
	{
	// create substr based on that answer
		string substr = create_substr(s, answers[i]);
	// push substr to <vector<string> ret
		ret.push_back(substr);
	}

	return ret;
}
int main() 
{
	vector<vector<int> > answers;
	string full_string;
	int size;
	cin >> full_string;

	vector<int> substr = generate_substr(full_string.size());

	binary_rep(0, substr, answers);
	print_answers(answers);
	
	vector<string> substrings = get_substr(full_string, answers);	

	for (int i = 0; i < substrings.size(); ++i)
	{
		cout << "[" << i << "]: " << substrings[i] << endl;
	}
}
