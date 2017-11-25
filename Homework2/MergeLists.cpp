#include<iostream>

using namespace std;

struct Node
{
	int data;
	Node *next;
};

Node* MergeLists(Node* headA, Node* headB)
{
	if (headA == NULL) return headB;
	if (headB == NULL) return headA;

	Node *p = new Node;

	if (headA->data < headB->data) {
		p = headA;
		headA = headA->next;
	}
	else {
		p = headB;
		headB = headB->next;
	}
	Node *res = p;

	while (headA && headB) {
		if (headA->data < headB->data) {
			p->next = headA;
			headA = headA->next;
		}
		else if (headA->data == headB->data) {
			p->next = headA;
			headA = headA->next;
			headB = headB->next;
		}
		else {
			p->next = headB;
			headB = headB->next;
		}
		p = p->next;
	}
	while (headA) {
		p->next = headA;
		headA = headA->next;
		p = p->next;
	}
	while (headB) {
		p->next = headB;
		headB = headB->next;
		p = p->next;
	}
	return res;
}