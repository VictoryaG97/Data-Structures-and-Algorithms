#include <iostream>
#include <stack>

using namespace std;

class Queue
{
	stack<int> inbox;
	stack<int> outbox;

public:

	void enqueue(int item)
	{
		inbox.push(item);
	}
	int dequeue()
	{
		if (outbox.empty()) {
			while (!inbox.empty())
			{
				outbox.push(inbox.top());
				inbox.pop();
			}
		}
		int top = outbox.top();
		outbox.pop();
		if (inbox.empty()) {
			while (!outbox.empty()) {
				inbox.push(outbox.top());
				outbox.pop();
			}
		}
		return top;
	}
	int top()
	{
		if (outbox.empty()) {
			while (!inbox.empty())
			{
				outbox.push(inbox.top());
				inbox.pop();
			}
		}
		int top = outbox.top();
		if (inbox.empty()) {
			while (!outbox.empty()) {
				inbox.push(outbox.top());
				outbox.pop();
			}
		}
		return top;
	}
	void print()
	{
		if (outbox.empty()) {
			while (!inbox.empty()) {
				outbox.push(inbox.top());
				inbox.pop();
			}
		}
		while (!outbox.empty()) {
			cout << outbox.top();
			outbox.pop();
		}
	}
};

int main()
{
	Queue queue;
	int n;
	cin >> n;
	int* result = new int[n];
	int index = 0;
	int type, element;

	for (int i = 0; i < n; i++) {

		cin >> type;

		if (type == 1) {
			cin >> element;
			queue.enqueue(element);
		}
		else if (type == 2) {
			queue.dequeue();
		}
		else {
			result[index] = queue.top();
			index++;
		}
	}

	for (int i = 0; i < index; i++) {
		cout << result[i] << endl;
	}

	system("pause");
	return 0;
}