#include<iostream>
#include<list>

using namespace std;

struct Node
{
	int data;
	struct Node *next;
};

Node* RemoveDuplicates(Node *head)
{
	if (head == NULL || head->next == NULL) return head;

	Node *p = head;
	while (p) {
		if (p->data != p->next->data) {
			p = p->next;
		}
		else {
			Node *q = p->next;
			p->next = p->next->next;
			delete q;
		}
	}
	return head;
}

int main()
{
	list<int> li;
	li.push_back(1);
	li.push_back(1);
	li.push_back(3);
	li.push_back(3);
	li.push_back(5);
	li.push_back(6);
	while (!li.empty()) {
		cout << li.front() << " ";
		li.pop_front();
	}
	cout << endl;

	system("pause");
	return 0;
}
