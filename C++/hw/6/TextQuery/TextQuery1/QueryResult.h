#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <iostream>

class QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);

public:
	typedef std::vector<std::string>::size_type line_no;

	QueryResult(std::string s, std::set<line_no>* p, std::vector<std::string> *f) :
		sought(s), lines(p), file(f) {}

private:
	std::string sought;  // word this query represents
	std::set<line_no> *lines; // lines it's on
	std::vector<std::string> *file;  //input file
};

#endif