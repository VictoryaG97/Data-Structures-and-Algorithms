#include<iostream>

using namespace std;

struct Node
{
	int data;
	Node *prev;
	Node *next;
};

Node* Reverse(Node *head)
{
	if (head == NULL) return head;
	if (head->next == NULL) {
		head->next = head->prev;
		head->prev = NULL;
		return head;
	}

	Node *nextPtr = head->next;
	Node *prevPtr = head->prev;
	head->next = prevPtr;
	head->prev = nextPtr;
	
	return Reverse(nextPtr);
}