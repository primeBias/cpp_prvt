
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.

	Grammar:
		Statement:
			Declaration
			Expression
		Declaration:
			"let" name '=' Expression
		Name:
			string
		Expression:
			Term
			Expression '+' Term
			Expression '-' Term
		Term:
			Primary
			Term '*' Primary
			.
			.
			.
		
*/

#include "std_lib_facilities.h"

class Token {
public:
	char kind;			// what kind of token
	double value;		// for numbers: a value
	string name;		// for ames: name itself
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) : kind(ch), name(n) { }
};

class Token_stream {
public:
	Token_stream() :full(0), buffer(0) { }	// make a Token_strema that reads from cin
	Token get();							// get a Token
	void unget(Token t) { buffer=t; full=true; }	// put a Token back
	void ignore(char);								// Discard tokens up to char including char
private:
	bool full;		// is there a Token in the buffer?
	Token buffer;	// here is where we keep a Token put back using putback()
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sq = 's';
const char pwr = 'p';
const char constant = 'c';

Token Token_stream::get()
{
	if (full) { full=false; return buffer; } // check if we already have a Token ready
	char ch;
	cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch) {
	case quit:
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ',':
	// case ';':
	case '=':
		return Token(ch); // let each character represent itself
	case '.':		// a floating point literal can start with a dot
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.putback(ch);
		double val;
		cin >> val;
		return Token(number,val);
	}
	case '#':
		return Token(let);
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s+=ch;
			cin.putback(ch);
			if (s == "sqrt") return Token(sq);
			if (s == "pow") return Token(pwr);
			if (s == "const") return Token(constant);
			// if (s == "quit") return Token(name);
			return Token(name,s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	cout << "Searching for ; char to end invalid statement." << endl;
	while (cin>>ch)
		if (ch==c) return;
}

class Variable {
public:
	string name;
	double value;
	bool is_const = false;
	Variable(string n, double v) :name(n), value(v) { }
	Variable(string n, double v, bool b) :name(n), value(v), is_const(b) { }
};


vector<Variable> names;	

double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

void set_value(string s, double d)
{
	for (int i = 0; i<=names.size(); ++i)
	{
		if (names[i].name == s && names[i].is_const == false) {
			names[i].value = d;
			return;
		}
		else if(names[i].name == s && names[i].is_const == true)
		{	
			cout << "Warning: " << s << " is a constant value and cannot change values.\n";
			return;
		}
	}
	error("set: undefined name ",s);

}

bool const_check(string s)
{
	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i].name == s)
			if (names[i].is_const == true)
				return true;
			else if (names[i].is_const == false)
				return false;
			else
				throw runtime_error("const_check(): some error with const value.");
	}
}

bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		//added below line
		return d;
	}
	case sq:
	{
		t = ts.get();	// get the '(' 
		if (t.kind != '(') error("'(' expected");
		double d = sqrt(expression());
		if (isnan(d)) error("negative sqrt computed");
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case pwr:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");

		double d = expression();
		t = ts.get();
		if (t.kind != ',') error("',' expected");

		int m = narrow_cast<int>(expression());
		d = pow(d,m);

		t = ts.get();
		if (t.kind != ')') error("')' expected");
		
		return d;
	}
	case '-':
		return - primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declare_const()
{
	Token t = ts.get();
	if (t.kind != 'a') error ("name expected in declaration");
	string name = t.name;
	if (const_check(name))
		throw runtime_error("Variable is a constant.");
	if (is_declared(name)) 
		cout << "Warning: variable with name= " << t.name << " is already declared. " << t.name << "= " << get_value(t.name) << " will be removed." << endl;
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();

	names.push_back(Variable(name,d,true));
	return d;
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error ("name expected in declaration");
	string name = t.name;
	if (const_check(name))
		throw runtime_error("Variable is a constant.");
	if (is_declared(name)) 
		cout << "Warning: variable with name= " << t.name << " is already declared. " << t.name << "= " << get_value(t.name) << " will be removed." << endl;
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	names.push_back(Variable(name,d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	case constant:
		return declare_const();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
	
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

	try {
		calculate();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >>c&& c!=';') ;
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin>>c && c!=';');
		return 2;
	}
