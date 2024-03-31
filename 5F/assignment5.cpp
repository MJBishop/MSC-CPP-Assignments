/* 	Michael Bishop		mbisho01		MSc Computer Science
	assignment5.cpp		Assignment 5F 	Submitted 06/12/2011

	This program:
	Reads the contents of the file a5.txt into memory
	(a list of student names and marks).
	Reads the file queries.txt, and looks up each name
	in the list of students in memory.
	Outputs the searched name and "not there", if the student
	record is not stored in memory.
	Outputs the student record if it is stored in memory.

	The Cohort class is implemented in two ways:
	1. Student records are stored in a vector.
	2. Student records are stored in a binary search tree.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iomanip>

using namespace std;

class Student
{ public:
	Student(string nm, int m1, int m2, int m3);
	string	getname() const { return name; }
	void	display() const;
  private:
	string name;
	int	math, comp, stat;
};

Student::Student(string nm, int m1, int m2, int m3) :
		name(nm), math(m1), comp(m2), stat(m3) { }

void	Student::display() const
{	cout << setw(20) << name << setw(5) << math
		<< setw(5) << comp << setw(5) << stat << endl;
}

//#define FIRST
#ifdef FIRST

class Cohort
{ public:
	Cohort() { }
	void insert(Student st);
	Student find(string n) const;
  private:
  	vector<Student> vs;
  	int b_search(vector<Student> vs, int from, int to, string n) const;
};

void Cohort::insert(Student st)
{	int last = vs.size() - 1, pos = 0;
	if (last < pos || st.getname() > vs[last].getname())
		vs.push_back(st);
	else
	{	vs.push_back(vs[last]);
		for (pos; pos < last; pos++)
		{	if(st.getname() < vs[pos].getname())
				break;
		}
		for (int i = last; i > pos; i--)
			vs[i] = vs[i - 1];
		vs[pos] = st;
	}
}

int Cohort::b_search(vector<Student> vs, int from, int to, string n) const
{	if (from > to)
		return -1;
	int mid = (from + to) / 2;
	if (vs[mid].getname() == n)
		return mid;
	else if (vs[mid].getname() < n)
		return b_search(vs, mid + 1, to, n);
	else
		return b_search(vs, from, mid - 1, n);
}

Student Cohort::find(string n) const
{	int i = vs.size() - 1, j = b_search(vs, 0, i, n);
	if (j < 0)
		return Student("", 0, 0, 0);
	else
		return vs[j];
}

#else

class Cohort
{ public:
	Cohort(): head(NULL) { }
	void insert(Student stx) { insert(head, stx); }
	Student find(string n) const { return find(head, n); }
  private:
  	class Binode;
  	Binode* head;
  	void insert(Binode*& p, Student stx);
  	Student find(Binode* p, string n) const;
};

class Cohort::Binode
{ public:
	Binode(Student stx) : st(stx), l(NULL), r(NULL) { }
	Student st;
	Binode* l, *r;
};

void Cohort::insert(Binode*& p, Student stx)
{	if (p == NULL)
		p = new Binode(stx);
	else
	{	if (stx.getname() > p->st.getname())
			insert(p->r, stx);
		else
			insert(p->l, stx);
	}
}

Student Cohort::find(Binode* p, string n) const
{	if (p == NULL)
		return Student ("", 0, 0, 0);
	if (n == p->st.getname())
		return p->st;
	else
	{	if (n < p->st.getname())
			return find(p->l, n);
		else
			return find(p->r, n);
	}
}

#endif

int main()
{	Cohort	cohort;
	ifstream	infile;
	infile.open("n:\\C++\\a5.txt");	// student names and marks
	assert (! infile.fail());
	int	m, c, s;
	string	nm;
	while(infile >> m >> c >> s)
	{	getline(infile, nm);	// Names have embedded spaces
		nm = nm.substr(3);	// Skip leading spaces
		Student	st(nm, m, c, s);
		cohort.insert(st);
	}
	ifstream	queryfile;
	queryfile.open("n:\\C++\\queries.txt");	// names to look for
	assert (! queryfile.fail());
	string query;
	while(getline(queryfile, query))
	{	Student	st = cohort.find(query);
		if (st.getname().length() > 0)
			st.display();
		else	cout << query << " not there" << endl;
	}
}