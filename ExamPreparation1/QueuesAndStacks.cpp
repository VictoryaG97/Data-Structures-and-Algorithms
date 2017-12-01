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
};

class Palindrome
{
	LStack<char> s;
	LQueue<char> q;

public:
	void pushCharacter(char ch){
		s.push(ch);
	}
	void enqueueCharacter(char ch) {
		q.push(ch);
	}
	char popCharacter() {
		return s.pop();
	}
	char dequeueCharacter() {
		return q.pop();
	}
};

int main()
{
	string s;
	getline(cin, s);
	Palindrome p;

	int index = 0;
	while (index < s.length()) {
		p.pushCharacter(s[index]);
		p.enqueueCharacter(s[index]);
		index++;
	}

	index = 0;
	while (index < s.length()) {
		if (p.popCharacter() != p.dequeueCharacter()) {
			cout << "The word is not a panidrome!" << endl;
			system("pause");
			return 0;
		}
		index++;
	}
	cout << "The word is a palindore!" << endl;


	system("pause");
	return 0;
}
