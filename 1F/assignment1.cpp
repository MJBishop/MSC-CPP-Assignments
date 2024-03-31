/* 	Michael Bishop		mbisho01		MSc Computer Science
	assignment1.cpp		Assignment 1F 	Submitted 18/10/2011

	This program: Reads three examination marks (Maths, Computing and
	Statistics) from the text file "a1f.txt". Writes the marks followed by
	the grade awarded to a file "output.txt". [Pass: 50 or over in all
	three exams, or 60 or over in two (one of which must be Maths) and 40
	or over in the other, or 75 or over in Maths and 40 or over in the
	other two. Distinction: 75 or over in two and already a pass. Fail: All
	others]. Writes "Bad input line: " and a copy of the line, if it fails
	to read an input line correctly or encounters values greater than 95 or less than 0.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool f_range(int m, int c, int s)
{	return(m < 0 || m > 95 || c < 0 || c > 95 || s < 0 || s > 95);
}

bool f_pass(int m, int c, int s)
{	return((m >= 75 && c >= 40 && s >= 40)
		|| (m >= 60 && ((c >= 60 && s >= 40) || (s >= 60 && c >= 40)))
		|| (m >= 50 && c >= 50 && s >= 50));
}

bool f_distinction(int m, int c, int s)
{	return(((m >= 75 && c >= 40 && s >= 40)
		|| (m >= 60 && ((c >= 60 && s >= 40) || (s >= 60 && c >= 40)))
		|| (m >= 50 && c >= 50 && s >= 50))
		&& ((m >= 75 && c >= 75 && s >= 40)
		|| (m >= 75 && s >= 75 && c >= 40)
		|| (s >= 75 && c >= 75 && m >= 40)));
}

int main()
{
	ifstream infile("a1f.txt");
	ofstream outfile("output.txt");

	if (infile.fail())
   	{  	cerr << "Error: input file not opened" << endl;
      	return EXIT_FAILURE;
   	}

	string s;
	while (getline(infile, s))
	{	istringstream is(s);
		int math = 0, comp = 0, stat = 0;
		is >> math >> comp >> stat;

		if(is.fail() || f_range(math, comp, stat))
			outfile << "Bad input line: " << s << endl;

		else	if(f_distinction(math, comp, stat))
					outfile << setw(2) << math << setw(3) << comp
							<< setw(3) << stat << " Distinction" << endl;

				else 	if(f_pass(math, comp, stat))
							outfile << setw(2) << math << setw(3) << comp
									<< setw(3) << stat << " Pass" << endl;

						else
							outfile << setw(2) << math << setw(3) << comp
									<< setw(3) << stat << " Fail" << endl;
	}
}