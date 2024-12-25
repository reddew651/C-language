#include "TextQuery.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

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
			auto &lines = wm[word]; // lines is a shared_ptr 
			if (!lines) // that pointer is null the first time we see word
				lines.reset(new set<line_no>); // allocate a new set
			lines->insert(n);      // insert this line number
		}
	}
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

QueryResult
TextQuery::query(const string &word) const
{
	// we'll return a pointer to this set if we don't find word
	static shared_ptr<set<line_no>> nodata(new set<line_no>);

	// use find and not a subscript to avoid adding words to wm!
	auto loc = wm.find(cleanup_str(word));

	if (loc == wm.end())
		return QueryResult(word, nodata, file);  // not found
	else
		return QueryResult(word, loc->second, file);
}

ostream &print(ostream & os, const QueryResult &qr)
{
	if (!qr.lines) 
		return os;

	// if the word was found, print the count and all occurrences
	os << qr.word << " occurrences " << qr.lines->size() << endl;

	// print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set 
		// don't confound the user with text lines starting at 0
		os << "\t(line " << num + 1 << ") "
		<< *(qr.file->begin() + num) << endl;

	return os;
}

// debugging routine, not covered in the book
void TextQuery::display_map()
{
	for (auto map_item : wm) {
		cout << "word: " << map_item.first << " {";
		// fetch location vector as a const reference to avoid copying it
		auto text_locs = map_item.second;
		// print all line numbers for this word
		for (auto line_no_item : *text_locs) {
			cout << line_no_item << " ";
		}
		cout << "}\n";  // end list of output this word
	}
	cout << endl;  // finished printing entire map
}
