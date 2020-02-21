#include <iostream>
using namespace std;

class node {
public:
	int key;
	char type;
	node *next;
	node *prev;
	node(int newkey, char newtype, node* next1=NULL, node* prev1=NULL) {
		key=newkey;
		type=newtype;
		next=next1;
		prev=prev1;
	}
};


class dList {
	private:
		node* head = NULL;
		node* tail = NULL;
		int size;
	public:
		dList() {
			head = tail = NULL;
			size = 0;
		}

		dList(int keyarray[], char typearray[], int arraysize) {
			size=0;
			for(int i=0; i < arraysize; i++) {
				if(size == 0) {
					tail = new node(keyarray[i],typearray[i]);
					head = tail;
					++size;
				}
				else {
					node *temp = new node(keyarray[i],typearray[i], NULL, tail);
					tail->next=temp;
					tail = temp;
					size++;
				}
			}
		}
			
		~dList() {
			node* current = head;
			while(current) {
				node* next = current->next;
				delete current;
				current = next;
			}
		}
			
		void addFront(int newkey, char newtype) {
			if(size == 0) {
				head = new node(newkey, newtype);
				tail = head;
				++size;
				return;
			}
			node *temp = new node(newkey, newtype, head);
			head->prev = temp;
			head = temp;
			size++;
			return;
		}

		void addBack(int newkey, char newtype) {
			if(size == 0) {
				tail = new node(newkey, newtype);
				head=tail;
				++size;
				return;
			}
			node *temp = new node(newkey, newtype, NULL, tail);
			tail->next=temp;
			tail=temp;
			size++;
			return;
		}

		node *search(int searchkey) {
			node* ptr;
			ptr=head;
			while(ptr != NULL) {
				if(ptr->key == searchkey) {
					return ptr;
				}
				else {
					ptr=ptr->next;
				}
			}
		}
			
		void find(char searchtype) {
			node* ptr=head;
			while(ptr != NULL) {
				if(ptr->type == searchtype) {
					cout << ptr->key << " " << ptr->type << " ";
					ptr=ptr->next;
				}
				else {
					ptr=ptr->next;
				}
			}
			cout << endl;
			return;
		}

		void moveFront(node *newfront) {
			if(newfront == head) {
				return;
			}
			else if(newfront == tail) {
				newfront->prev->next = NULL;
				tail = newfront->prev;
			}
			else {
				newfront->prev->next=newfront->next;
				newfront->next->prev=newfront->prev;
			}
			head->prev=newfront;
			newfront->next=head;
			newfront->prev=NULL;
			head=newfront;
			return;
		}

		void moveBack(node *newback) {
			if(newback == head) {
				newback->next->prev = NULL;
				head = newback->next;
			}
			else if(newback == tail) {
				return;
			}
			else{
				newback->prev->next=newback->next;
				newback->next->prev=newback->prev;
			}
			tail->next=newback;
			newback->prev=tail;
			newback->next=NULL;
			tail=newback;
			return;
		}

		void out(int output, char forb = 'f') {
			if(forb == 'f') {
				node *ptr = head;
				if(output <= size) {
					for(int i=0; i < output; i++) {
						cout << ptr->key << " " << ptr->type << " ";
						ptr=ptr->next;
					}
				}
				else {
					for(int l=0; l<size; l++) {
						cout<<ptr->key<<" "<<ptr->type<<" ";
						ptr=ptr->next;	
					}
				}
				cout << endl;
				return;
			}
			if(forb == 'b') {
				node *ptr2 = tail;
				if(output <= size) {
					for(int j=0; j<output; j++) {
						cout << ptr2->key << " " << ptr2->type << " ";
						ptr2=ptr2->prev;
					}
				}
				else {
					for(int k=0; k<size; k++) {
						cout<<ptr2->key<<" "<<ptr2->type<<" ";
						ptr2=ptr2->prev;
					}
				}
				cout << endl;
				return;
			}
		}
		
		void sort() {
			head = mergesort(head);
			node* ptr=head;
			while(ptr != NULL) {
				if(ptr->next == NULL) {
					tail=ptr;
				}
				ptr=ptr->next;
			}
			return;
		}
			

		node *merge(node* first, node* second) {
			if(!first) {
				return second;
			}
			if(!second) {
				return first;
			}
			if(first->key <= second->key) {
				first->next=merge(first->next, second);
				first->next->prev = first;
				first->prev=NULL;
				return first;
			}
			else{
				second->next=merge(first, second->next);
				second->next->prev=second;
				second->prev=NULL;
				return second;
			}
		}

		node *mergesort(node *head) {
			if(!head || !head->next) {
				return head;
			}
			node* second = split(head);
			head = mergesort(head);
			second = mergesort(second);
			return merge(head, second);
		}

		node *split(node *head) {
			node *fast=head, *slow=head;
			while(fast->next && fast->next->next) {
				fast = fast->next->next;
				slow=slow->next;
			}
			node *temp=slow->next;
			slow->next=NULL;
			return temp;
		}	
};
