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

	void resetStack() {
		eraseLStack();
	}
	void copyStack(LStack const &other) {
		copyLStack(other);
	}

	bool empty() const;
	void push(T const&);
	T pop();
	T top() const;

	void print();
};

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
		return T();
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
		T x = pop();
		cout << x << endl;
	}
}

bool isPrime(int num)
{
	int count = 0;
	for (int i = 1; i <= num; i++) {
		if (num % i == 0)
			count++;
	}
	if (count == 2) 
		return true;
	return false;
}

typedef LStack<int> IntStack;
typedef LStack<IntStack> IntStackStack;

int main()
{
	int n, q;
	cin >> n >> q;
	cin.ignore();


	IntStack a0, a, b;
	IntStackStack res;
	
	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;
		a0.push(num);
	}
	while (!a0.empty()) {
		if (a0.top() % 2 == 0)
			b.push(a0.pop());
		else
			a.push(a0.pop());
	}
	res.push(b);
	b.resetStack();
	
	int it = 2;
	int primeNum = 3;
	while (it <= q) {
		while (!isPrime(primeNum))
			primeNum++;

		IntStack tempA;
		while (!a.empty()) {
			if (a.top() % primeNum == 0)
				b.push(a.pop());
			else
				tempA.push(a.pop());
		}

		res.push(b);
		b.resetStack();
		a.copyStack(tempA);
		primeNum++;
		it++;
	}

	IntStackStack result;
	while (!res.empty()) {
		result.push(res.pop());
	}
	while (!result.empty()) {
		IntStack r = result.pop();
		r.print();
	}
	a.print();

	system("pause");
	return 0;
}