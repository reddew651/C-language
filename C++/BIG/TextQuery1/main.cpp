#include "TextQuery.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

void runQueries(ifstream &infile)
{
	// infile is an ifstream that is the file we want to query
	TextQuery tq(infile);  // store the file and build the query map

	tq.display_map();
	
	// iterate with the user: prompt for a word to find and print results
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string s;
		// stop if we hit end-of-file on the input or if a 'q' is entered
		if (!(cin >> s) || s == "q") break;
		// run the query and print the results
		print(cout, tq.query(s)) << endl;
	}
}

// program takes single argument specifying the file to query
int main(int argc, char **argv)
{
	// open the file from which user will query words
	if (argc >= 2) {
		ifstream infile(argv[1]);
		if (infile.is_open()) {
			runQueries(infile);
		}
		else {
			cerr << "Failed opening input file!" << endl;
			return -1;
		}
	}
	else {
		cerr << "No input file name!" << endl;
	}
	return 0;
}