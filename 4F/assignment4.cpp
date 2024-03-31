/* 	Michael Bishop		mbisho01		MSc Computer Science
	assignment4.cpp		Assignment 4F 	Submitted 22/11/2011

	This program: Reads the names of the staff members from
	staff.txt into a circular, singly-linked list.
	Selects every nth person from the list to output and
	eliminate.

*/

#include <string>
#include <fstream>
#include <cassert>
#include <iostream>
using namespace std;



class Circlist
{ public:
	Circlist();					// default constructor
	void addnode(string sx);	// adds name sx to the circle
	string select(int n);		// removes every nth, returns winner
	void display( ) const;		// displays contents of list
  private:
	class Node;
	Node* start;
};

class Circlist::Node
{ public:
	Node(string sx) : s(sx), link(NULL) { }
	string s;
	Node* link;
};


Circlist::Circlist()
{	start = NULL;
}

void Circlist::addnode(string sx)
{	Node* p = new Node(sx);
	if (start == NULL)
	{	start = p;
		start->link = start;
	}
	else
	{	p->link = start->link;
		start->link = p;
	}
}

string Circlist::select(int n)
{	if (start == NULL)
	{	cout << endl << "** Cannot select from empty list" << endl;
		return "";
	}
	if (n <= 0)
	{	cout << endl << "** Cannot remove every nth where n is <= zero"
			 << endl;
		return "";
	}
	else
	{	string win;
		Node* p = start->link;
		while (start != NULL)
		{	for (int i = 1; i < n; i++)
			{	p = p->link;
				start = start->link;
			}
			cout << p->s << endl;
			start->link = p->link;
			delete p;
			p = start->link;
			if (p == start)
			{	win = p->s;
				delete p;
				start = NULL;
			}
		}
		return win;
	}
}

void Circlist::display( ) const
{	if (start == NULL)
		cout << endl << "** List Empty" << endl;
	else
	{	Node* p = start->link;
		while (p != start)
		{	cout << p->s << endl;
			p = p->link;
		}
		cout << p->s << endl;
	}
}

int main( )
{	Circlist	c;
	cout << endl << "Contents of c:" << endl;
	c.display();
	assert (c.select(5).length() == 0);	// test of error handling

	ifstream	infile("staff.txt");
	assert (! infile.fail());
	string name;
	while (getline(infile,name))
		c.addnode(name);
	assert(infile.eof());

	cout << endl << "Contents of c:" << endl;
	c.display();
	assert (c.select(0).length() == 0);	// test of error handling
	cout << endl << "Eliminating every seventh:" << endl;
	name = c.select(7);
	cout << endl << "The winner is " << name << endl;
}