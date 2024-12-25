#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "QueryResult.h"

class QueryResult; // declaration needed for return type in the query function
class TextQuery {
public:

	typedef std::vector<std::string>::size_type line_no;

	TextQuery(std::ifstream&);
	~TextQuery();
	QueryResult query(const std::string&) const;
	void display_map();        // debugging aid: print the map

private:
	std::vector<std::string> *file; // input file	

	// maps each word to the set of the lines in which that word appears
	std::map<std::string, std::set<line_no>*> wm; //word map

	// canonicalizes text: removes punctuation and makes everything lower case
	static std::string cleanup_str(const std::string&);
};
#endif