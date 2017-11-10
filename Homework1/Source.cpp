#include<iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node* next;
};

template <typename T>
class LStack
{
	Node<T>* topNode;
	void copy(Node<T>*);
	void eraseLStack();
	void copyLStack(LStack const&);

public:
	LStack();
	LStack(LStack const&);
	LStack& operator=(LStack const&);
	~LStack();

	bool empty() const;
	void push(T const&);
	T pop();
	T top() const;
	
	void print();
	T getMax() const;
};

int main()
{
	LStack<int> ls;
	int n;
	cin >> n;
	int type, element, index = 0;
	int *max = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> type;

		if (type == 1) {
			cin >> element;
			ls.push(element);
		}
		else if (type == 2) {
			ls.pop();
		}
		else {
			max[index] = ls.getMax();
			index++;
		}
	}

	for (int i = 0; i < index; i++)
		cout << max[i] << endl;

	system("pause");
	return 0;
}

template<typename T>
void LStack<T>::copy(Node<T>* toCopy)
{
	if (toCopy == nullptr)
		return;
	copy(toCopy->next);
	push(toCopy->data);
}

template<typename T>
void LStack<T>::eraseLStack()
{
	while (!empty())
		pop();
}

template<typename T>
void LStack<T>::copyLStack(LStack const &ls)
{
	topNode = nullptr;
	copy(ls.topNode);
}

template<typename T>
LStack<T>::LStack()
{
	topNode = nullptr;
}

template<typename T>
LStack<T>::LStack(LStack const &ls)
{
	copyLStack(ls);
}

template<typename T>
LStack<T> & LStack<T>::operator=(LStack const &ls)
{
	if (this != &ls) {
		eraseLStack();
		copyLStack(ls);
	}
	return *this;
}

template<typename T>
LStack<T>::~LStack()
{
	eraseLStack();
}

template<typename T>
bool LStack<T>::empty() const
{
	return topNode == nullptr;
}

template<typename T>
void LStack<T>::push(T const &element)
{
	Node<T>* p = new Node<T>;
	p->data = element;
	p->next = topNode;
	topNode = p;
}

template<typename T>
T LStack<T>::pop()
{
	if (empty()) {
		cerr << "Empty stack!" << endl;
		return 0;
	}

	Node<T>* p = topNode;
	topNode = topNode->next;
	T x = p->data;
	delete p;

	return x;
}

template<typename T>
T LStack<T>::top() const
{
	if (empty()) {
		cerr << "Empty stack!" << endl;
		return 0;
	}

	return topNode->data;
}

template<typename T>
void LStack<T>::print()
{
	while (!empty()) {
		int x = pop();
		cout << x << " ";
	}
}

template<typename T>
T LStack<T>::getMax() const
{
	if (empty()) {
		cerr << "Empty stack!";
		return 0;
	}
	Node<T>* p = topNode;
	T max = p->data;
	while (p != nullptr) {
		if (max < p->data)
			max = p->data;
		p = p->next;
	}
	return max;
}
