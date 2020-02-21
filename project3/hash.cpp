#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

class node {
public:
	string key;
	vector<int> lines;	
	int n;
	int col;
	node(string key1, int line1) {
		col=0;
		n=0;
		lines.push_back(line1);
		key=key1;
		n++;
	}
};

class Map {
private:
	node **table;
public:
	int size;
	Map(int size1) {
		size=size1;
		table = new node*[size1];
		for (int i=0; i < size; i++) {
			table[i] = NULL;
		}
	}
	
	~Map() {
		for(int i=0; i < size; i++) {
			if(table[i]) {
				delete table[i];
			}
		}
		delete[] table;
	}
	
	unsigned long djb2(string str) {
		unsigned long hash = 5381;
		int c;
		for(int i=0; i < str.length(); i++) {
			c = (int) str[i];
			hash = ((hash << 5) + hash) + c;
		}
		return hash;
	}

	int lp(string key, int line, int size) {
		int collisions=0;
		int flag=0;
		unsigned long hashvalue = djb2(key) % size;
		while(table[hashvalue] != NULL && table[hashvalue]->key != key) {
			hashvalue = (hashvalue + 1) % size;
			collisions++;
		}
		if(table[hashvalue] == NULL) {
			flag=1;
			table[hashvalue]=new node(key, line);
			table[hashvalue]->col=collisions;
			return flag;
		}
		if(table[hashvalue]->key == key) {
			flag=2;
			int n=table[hashvalue]->n;
			table[hashvalue]->lines.push_back(line);
			n++;
			table[hashvalue]->n=n;
			table[hashvalue]->col=(table[hashvalue]->col) + collisions;
			return flag;
		}
		return flag;
	}

	void lpsearch(string key, int size) {
		unsigned long hashvalue = djb2(key) % size;
		int col=0;
		while(table[hashvalue] != NULL && table[hashvalue]->key != key) {
			hashvalue=(hashvalue+1) % size;
			col++;
		}
		if(table[hashvalue] == NULL) {
			cout << key << " appears on lines []" << endl;
			cout << "The search had " << col << " collisions" << endl << endl;
			return;
		}
		if(table[hashvalue]->key == key) {
			int n=table[hashvalue]->n;
			cout << key << " appears on lines [";
			for(int i=0; i < n; i++) {
				if(table[hashvalue]->lines[i] != 0) {
					if(i > 0) {
						cout << ",";
					}
					cout << table[hashvalue]->lines[i];
				}
			}
			cout << "]" << endl;
				cout << "The search had " << col << " collisions" << endl << endl;
				return;
			}
			return;
		}
		
	int qp(string key, int line, int size) {
		int collisions=0;
		int flag=0;
		int hash = djb2(key) % size;
		int qhash=hash;
		while(table[qhash] != NULL && table[qhash]->key != key) {
			collisions++;
			qhash = (hash + ((int)pow(collisions,2))) % size;
		}
		if(table[qhash] == NULL) {
			flag = 1;
			table[qhash] = new node(key, line);
			table[qhash]->col=collisions;
			return flag;
		}
		if(table[qhash]->key == key) {
			flag = 2;
			int n=table[qhash]->n;
			table[qhash]->lines.push_back(line);
			n++;
			table[qhash]->n=n;
			table[qhash]->col = (table[qhash]->col) + collisions;
			return flag;
		}
		return flag;	
	}	

	void qpsearch(string key, int size) {
		int hash = djb2(key) % size;
		int col=0;
		int qhash=hash;
		while(table[qhash] != NULL && table[qhash]->key != key) {
			col++;
			qhash = (hash + ((int)pow(col,2))) % size;
		}
		if(table[qhash] == NULL) {
			cout << key << " appears on lines []" << endl;
			cout << "The search had " << col << " collisions" << endl << endl;
			return;
		}
		if(table[qhash]->key == key) {
			int n=table[qhash]->n;
			cout << key << " appears on lines [";
			for(int i=0; i < n; i++) {
				if(table[qhash]->lines[i] != 0) {
					if(i > 0) {
						cout << ",";
					}
					cout << table[qhash]->lines[i];
				}
			}
			cout << "]" << endl;
			cout << "The search had " << col << " collisions" << endl << endl;
			return;
		}
		return;
	}

	int dh(string key, int line, int size, int a) {
		int col=0;
		int flag=0;
		unsigned long hash = djb2(key) % size;
		unsigned long dhash = hash;
		while(table[dhash] != NULL && table[dhash]->key != key) {
			dhash = (dhash + (a - (hash % a))) % size;
			col++;
		}
		if(table[dhash] == NULL) {
			flag=1;
			table[dhash]= new node(key, line);
			table[dhash]->col=col;
			return flag;
		}
		if(table[dhash]->key == key) {
			flag=2;
			int n=table[dhash]->n;
			table[dhash]->lines.push_back(line);
			n++;
			table[dhash]->n=n;
			table[dhash]->col=(table[dhash]->col) + col;
			return flag;
		}
		return flag;
	}

	void dhsearch(string key, int size, int a) {
		unsigned long hash = djb2(key) % size;
		int col=0;
		unsigned long dhash = hash;
		while(table[dhash] != NULL && table[dhash]->key != key) {
			dhash = (dhash + (a - (hash % a))) % size;
			col++;
		}
		if(table[dhash] == NULL) {
			cout << key << " appears on lines []" << endl;
			cout << "The search had " << col << " collisions" << endl << endl;
			return;
		}
		if(table[dhash]->key == key) {
			int n=table[dhash]->n;
			cout << key << " appears on lines [";
			for(int i=0; i < n; i++) {
				if(table[dhash]->lines[i] != 0) {
					if(i > 0) {
						cout << ",";
					}
					cout << table[dhash]->lines[i];
				}
			}
			cout << "]" << endl;
			cout << "The search had " << col << " collisions" << endl << endl;
			return;
		}
		return;
	}
	
	int Collisions(int size) {
		int col=0;
		for(int i=0; i<size; i++) {
			if(table[i] != NULL) {
				col=col+table[i]->col;
			}
		}
		return col;
	}
};


int main(int argc, char *argv[]) {
	int size=atoi(argv[3]);
	Map hash(size);
	string key;
	int line=1;
	string input;
	int totalwords=0;
	int uniquewords=0;
	int flag=0;
	string input2;
	string method = argv[4];
	ifstream myfile(argv[1]);
	while(getline(myfile, input)) {
		istringstream iss(input);
		while (iss >> key) {
			if(method == "lp") {
				flag = hash.lp(key, line, size);
				totalwords++;
				if(flag==1) {
					uniquewords++;
				}
			}
			if(method == "qp") {
				flag=hash.qp(key, line, size);
				totalwords++;
				if(flag==1) {
					uniquewords++;
				}
			}
			if(method == "dh") {
				flag=hash.dh(key,line,size,atoi(argv[5]));
				totalwords++;
				if(flag==1) {
					uniquewords++;
				}
			}
		}
		line++;
	}
	
	int collisions = hash.Collisions(size);
	
	cout << endl;
	cout << "The number of words found in the file was " << totalwords << endl;
	cout << "The number of unique words found in the file was " << uniquewords << endl;
	cout << "The number of collisions was " << collisions << endl << endl;
	
	ifstream query(argv[2]);
	while(getline(query, input2)) {
		istringstream ss(input2);
		while(ss >> key) {
			if(method == "lp") {
				hash.lpsearch(key,size);
			}
			if(method == "qp") {
				hash.qpsearch(key, size);
			}
			if(method == "dh") {
				hash.dhsearch(key, size, atoi(argv[5]));
			}
		}	
	}
	return 0;
}


		















