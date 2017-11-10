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
};

int main()
{
	LStack<int> ls;

	ls.push(5);
	ls.push(9);
	ls.push(13);
	cout << ls.top() << endl;
	cout << ls.pop() << endl;
	ls.push(26);
	cout << ls.top() << endl;

	ls.print();
	cout << endl;

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
