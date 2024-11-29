#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

bool compareByFrequency(const std::pair<std::string, int>& a, 
                       const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

class FileQuery {
private:
    std::vector<std::string> sentences_;
    std::map<std::string, int> word_count_;
    std::map<std::string, std::vector<std::pair<int, int> > > word_positions_;

    // 一次性处理字符串：转小写并移除标点
    std::string processString(const std::string& str) {
        std::string result;
        for (char c : str) {
            if (std::isalpha(c)) {
                result += std::tolower(c);
            } else if (c == ',' || c == '.' || std::isspace(c)) {
                result += c;
            } else {
                result += ' ';
            }
        }
        return result;
    }

    void processFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) return;

        std::string line;
        std::string current_sentence;
        int line_count = 0, word_pos = 0;
        
        // 跳过标题和作者
        while (line_count < 2 && std::getline(file, line)) line_count++;

        // 处理正文
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            line = processString(line);
            std::istringstream iss(line);
            std::string word;
            
            while (iss >> word) {
                if (word == "," || word == ".") {
                    if (!current_sentence.empty()) {
                        sentences_.push_back(current_sentence);
                        current_sentence.clear();
                        word_pos = 0;
                    }
                } else {
                    current_sentence += word + " ";
                    word_count_[word]++;
                    word_positions_[word].push_back(std::make_pair(sentences_.size(), word_pos++));
                }
            }
        }
        
        if (!current_sentence.empty()) {
            sentences_.push_back(current_sentence);
        }
    }

public:
    FileQuery(const std::string& filename) {
        processFile(filename);
    }

    void PrintSentences() const {
        for (const auto& s : sentences_) std::cout << s << '\n';
    }

    void PrintSentencesAscend() {
        std::vector<std::string> sorted = sentences_;
        std::sort(sorted.begin(), sorted.end());
        for (const auto& s : sorted) std::cout << s << '\n';
    }

    void PrintWordCount() const {
        for (const auto& p : word_count_) {
            std::cout << p.first << ": " << p.second << '\n';
        }
    }

    void PrintTopWordContext(int n) {
        std::vector<std::pair<std::string, int> > words(word_count_.begin(), word_count_.end());
        std::sort(words.begin(), words.end(), compareByFrequency);
        
        for (int i = 0; i < std::min(n, static_cast<int>(words.size())); i++) {
            const auto& word = words[i].first;
            std::cout << "\nWord: " << word << " (frequency: " << words[i].second << ")\n";
            
            for (const auto& pos : word_positions_[word]) {
                std::istringstream iss(sentences_[pos.first]);
                std::vector<std::string> words;
                std::string w;
                while (iss >> w) words.push_back(w);
                
                if (pos.second > 0) std::cout << words[pos.second - 1] << " ";
                std::cout << word << " ";
                if (pos.second < words.size() - 1) std::cout << words[pos.second + 1];
                std::cout << '\n';
            }
        }
    }

    void Find(const std::string& target) {
        for (size_t i = 0; i < sentences_.size(); i++) {
            if (sentences_[i].find(target) != std::string::npos) {
                std::cout << "Line " << (i + 1) << ": " << sentences_[i] << '\n';
            }
        }
    }

    void Replace(const std::string& old_word, const std::string& new_word) {
        for (auto& sentence : sentences_) {
            size_t pos = 0;
            while ((pos = sentence.find(old_word, pos)) != std::string::npos) {
                sentence.replace(pos, old_word.length(), new_word);
                pos += new_word.length();
            }
        }
    }
};

int main() {
    try {
        FileQuery fq("poem.txt");
        
        std::cout << "=== Original sentences ===\n";
        fq.PrintSentences();
        
        std::cout << "\n=== Word counts ===\n";
        fq.PrintWordCount();
        
        std::cout << "\n=== Top 3 words context ===\n";
        fq.PrintTopWordContext(3);
        
        std::cout << "\n=== Finding 'captain' ===\n";
        fq.Find("captain");
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}