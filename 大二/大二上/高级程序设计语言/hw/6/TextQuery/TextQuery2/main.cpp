#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>

using namespace std;

bool get_word(string &s1)
{
	cout << "enter a word to search for, or q to quit: ";
	cin >> s1;
	if (!cin || s1 == "q") return false;
	else return true;
}

bool get_words(string &s1, string &s2)
{
	// iterate with the user: prompt for a word to find and print results
	cout << "Enter two words to search for, or q to quit: ";
	cin >> s1;

	// stop if hit eof on input or a "q" is entered
	if (!cin || s1 == "q") return false;
	cin >> s2;
	return true;
}


int main(int argc, char **argv)
{
	ifstream infile;
	if (argc == 2)
		infile.open(argv[1]);

	if (!infile) {
		cerr << "No input file!" << endl;
		return -1;
	}

	TextQuery file(infile);  //内部构建好词典	

	while (true) {

		//用户输入查询单词
		string word1, word2, word3;		
		if (!get_words(word1, word2)) //get two words from cin
			break;
		cout << "Enter the third word: ";
		cin >> word3; //get the 3rd word

		//本查询树的基础查询单元，为每个查询单词构造一个
		ptr_query_base q1 = std::make_shared<WordQuery>(word1);
		ptr_query_base q2 = std::make_shared<WordQuery>(word2);
		ptr_query_base q3 = std::make_shared<WordQuery>(word3);

		//构建查询树
		ptr_query_base query_tree = q1 & q2 | q3;
		
		//执行查询树
		QueryResult results = query_tree->do_query(file);

		//打印结果
		cout << "\nExecuting Query for: " << query_tree->query_string() << endl;
		print(cout, results) << endl;
	}
	return 0;
}