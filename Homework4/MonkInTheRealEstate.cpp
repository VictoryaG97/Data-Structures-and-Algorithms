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

	bool empty() const {
		return start == NULL;
	}
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
		deleteAfter(q, x);
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


typedef LList<int> IntList;
typedef LList<IntList> IntGraph;

elem_link<int>* Point(int a, IntGraph &g)
{
	g.iterStart();
	elem_link<IntList> *p;
	elem_link<int> *q;

	do {
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	} while (q->inf != a);

	if (q->inf != a)
		return NULL;
	return q;
}

void AddTop(int a, IntGraph &g)
{
	IntList l;
	l.toEnd(a);
	g.toEnd(l);
}

void AddRib(int a, int b, IntGraph &g)
{
	elem_link<int> *p, *q = Point(a, g);
	while (q->link)q = q->link;
	p = new elem_link<int>;
	p->inf = b;
	p->link = NULL;
	q->link = p;
}

void CreateGraph(IntGraph &g)
{
	char c;
	do {
		cout << "top of graph: ";
		int x;
		cin >> x;
		AddTop(x, g);
		cout << "top y/n? ";
		cin >> c;
	} while (c == 'y');

	cout << "ribs: " << endl;

	do {
		cout << "start top: ";
		int x, y;
		cin >> x;
		cout << "end top: ";
		cin >> y;
		AddRib(x, y, g);
		cout << "next y/n? ";
		cin >> c;
	} while (c == 'y');
}

bool member(int a, IntList &l)
{
	if (!l.empty()) {
		l.iterStart();
		elem_link<int> *p = l.iter();

		while (p) {
			if (p->inf == a)
				return true;
			p = p->link;
		}
		return false;
	}
	return false;
}

int countOfCities(IntGraph &g)
{
	int count = 0;
	IntList l;

	g.iterStart();
	elem_link<IntList> *p = g.iter();

	while (p) {
		p->inf.iterStart();
		elem_link<int> *q = p->inf.iter();

		while (q) {
			if (!member(q->inf, l)) {
				l.toEnd(q->inf);
				count++;
			}
			q = q->link;
		}
		p = p->link;
	}
	return count;
}

int main()
{
	IntGraph g;
	int t;
	cin >> t;

	for (int i = 1; i <= t; i++) {
		int e, x, y;
		cin >> e;

		for (int j = 1; j <= e; j++) {
			cin >> x >> y;

			if (!Point(x, g))
				AddTop(x, g);
			if (!Point(y, g))
				AddTop(y, g);
			AddRib(x, y, g);
		}
		cout << countOfCities(g) << endl;
	}

	system("pause");
	return 0;
}