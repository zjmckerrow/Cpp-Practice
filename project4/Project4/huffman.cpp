#include <iostream>
#include <fstream>
using namespace std;
class node {
public:
	int freq;
	int ch;
	node* left;
	node* right;
	node(int freq, int ch) {
		freq=freq;
		ch=ch;
		left=right=NULL;
	}
};
class minheap {
public:
	int *headfreq;
	int *headch;
	int capacity;
	int chsize;	
	int freqsize;
	int parent(int i) {
		return (i-1)/2;
	}
	int left(int i) {
		return (2*i + 1);
	}
	int right(int i) {
		return (2*i +2);
	}
	int getmin() {
		return headfreq[0];
	}
	minheap(int cap) {
		capacity=cap;
		freqsize=0;
		chsize=0;
		headfreq = new int[cap];
		headch = new int[cap];
	}
	~minheap() {
		delete headfreq;
		delete headch;
	}
	void insert(int ch, int freq) {
		freqsize++;
		chsize++;
		int i = freqsize-1;
		int j = chsize-1;
		headfreq[i]=freq;
		headch[j]=ch;
		while(i != 0 && headfreq[parent(i)] > headfreq[i]) {
			swap(&headfreq[i], &headfreq[parent(i)]);
			swap(&headch[j], &headch[parent(j)]);
			i=parent(i);
			j=parent(j);
		}
		return;
	}
	int extractmin(int i) {
		if(i==1) {
			if (freqsize == 1) {
				freqsize--;
				return headfreq[0];
			}
			int rootfreq = headfreq[0];
			headfreq[0]=headfreq[freqsize-1];
			freqsize--;
			minheapify(0);
			return rootfreq;
		}
		if(i==0) {
			if(chsize==1) {
				chsize--;
				return headch[0];
			}
			int rootch = headch[0];
			headch[0]=headch[chsize-1];
			chsize--;
			minheapify(0);
			return rootch;
		}
	}
	void minheapify(int i) {
		int l=left(i);
		int r=right(i);
		int smallest=i;
		if(l < freqsize && headfreq[l] < headfreq[i]) {
			smallest = l;
		}
		if(r < freqsize && headfreq[r] < headfreq[smallest]) {
			smallest = r;
		}
		if(smallest != i) {
			swap(&headfreq[i], &headfreq[smallest]);
			swap(&headch[i], &headch[smallest]);
			minheapify(smallest);
		}
		return;
	}
	void swap(int *x, int *y) {
		int temp = *x;
		*x=*y;
		*y=temp;
		return;
	}	
};		
class huffman {
public:
	node* root;
	int internalch;
	huffman() {
		root = NULL;
		internalch = 128;
	}
	~huffman() {
		delete root;
	}
	node* search(int freq, int ch) {
		node* temp = root;
		while(temp != NULL) {
			if(temp->freq == freq) {
				if(temp->ch == ch)
					return temp;
			}
			if(freq > temp->freq) {
				temp = temp->right;
			}
			else {
				if(freq < temp->freq) {
					temp = temp->right;
				}
			}
		}
		return NULL;
	}	
	void insert(minheap* heap) {
		while(heap->chsize != 0 && heap->freqsize != 0) {
			int freq1 = heap->extractmin(1);
			int ch1 = heap->extractmin(0);
			int freq2 = heap->extractmin(1);
			int ch2 = heap->extractmin(0);
			int ifreq = freq1+freq2;
			node* internal = new node(ifreq, internalch);
			internalch++;
			root = internal;
			node* test = search(freq1,ch1);
			if(test == NULL) {
				node* left = new node(freq1, ch1);
				internal->left = left;
			}
			else {
				internal->left = test;
			}
			node* test2 = search(freq2,ch2);
			if(test2 == NULL) {
				node* right = new node(freq2, ch2);
				internal->right = right;
			}
			else {
				internal->right = test2;
			}
			heap->insert(internalch, ifreq);
		}
	}
				
};				
	
int main(int argc, char *argv[]) {
	int nodes=0;
	int array[128]; // number of occurrences stored in ascii value spot
	for(int i=0; i<128; i++) {
		array[i]=0;
	}
	ifstream in(argv[1]);
	char ascii;
	int lines=0;
	while(in.get(ascii)) {
		array[(int)ascii]++;
		nodes++;
	}
	minheap heap(nodes);
	for(int j=0; j<128; j++) {
		if(array[j] != 0) {
			heap.insert(j, array[j]);
		}
	}
	huffman huff;
	minheap* heapptr;
	huff.insert(heapptr);
	return 0;
}
			
