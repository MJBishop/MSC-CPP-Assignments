/*	Michael Bishop		mbisho01		MSc Computer Science
	assignment6.cpp		Assignment 6F 	Submitted 20/12/2011

	This program: Reads the contents of the file a6f.txt
	and formats the text to a maximum line length as specified by the user.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

string format(string next, int max)
{	ostringstream os;
	int count = 0;
	while (static_cast<int>(next.length()) != 0)
	{	int sp = 0, wd = 0;
		while (next.substr(sp, 1) == " " && sp < static_cast<int>(next.length()))
   			sp++;
   		next = next.substr(sp);

		while (next.substr(wd, 1) != " " && wd < static_cast<int>(next.length()))
			wd++;
   		string word = next.substr(0, wd);
   		next = next.substr(wd);

   		if (wd > 0)
   		{	if ((count += sp + wd) > max)
			{	count = wd;
				os << endl;
			}
			else
				for (sp; sp > 0; sp--)
					os << "_";
				os << word;
		}
	}
	next = os.str();
	return next;
}

int main()
{	ofstream outfile("output.txt");
	bool first = true, more = true;
	while (more)
	{	if (first)
		{	cout << endl << "Please key in the line length: ";
			first = false;
		}
		else
			cout << endl << "Please key in another line length or Q to Quit: ";
		int max = 0;
		cin >> max;
		if (cin.fail())
			more = false;
		else
		{	outfile << endl << "Max line length: " << max << "\n" << endl;
			ifstream infile;
			infile.open("n:\\C++\\a6f.txt");
			assert (!infile.fail());
			string next;
			while (getline(infile, next))
			{	if (next.length() > 0)
					outfile << format(next, max);
				outfile << endl;
			}
		}
	}
}