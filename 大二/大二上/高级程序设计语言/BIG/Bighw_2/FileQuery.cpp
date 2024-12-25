#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

bool compareByFrequency(const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second;}//比较函数，按频率降序排列

class FileQuery {// FileQuery类定义
private:
    vector<string> sentences_;
    map<string, int> word_count_;
    map<string, vector<pair<int, int> > > word_positions_;
    string processString(const string& str) {// 一次性处理字符串，转小写并移除标点
        string result;
        for (char c : str) {
            if (isalpha(c)) result += tolower(c);//如果是字母，转小写
            else if (c == ',' || c == '.' || isspace(c)) result += c;//如果是逗号、句号或者空格，保留
            else result += ' ';//否则不给你好果子吃，替换成空格
        }
        return result;
    }

    void processFile(const string& filename) {
        ifstream file(filename);
        if (!file) return;

        string line;
        string current_sentence;
        int line_count = 0, word_pos = 0;
        
        while (line_count < 2 && getline(file, line)) line_count++;// 标题和作者当然不是正文，跳过

        while (getline(file, line)) {// 处理正文
            if (line.empty()) continue;
            
            line = processString(line);
            istringstream iss(line);
            string word;
            
            while (iss >> word) {
                if (word == "," || word == ".") {
                    if (!current_sentence.empty()) {
                        sentences_.push_back(current_sentence);//句子结束，加入句子列表
                        current_sentence.clear();
                        word_pos = 0;
                    }
                } else {
                    current_sentence += word + " ";
                    word_count_[word]++;
                    word_positions_[word].push_back(make_pair(sentences_.size(), word_pos++));//记录单词位置
                }
            }
        }
        if (!current_sentence.empty()) sentences_.push_back(current_sentence);//最后一句，加入句子列表
    }

public:
    FileQuery(const string& filename) {processFile(filename);}//构造函数

    void PrintSentences() const {for (const auto& s : sentences_) cout << s << '\n';}//打印句子

    void PrintSentencesAscend() {//按字典序打印句子
        vector<string> sorted = sentences_;
        sort(sorted.begin(), sorted.end());
        for (const auto& s : sorted) cout << s << '\n';
    }

    void PrintWordCount() const {//打印单词频率
        for (const auto& p : word_count_) cout << p.first << ": " << p.second << '\n';
    }

    void PrintTopWordContext(int n) {//打印频率最高的n个单词的上下文
        vector<pair<string, int> > words(word_count_.begin(), word_count_.end());
        sort(words.begin(), words.end(), compareByFrequency);
        
        for (int i = 0; i < min(n, static_cast<int>(words.size())); i++) {
            const auto& word = words[i].first;
            cout << "\nWord: " << word << " (frequency: " << words[i].second << ")\n";
            
            for (const auto& pos : word_positions_[word]) {
                istringstream iss(sentences_[pos.first]);//将句子分割成单词
                vector<string> words;
                string w;//单词
                while (iss >> w) words.push_back(w);//当单词不为空时，就给你加入单词列表
                
                if (pos.second > 0) cout << words[pos.second - 1] << " ";
                cout << word << " ";
                if (pos.second < words.size() - 1) cout << words[pos.second + 1];
                cout << '\n';
            }
        }
    }

    void Find(const string& target) {//查找包含目标单词的句子
        for (size_t i = 0; i < sentences_.size(); i++) {
            if (sentences_[i].find(target) != string::npos) {
                cout << "Line " << (i + 1) << ": " << sentences_[i] << '\n';
            }
        }
    }

    void Replace(const string& old_word, const string& new_word) {
        for (auto& sentence : sentences_) {
            size_t pos = 0;
            while ((pos = sentence.find(old_word, pos)) != string::npos) {
                sentence.replace(pos, old_word.length(), new_word);
                pos += new_word.length();
            }
        }
    }
};

int main() {
    try {
        FileQuery fq("poem.txt");
        
        cout << "=== Original sentences ===\n";
        fq.PrintSentences();
        cout << "\n=== Word counts ===\n";
        fq.PrintWordCount();
        cout << "\n=== Top 3 words context ===\n";
        fq.PrintTopWordContext(3);
        cout << "\n=== Finding 'captain' ===\n";
        fq.Find("captain");
        cout << "\n=== Replacing 'captain' with 'John Keating' ===\n";//我最喜欢的电影《死亡诗社》，致敬永远的John Keating老师，O Captain! My Captain!
        fq.Replace("captain", "John Keating");
        cout << "\n=== Replaced sentences ===\n";
        fq.PrintSentences();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;//不对劲，返回1
    }
    return 0;
}