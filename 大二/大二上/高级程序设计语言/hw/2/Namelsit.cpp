#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // 用于排序
using namespace std;

class NameList {
private:
	vector<string> names; // 名字列表

public:
	// 构造函数
	NameList() {
		cout << "NameList constructed." << endl;
	}

	// 析构函数
	~NameList() {
		cout << "NameList destructed." << endl;
	}

	// 拷贝构造函数
	NameList(const NameList& other) : names(other.names) {
		cout << "NameList copy constructed." << endl;
	}

	// 赋值重载
	NameList& operator=(const NameList& other) {
		if (this == &other) return *this; // 防止自我赋值
		names = other.names;
		cout << "NameList assignment operator." << endl;
		return *this;
	}

	// 添加名字
	void addName(const string& name) {
		names.push_back(name);
	}

	// 删除名字
	void deleteName(const string& name) {
		auto it = find(names.begin(), names.end(), name);
		if (it != names.end()) {
			names.erase(it);
			cout << "Deleted name: " << name << endl;
		}
		else {
			cout << "Name not found: " << name << endl;
		}
	}

	// 查找包含子字符串的名字
	vector<string> search(const string& substr) const {
		vector<string> results;
		for (const auto& name : names) {
			if (name.find(substr) != string::npos) {
				results.push_back(name);
			}
		}
		return results;
	}

	// 打印名字列表
	void print(int order = 0) const {
		vector<string> sortedNames = names;

		if (order == 1) {
			sort(sortedNames.begin(), sortedNames.end()); // 升序排序
		}
		else if (order == 2) {
			sort(sortedNames.begin(), sortedNames.end(), greater<string>()); // 降序排序
		}

		for (const auto& name : sortedNames) {
			cout << name << endl;
		}
	}
};

// 测试主函数
int main() {
	NameList nameList;

	// 添加名字
	nameList.addName("Zhang San");
	nameList.addName("Li Si");
	nameList.addName("Wang Wu");
	nameList.addName("Zhao Liu");
	nameList.addName("Chen Qi");

	// 打印原始顺序
	cout << "Original order:" << endl;
	nameList.print();

	// 删除一个名字
	nameList.deleteName("Wang Wu");

	// 打印删除后的列表
	cout << "\nAfter deletion:" << endl;
	nameList.print();

	// 查找包含 "Zhang" 的名字
	vector<string> searchResults = nameList.search("Zhang");
	cout << "\nSearch results for 'Zhang':" << endl;
	for (const auto& name : searchResults) {
		cout << name << endl;
	}

	// 按升序打印
	cout << "\nAscending order:" << endl;
	nameList.print(1);

	// 按降序打印
	cout << "\nDescending order:" << endl;
	nameList.print(2);

	return 0;
}
