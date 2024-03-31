/* 	Michael Bishop		mbisho01		MSc Computer Science
	assignment2.cpp		Assignment 2F 	Submitted 25/10/2011

	This program: Reads three examination marks (Maths, Computing and
	Statistics) from the text file "a1f.txt". 
	Writes "Bad input line: " and a copy of the line, 
	if it fails to read an input line correctly
	or encounters values greater than 95 or less than 0. Prints a
	histogram showing the distribution of the Computing marks in 8
	ranges of 12 marks each: 0 through 11, 12 through 23,..,84 through 95.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


bool invalid_range(int m, int c, int s)
{
	return(m < 0 || m > 95 || c < 0 || c > 95 || s < 0 || s > 95);
}


int max_freq(vector<int> v, int c)	//Calculates the maximum frequency:
{
	int max = v[1];
    for(int i = 1; i < c; i++)
	{
		if(v[i + 1] > max)
			max = v[i + 1];
	}
    return max;
}


int freq_width(int freq)	//Calculates the width of the max freq:
{
	int width = 0;
    while (freq)
    {
		freq /= 10;
        width++;
    }
    return width;
}


int main()
{
	ifstream infile("a1f.txt");
	ofstream outfile("output.txt");

	if (infile.fail())
   	{
		cerr << "Error: input file not opened" << endl;
      	return EXIT_FAILURE;
   	}


	const int TOTAL_RANGE = 96;
	const int COLUMN_NUM = 8;
	const int COLUMN_RANGE = TOTAL_RANGE / COLUMN_NUM;

	vector<int> vfreq(COLUMN_NUM + 1);
	vector<int> vrange(COLUMN_NUM + 1);

	for(int i = 0; i < COLUMN_NUM + 1; i++)	//Calculates the ranges:
		vrange[COLUMN_NUM - i] = (TOTAL_RANGE - 1) - (i * COLUMN_RANGE);


	string s;
	while (getline(infile, s))
	{
		istringstream is(s);
		int math = 0, comp = 0, stat = 0;
		is >> math >> comp >> stat;

		if(is.fail() || invalid_range(math, comp, stat))
			outfile << "Bad input line: " << s << endl;

		else	for(int i = 0; i < COLUMN_NUM + 1; i++)	//Dist. marks:
				{
					if(comp > vrange[i] && comp < (vrange[i + 1] + 1))
						vfreq[i + 1]++;
				}
	}


	const int MAX_FREQ = max_freq(vfreq, COLUMN_NUM);
	const int FREQ_WIDTH = freq_width(MAX_FREQ);


	for(int i = 0; i < MAX_FREQ; i++)	//Outputs freq range and y-axis:
	{
		outfile << setw(FREQ_WIDTH) << (MAX_FREQ - i) << "|";

			for(int j = 0; j < COLUMN_NUM; j++)	//Outputs distribution:
			{
				if(vfreq[j + 1] >= MAX_FREQ - i)
					outfile << setw(3) << "**";

				else
					outfile << setw(3) << "  ";
			}
		outfile << " |" << endl;
	}


	for(int i = 0; i < FREQ_WIDTH; i++)	//Outputs the x-axis:
		outfile << "-";
	outfile << "+";

	for(int i = 0; i < COLUMN_NUM; i++)
		outfile << "---";
	outfile << "-+" << endl;


	for(int i = 0; i < FREQ_WIDTH; i++)	//Outputs the column range:
		outfile << " ";
	outfile << "|";

	for(int i = 0; i < COLUMN_NUM; i++)
		outfile << setw(3) << vrange[i + 1];
	outfile << " |" << endl;
}