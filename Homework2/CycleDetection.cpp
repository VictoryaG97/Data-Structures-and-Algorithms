#include<iostream>

using namespace std;

struct Node
{
	int data;
	Node *next;
};

bool has_cycle(Node *head)
{
	if (head == NULL || head->next == NULL) return false;

	Node *p = head;
	Node *q = head;

	while (p != NULL && p->next != NULL) {
		q = q->next;
		p = p->next->next;

		if (p == q)
			return true;
	}
	return false;
}