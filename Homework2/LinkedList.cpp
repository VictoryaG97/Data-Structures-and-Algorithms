#include<iostream>

using namespace std;

template <typename T>
struct elem_link
{
	T inf;
	elem_link<T> *link;
};

template <typename T>
class LList
{
	elem_link<T> *start, *end, *current;

	void deleteList();
	void copyList(LList<T> const&);

public:
	LList();
	LList(LList<T> const&);
	LList& operator=(LList<T> const&);
	~LList();

	void iterStart(elem_link<T> *p = NULL);
	elem_link<T>* iter();

	void toEnd(T const &);
	void insertAfter(elem_link<T>*, T const &);
	void insertBefore(elem_link<T>*, T const&);
	bool deleteAfter(elem_link<T>*, T &);
	bool deleteBefore(elem_link<T>*, T &);
	void deleteElem(elem_link<T>*, T &);

	void print();
	int length();
	void concat(LList<T> const&);

};

template<typename T>
void LList<T>::deleteList()
{
	elem_link<T>* p;
	while (start) {
		p = start;
		start = start->link;
		delete p;
	}
	end = NULL;
}

template<typename T>
void LList<T>::copyList(LList<T> const &list)
{
	start = end = NULL;
	if (list.start) {
		elem_link<T>* p = list.start;
		while (p) {
			toEnd(p->inf);
			p = p->link;
		}
	}
}

template<typename T>
LList<T>::LList()
{
	start = NULL;
	end = NULL;
}

template<typename T>
LList<T>::LList(LList<T> const &list)
{
	copyList(list);
}

template<typename T>
LList<T>& LList<T>::operator=(LList<T> const &list)
{
	if (this != &list) {
		deleteList();
		copyList(list);
	}
	return *this;
}

template<typename T>
LList<T>::~LList()
{
	deleteList();
}

template<typename T>
void LList<T>::iterStart(elem_link<T>* p)
{
	if (p) current = p;
	else current = start;
}

template<typename T>
elem_link<T>* LList<T>::iter()
{
	elem_link<T> *p = current;
	if (current) current = current->link;
	return p;
}

template<typename T>
void LList<T>::toEnd(T const &x)
{
	current = end;
	end = new elem_link<T>;
	end->inf = x;
	end->link = NULL;
	if (current) current->link = end;
	else start = end;
}

template<typename T>
void LList<T>::insertAfter(elem_link<T>* p, T const &x)
{
	elem_link<T> *q = new elem_link<T>;
	q->inf = x;
	q->link = p->link;

	if (p == end) end = q;
	p->link = q;
}

template<typename T>
void LList<T>::insertBefore(elem_link<T> *p, T const &x)
{
	elem_link<T> *q = new elem_link<T>;
	*q = *p;

	if (p == end) end = q;

	p->inf = x;
	p->link = q;
}

template<typename T>
bool LList<T>::deleteAfter(elem_link<T> *p, T &x)
{
	if (p->link) {
		elem_link<T> *q = p->link;
		x = q->inf;
		p->link = q->link;

		if (q == end) end = p;

		delete q;
		return 1;
	}
	return 0;
}

template<typename T>
bool LList<T>::deleteBefore(elem_link<T> *p, T &x)
{
	if (p != start) {
		elem_link<T> *q = start;
		while (q->link != p) q = q->link;
		DeleteElem(q, x);
		return 1;
	}
	return 0;
}

template<typename T>
void LList<T>::deleteElem(elem_link<T> *p, T &x)
{
	if (p == start) {
		x = p->inf;
		if (start == end)
			start = end = NULL;
		else {
			start = start->link;
		}
		delete p;
	}
	else {
		elem_link<T>* q = start;
		while (q->link != p) q = q->link;
		DeleteAfter(q, x);
	}
}

template<typename T>
void LList<T>::print()
{
	elem_link<T> *p = start;
	while (p) {
		cout << p->inf << " ";
		p = p->link;
	}
	cout << endl;
}

template<typename T>
int LList<T>::length()
{
	int n = 0;
	elem_link<T> *p = start;
	while (p) {
		n++;
		p = p->link;
	}
	return n;
}

template<typename T>
void LList<T>::concat(LList<T> const &other)
{
	elem_link<T> *p = other.start;
	while (p) {
		toEnd(p->inf);
		p = p->link;
	}
}


int main()
{
	LList<int> list;
	list.toEnd(1);
	list.toEnd(2);
	list.print();

	elem_link<int> *p = list.iter();
	list.insertBefore(p, 3);

	list.iterStart();
	p = list.iter();

	list.insertAfter(p, 4);
	list.print();

	system("pause");
	return 0;
}