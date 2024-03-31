/* 	Michael Bishop		mbisho01		MSc Computer Science
 	assignment3.cpp		Assignment 3F 	Submitted 23/10/2011

 	This program:
 	Enables a user to do integer addition even though the result might exceed INT_MAX. 
 	Bigint holds an integer in the form of a vector of int, 
 	each element of the vector holding one (decimal) digit, 
 	with element zero holding the right most (least significant) digit. 
 
 	For example, the integer 567 would be stored with the 5 in element two, 
 	the 6 in element one and the 7 in element zero. 
 	Leading zeros are not stored, 
 	which means that the integer zero is represented by an empty vector. 
 	Only non-negative values ( >= 0 ) can be represented.
 */

#include <climits>
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


class Bigint
{
public:
	Bigint();
	Bigint(int x);
	Bigint(string s);
	Bigint operator+(const Bigint& b) const;
	string str() const;
private:
	vector<int> v;
};

Bigint::Bigint()
{
}

Bigint::Bigint(int x)
{	int y = x;
	for (int i = 0; y > 0; i++)
	{	v.push_back(0);
		v[i] = y % 10;
		y /= 10;
	}
}

Bigint::Bigint(string s)
{	while (s.length() > 1 && s[0] < '1')
		s = s.substr(1, static_cast<int>(s.length()));
	istringstream is(s);
	char ch;
	while(is.get(ch))
	{	if (ch < '0' || ch > '9')
		{	v.clear();
			break;
		}
		else
		{	v.push_back(0);
			for (int i = v.size() - 1; i > 0; i--)
				v[i] = v[i - 1];
			v[0] = ch - '0';
		}
	}
}

Bigint Bigint::operator+(const Bigint& b) const
{	Bigint c; c.v = v;
	Bigint d; d.v = b.v;
	if (c.v.size() > d.v.size())
	{	for (int i = d.v.size(); i < static_cast<int>(c.v.size()); i++)
			d.v.push_back(0);
	}
	else
	{	for (int i = c.v.size(); i < static_cast<int>(d.v.size()); i++)
			c.v.push_back(0);
	}
	for (int i = 0; i < static_cast<int>(c.v.size()); i++)
		c.v[i] = c.v[i] + d.v[i];

	for (int i = 0; i < static_cast<int>(c.v.size() - 1); i++)
	{	if(c.v[i] > 9)
		{	c.v[i] %= 10;
			c.v[i + 1]++;
		}
	}
	if (c.v[static_cast<int>(c.v.size() - 1)] > 10)
	{	c.v.push_back(0);	d.v.push_back(0);
		c.v[static_cast<int>(c.v.size() - 2)] %= 10;
		c.v[static_cast<int>(c.v.size() - 1)]++;
	}
	return c;
}

string Bigint::str() const
{	ostringstream os;
	if (v.empty())
		os << 0;
	else
		for (int i = static_cast<int>(v.size() - 1); i > -1; i--)
			os << v[i];
	return os.str();
}

int main()
{	Bigint x, y(0), z("1");
	cout << "x is " << x.str() << " and y is " << y.str() << " and z is "
		 << z.str() << endl;
	x = Bigint("1234567890123456789");    y = Bigint("000456");
	z = Bigint(-1);
	cout << "x is " << x.str() << " and y is " << y.str() << " and z is "
		 << z.str() << endl;
	x = Bigint("987C++");    y = Bigint("0000");
	z = Bigint("-5.67");
	cout << "x is " << x.str() << " and y is " << y.str() << " and z is "
		 << z.str() << endl;
	x = Bigint(INT_MAX);
	y = Bigint(1);
	z = x + y;
	cout << "x is " << x.str() << " and y is " << y.str() << " and z is "
		 << z.str() << endl;
	y = Bigint("1608236086");
	z = x + x + x + x + x + y;
	cout << "x is " << x.str() << " and y is " << y.str() << " and z is "
		 << z.str() << endl;
	cout << endl;

	ifstream inf("a3.txt");
		assert (! inf.fail());
		string	s, t;
	while (inf >> s >> t)
	{	Bigint	a(s), b(t), c;
		c = a + b;
		cout << c.str() << endl << endl;
	}
}
