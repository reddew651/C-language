#ifndef QUERY_H
#define QUERY_H

#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>


class Query_base {
public:
	virtual ~Query_base() {}

	//查询的字符串表示，如"him & walk"
	virtual std::string query_string() const { return ""; }

	//执行查询(树)，返回匹配结果
	virtual QueryResult do_query(const TextQuery&) const { return QueryResult(); }
};

typedef std::shared_ptr<Query_base> ptr_query_base;

//基础查询单元，同时也是查询树上的叶子节点
class WordQuery : public Query_base {

public:
	WordQuery(const std::string &s) : query_word(s) { }

	QueryResult do_query(const TextQuery &t) const
	{
		return t.query(query_word);
	}
	std::string query_string() const { return query_word; }

private:
	std::string query_word;   // word for which to search 
};

//取反查询
class NotQuery : public Query_base {
	friend ptr_query_base operator~(const ptr_query_base);
	NotQuery(const ptr_query_base q) : query(q) { }

	// concrete class: NotQuery defines all inherited pure virtual functions
	std::string query_string() const 
	{ 
		return "~(" + query->query_string() + ")"; 
	}
	QueryResult do_query(const TextQuery&) const;
	ptr_query_base query;
};

//二元查询基类
class BinaryQuery : public Query_base {
protected:
	BinaryQuery(ptr_query_base left, ptr_query_base right, std::string s) :
		left_operand(left), right_operand(right), operator_symbol(s) { }

	std::string query_string() const {
		return "(" + left_operand->query_string() + " "
			+ operator_symbol + " "
			+ right_operand->query_string() + ")";
	}

	ptr_query_base left_operand;
	ptr_query_base right_operand;
	std::string operator_symbol; // e.g., "&"
};

//与查询
class AndQuery : public BinaryQuery {
	friend ptr_query_base operator&(const ptr_query_base, const ptr_query_base);
	AndQuery(ptr_query_base left, ptr_query_base right) :
		BinaryQuery(left, right, "&") { }

	// concrete class: AndQuery inherits rep and defines the remaining pure virtual
	QueryResult do_query(const TextQuery&) const;
};

//或查询
class OrQuery : public BinaryQuery {
	friend ptr_query_base operator|(ptr_query_base, ptr_query_base);
	OrQuery(ptr_query_base left, ptr_query_base right) :
		BinaryQuery(left, right, "|") { }

	QueryResult do_query(const TextQuery&) const;
};

inline ptr_query_base operator&(ptr_query_base left_operand, ptr_query_base right_operand)
{
	return std::shared_ptr<AndQuery>(new AndQuery(left_operand, right_operand));
}

inline ptr_query_base operator|(ptr_query_base left_operand, ptr_query_base right_operand)
{
	return std::shared_ptr<OrQuery>(new OrQuery(left_operand, right_operand));
}

inline ptr_query_base operator~(ptr_query_base operand)
{
	return std::shared_ptr<NotQuery>(new NotQuery(operand));
}

std::ostream &print(std::ostream&, const QueryResult&);

#endif