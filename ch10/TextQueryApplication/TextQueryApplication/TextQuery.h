
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
class TextQuery{
public:
	typedef vector<string>::size_type line_no;
	void read_file(ifstream& is){
		store_file(is);
		build_map();
	}
	set<line_no> run_query(const string&) const{
		map<string, set<line_no> >::const_iterator
			loc = word_map.find(query_word);
		if (loc == word_map.end())
			return sec<line_no>();
		else
			return loc->second;
	};
	string text_line(line_no) const{
		if (line < lines_of_text.size())
			return lines_of_text[line];
		throw out_of_range("line number out of range");
	};
private:
	void store_file(ifstream& is){
		string textline;
		while(GetInputState(is, textline))
			lines_of_text.push_back(textline);
	};
	void build_map(){
		for (line_no line_num = 0; line_num  != lines_of_text.size(); ++line_num){
			istringstream line(lines_of_text[line_num]);
			string word;
			while(line << word)
				word_map[word].insert(line_num);
	};
	vector<string> lines_of_text;
	map<string, set<line_no> > word_map;
};

#endif
