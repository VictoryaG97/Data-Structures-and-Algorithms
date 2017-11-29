#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node* next;
};

template <typename T>
class LQueue
{
	Node<T> *front, *back;

	void copy(LQueue<T> const& lq)
	{
		if (!lq.empty()) {
			Node<T>* p = lq.front;
			while (p) {
				push(p->data);
				p = p->next;
			}
		}
	}
	void clean()
	{
		while (!empty())
			pop();
	}

public:
	LQueue() : front(NULL), back(NULL) {}
	LQueue(LQueue const& lq) : front(NULL), back(NULL)
	{
		copy(lq);
	}
	LQueue& operator=(LQueue const& lq)
	{
		if (this != &lq) {
			clean();
			copy(lq);
		}
		return *this;
	}
	~LQueue()
	{
		clean();
	}

	bool empty() const
	{
		return front == NULL;
	}
	void push(T const& x)
	{
		Node<T>* p = new Node<T>;
		p->data = x;
		p->next = NULL;
		if (!empty()) {
			back->next = p;
		}
		else
			front = p;
		back = p;
	}
	T pop()
	{
		if (empty()) {
			cerr << "Empty Queue";
			return 0;
		}
		Node<T>* p = front;
		T x = p->data;
		if (p == back) {
			front = NULL;
			back = NULL;
		}
		else
			front = p->next;
		delete p;
		return x;
	}
	T head() const
	{
		if (empty()) {
			cerr << "Empty Queue";
			return T();
		}
		return front->data;
	}

	void print()
	{
		while (!empty()) {
			cout << pop() << " ";
		}
		cout << endl;
	}
};

int calculate(int a, int b, char operation)
{
	int result = 0;

	if (operation == '+')
		result = a + b;
	else if (operation == '-')
		result = a - b;
	else if (operation == '*')
		result = a * b;
	else if (operation == '/')
		result = a / b;
	return result;
}

int main()
{
	LQueue<int> numbers;
	LQueue<char> operators;

	int n;
	cin >> n;
	cin.ignore();
	string expression;
	for (int i = 0; i < n; i++) {

		getline(cin, expression);
		int index = 0;
		int operationsCount = 0;

		while (index < expression.length()) {
			if (expression[index] >= '0' && expression[index] <= '9')
				numbers.push((int)(expression[index]) - '0');
			else {
				operators.push(expression[index]);
				operationsCount++;
			}
			index += 2;
		}
		numbers.print();
		operators.print();
		int res = calculate(numbers.pop(), numbers.pop(), operators.pop());
		while (!operators.empty()) {
			int a = res;
			int b = numbers.pop();
			char op = operators.pop();

			res = calculate(a, b, op);
		}
		cout << res << endl;

	}

	system("pause");
	return 0;
}