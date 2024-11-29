#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // ��������
using namespace std;

class NameList {
private:
	vector<string> names; // �����б�

public:
	// ���캯��
	NameList() {
		cout << "NameList constructed." << endl;
	}

	// ��������
	~NameList() {
		cout << "NameList destructed." << endl;
	}

	// �������캯��
	NameList(const NameList& other) : names(other.names) {
		cout << "NameList copy constructed." << endl;
	}

	// ��ֵ����
	NameList& operator=(const NameList& other) {
		if (this == &other) return *this; // ��ֹ���Ҹ�ֵ
		names = other.names;
		cout << "NameList assignment operator." << endl;
		return *this;
	}

	// �������
	void addName(const string& name) {
		names.push_back(name);
	}

	// ɾ������
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

	// ���Ұ������ַ���������
	vector<string> search(const string& substr) const {
		vector<string> results;
		for (const auto& name : names) {
			if (name.find(substr) != string::npos) {
				results.push_back(name);
			}
		}
		return results;
	}

	// ��ӡ�����б�
	void print(int order = 0) const {
		vector<string> sortedNames = names;

		if (order == 1) {
			sort(sortedNames.begin(), sortedNames.end()); // ��������
		}
		else if (order == 2) {
			sort(sortedNames.begin(), sortedNames.end(), greater<string>()); // ��������
		}

		for (const auto& name : sortedNames) {
			cout << name << endl;
		}
	}
};

// ����������
int main() {
	NameList nameList;

	// �������
	nameList.addName("Zhang San");
	nameList.addName("Li Si");
	nameList.addName("Wang Wu");
	nameList.addName("Zhao Liu");
	nameList.addName("Chen Qi");

	// ��ӡԭʼ˳��
	cout << "Original order:" << endl;
	nameList.print();

	// ɾ��һ������
	nameList.deleteName("Wang Wu");

	// ��ӡɾ������б�
	cout << "\nAfter deletion:" << endl;
	nameList.print();

	// ���Ұ��� "Zhang" ������
	vector<string> searchResults = nameList.search("Zhang");
	cout << "\nSearch results for 'Zhang':" << endl;
	for (const auto& name : searchResults) {
		cout << name << endl;
	}

	// �������ӡ
	cout << "\nAscending order:" << endl;
	nameList.print(1);

	// �������ӡ
	cout << "\nDescending order:" << endl;
	nameList.print(2);

	return 0;
}
