#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <iostream>

typedef std::vector<std::string> line_str_vec;  //a vector of lines (i.e., strings)
typedef line_str_vec::size_type line_no;        //line index
typedef std::shared_ptr<std::set<line_no>> ptr_line_no_set; 
typedef std::shared_ptr<line_str_vec> ptr_line_str_vec; 
typedef std::set<line_no>::size_type line_set_size;
typedef std::set<line_no>::const_iterator line_set_iter;

class QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);

public:
	QueryResult() {};
	QueryResult(std::string s, ptr_line_no_set p,	ptr_line_str_vec f) :
		word(s), lines(p), file(f) { }

	line_set_size size() const  { return lines->size(); }
	line_set_iter begin() const { return lines->cbegin(); }
	line_set_iter end() const   { return lines->cend(); }
	ptr_line_str_vec get_file() { return file; }

private:
	std::string word;  // word this query represents
	ptr_line_no_set lines = nullptr; // indices of lines the word is on
	ptr_line_str_vec file = nullptr;  //input file
};

std::ostream &print(std::ostream&, const QueryResult&);
#endif