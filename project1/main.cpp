#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
	ifstream infile;
	infile.open(argv[1]);
	char ch;
	string array[10000];
	int count[10000];
	for(int b=0; b<10000; b++) {
		count[b] = 0;
	}
	int totalcount=0;
	int a=0;
	int unique=0;
	string temp;
	string find;

	while(infile.get(ch)) {
		if(isalpha(ch)) {
			temp.push_back(tolower(ch));
		}
		else {
			if(temp.size() > 0) {
				array[a]=temp;
				a++;
				temp.clear();
				totalcount++;
			}
		}
	}
	int ucount[10000];
	string uarray[10000];
	int v=0;
	int w=0;
	for(int c=0; c<totalcount; c++) {
		if(count[c]==0) {
			int wordcount=0;	
			for(int d=c; d<totalcount; d++) {
				if (array[d]==array[c]) {
					wordcount += 1;
					count[d]=1;
				}
			}
			uarray[v]=array[c];
			v++;
			ucount[w]=wordcount;
			w++;
			unique++;
		}
	}

	cout << "The number of words found in the file was " << totalcount+1 << endl;
	cout << "The number of unique words found in the file was " << unique << endl;
	cout << "Please enter a word: ";
	cin >> find;

	int letters=0;
	int mycount=0;
	int flag=0;
	while(find!="END") {
		int len=find.size();
		for(int n=0; n<len; n++) {
			if(find[n] == '?') {
				flag=1;
			}
		}
		if(flag==0) {
			for(int m=0; m<totalcount; m++) {
				if(array[m] == find) {
					mycount++;
				}
			}
			cout << "The word " << find << " appears " << mycount << " times in the document" << endl;
			mycount=0;
			cout << "Please enter a word: ";
			cin >> find;
		}
		int flag2=0;
		if(flag==1) {
			for(int p=0; p<unique; p++) {
				string str=uarray[p];
				int leng=str.size();
				if(len==leng) {
					for (int o=0; o<len; o++) {
						if(uarray[p].at(o) == find.at(o) || find.at(o)=='?') {
							letters++;
						}
						else {
							o=len;
							letters=0;
						}
					}
				}
				if(letters==len) {
					cout<< "The word " << uarray[p] << " appears " << ucount[p] << " times in the document" << endl;
					letters=0;
					flag2=1;
				}
			}
			if(flag2==0) {
				cout << "The word " << find << " appears 0 times in the document" << endl;
			}
			cout << "Please enter a word: ";
			cin >> find;
		}
		flag=0;
	}
					
	infile.close();
	return 0;
}
		
				
	


