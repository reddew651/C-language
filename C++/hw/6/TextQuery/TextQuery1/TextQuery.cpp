/*
* This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
* Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
* copyright and warranty notices given in that book:
*
* "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
*
*
* "The authors and publisher have taken care in the preparation of this book,
* but make no expressed or implied warranty of any kind and assume no
* responsibility for errors or omissions. No liability is assumed for
* incidental or consequential damages in connection with or arising out of the
* use of the information or programs contained herein."
*
* Permission is granted for this code to be used for educational purposes in
* association with the book, given proper citation if and when posted or
* reproduced.Any commercial use of this code requires the explicit written
* permission of the publisher, Addison-Wesley Professional, a division of
* Pearson Education, Inc. Send your request for permission, stating clearly
* what code you would like to use, and in what specific way, to the following
* address:
*
* 	Pearson Education, Inc.
* 	Rights and Permissions Department
* 	One Lake Street
* 	Upper Saddle River, NJ  07458
* 	Fax: (201) 236-3290
*/

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include "TextQuery.h"

using namespace std;

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream &is) : file(new vector<string>)
{
	string text;
	while (getline(is, text)) {       // for each line in the file
		file->push_back(text);        // remember this line of text
		int n = file->size() - 1;     // the current line number
		istringstream line(text);     // separate the line into words
		string word;
		while (line >> word) {        // for each word in that line
			word = cleanup_str(word);
			// if word isn't already in wm, subscripting adds a new entry
			auto &lines = wm[word]; // lines is a pointer 
			if (!lines) // that pointer is null the first time we see word
				lines = new set<line_no>; // allocate a new set
			lines->insert(n);      // insert this line number
		}
	}
}

TextQuery::~TextQuery() {
	for (const auto & word2lines : wm) {
		set<line_no> * ptr_line_set = word2lines.second;
		delete ptr_line_set;  
	}
	delete file;
}

// removes punctuation and converts all text to lowercase so that
// the queries operate in a case insensitive manner
string TextQuery::cleanup_str(const string &word)
{
	string ret;
	for (auto it = word.begin(); it != word.end(); ++it) {
		if (!ispunct(*it))
			ret += tolower(*it);
	}
	return ret;
}

QueryResult TextQuery::query(const string &sought) const
{
	// we'll return a pointer to this set if we don't find sought
	static set<line_no> nodata;

	// use find and not a subscript to avoid adding words to wm!
	auto loc = wm.find(cleanup_str(sought));

	if (loc == wm.end())
		return QueryResult(sought, &nodata, file);  // not found
	else 
		return QueryResult(sought, loc->second, file);
}

ostream &print(ostream & os, const QueryResult &qr)
{
	// if the word was found, print the count and all occurrences
	os << qr.sought << " occurrences: " << qr.lines->size() << endl;
	// print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set 
		os << "\t(line " << num + 1 << ") " << qr.file->at(num) << endl;

	return os;
}

// debugging routine
void TextQuery::display_map()
{
	for (auto map_item : wm) {
		cout << "word \'" << map_item.first << "\' appears in lines { ";
		
		auto ptr_line_set = map_item.second;
		// print all line numbers for this word
		for (auto line_num : *ptr_line_set) {
			cout << line_num << " ";
		}
		cout << "}\n";  // end list of output this word
	}
	cout << endl;  // finished printing entire map
}
