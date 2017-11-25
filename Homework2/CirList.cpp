#include<iostream>

using namespace std;

template <typename T>
struct elem_cir
{
	T inf;
	elem_cir<T> *link;
};

template <typename T>
class CirList
{
	elem_cir<T> *end;
	elem_cir<T> *current;

	void DeleteList();
	void CopyList(CirList<T> const &);

public:
	CirList();
	CirList(CirList<T> const &);
	CirList& operator=(CirList<T> const &);
	~CirList();

	void IterStart(elem_cir<T> *p = NULL);
	elem_cir<T>* Iter();

	void ToEnd(T const &);
	void DeleteElement(elem_cir<T>*, T &);

	void print();
};

template<typename T>
void CirList<T>::DeleteList()
{
	IterStart();
	elem_cir<T> *p = Iter();
	while (p) {
		delete p;
		p = Iter();
	}
}

template<typename T>
void CirList<T>::CopyList(CirList<T> const &list)
{
	end = NULL;
	elem_cir<T> *p = list.end;
	if (p) {
		p = p->link;
		while (p != list.end) {
			ToEnd(p->inf);
			p = p->link;
		}
		ToEnd(p->inf);
	}
}

template<typename T>
CirList<T>::CirList()
{
	end = NULL;
}

template<typename T>
CirList<T>::CirList(CirList<T> const &list)
{
	CopyList(list);
}

template<typename T>
CirList<T> & CirList<T>::operator=(CirList<T> const &list)
{
	if (this != &list) {
		DeleteList();
		CopyList(list);
	}
	return *this;
}

template<typename T>
CirList<T>::~CirList()
{
	DeleteList();
}

template<typename T>
void CirList<T>::IterStart(elem_cir<T>* p)
{
	if (p) current = p;
	else {
		if (!end) current = NULL;
		else current = end->link;
	}
}

template<typename T>
elem_cir<T>* CirList<T>::Iter()
{
	elem_cir<T>* p = current;
	if (current == end) current = NULL;
	else if(current) current = current->link;
	return p;
}

template<typename T>
void CirList<T>::ToEnd(T const &x)
{
	elem_cir<T> *p = new elem_cir<T>;
	p->inf = x;

	if (end) p->link = end->link;
	else end = p;

	end->link = p;
	end = end->link;
}

template<typename T>
void CirList<T>::DeleteElement(elem_cir<T> *p, T &x)
{
	x = p->inf;
	if (end != end->link) {
		elem_cir<T> *q = end;
		while (q->link != p)q = q->link;
		q->link = p->link;
		if (p == end) end = q;
		delete p;
	}
	else {
		end = NULL;
		delete p;
	}
}

template<typename T>
void CirList<T>::print()
{
	IterStart();
	elem_cir<T> *p = Iter();

	while (p) {
		cout << p->inf << " ";
		p = Iter();
	}
	cout << endl;
}

int main()
{
	CirList<int> cl;
	cl.ToEnd(1);
	cl.ToEnd(2);
	cl.ToEnd(3);
	cl.ToEnd(4);
	cl.print();


	system("pause");
	return 0;
}
