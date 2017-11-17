#include <iostream>

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
			return 0;
		}
		return front->data;
	}
};

int main()
{
	
	return 0;
}
