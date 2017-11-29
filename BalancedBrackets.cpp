#include<iostream>
#include<string>

using namespace std;

template <typename T>
struct elem_link2 {
	T inf;
	elem_link2<T> *next;
	elem_link2<T> *prev;
};

template <typename T>
class DList
{
	elem_link2<T> *start;
	elem_link2<T> *end;
	elem_link2<T> *currentS;
	elem_link2<T> *currentE;


	void CopyList(DList<T> const &);
	void DeleteList();

public:
	DList();
	DList(DList<T> const &);
	DList& operator=(DList<T> const &);
	~DList();

	void ResetList();

	void IterStart(elem_link2<T> *p = NULL);
	void IterEnd(elem_link2<T> *p = NULL);

	elem_link2<T>* IterNext();
	elem_link2<T>* IterPrev();

	void ToEnd(T const &);
	void DeleteElement(elem_link2<T> *, T &);

	void print();
	void print_reverse();
	int length();
};

template <typename T>
void DList<T>::DeleteList()
{
	elem_link2<T> *p;
	while (start) {
		p = start;
		start = start->next;
		delete p;
	}
	start = end = NULL;
}

template <typename T>
void DList<T>::CopyList(DList<T> const &list)
{
	start = end = NULL;
	if (list.start) {
		elem_link2<T> *p = list.start;
		while (p) {
			ToEnd(p->inf);
			p = p->next;
		}
	}
}

template <typename T>
DList<T>::DList()
{
	start = NULL;
	end = NULL;
}

template <typename T>
DList<T>::DList(DList<T> const &list)
{
	CopyList(list);
}

template <typename T>
DList<T>& DList<T>::operator=(DList<T> const &list)
{
	if (this != &list) {
		DeleteList();
		CopyList(list);
	}
	return *this;
}

template <typename T>
DList<T>::~DList()
{
	DeleteList();
}

template<typename T>
void DList<T>::ResetList()
{
	DeleteList();
}

template <typename T>
void DList<T>::IterStart(elem_link2<T> *p)
{
	if (p) currentS = p;
	else currentS = start;
}

template <typename T>
void DList<T>::IterEnd(elem_link2<T> *p)
{
	if (p) currentE = p;
	else currentE = end;
}

template <typename T>
elem_link2<T>* DList<T>::IterNext()
{
	elem_link2<T> *p = currentS;
	if (currentS) currentS = currentS->next;
	return p;
}

template <typename T>
elem_link2<T>* DList<T>::IterPrev()
{
	elem_link2<T> *p = currentE;
	if (currentE) currentE = currentE->prev;
	return p;
}

template <typename T>
void DList<T>::ToEnd(T const &x)
{
	elem_link2<T> *p = end;
	end = new elem_link2<T>;
	end->inf = x;
	end->next = NULL;

	if (p) p->next = end;
	else start = end;

	end->prev = p;
}

template <typename T>
void DList<T>::DeleteElement(elem_link2<T> *p, T &x)
{
	x = p->inf;
	if (start == end) {
		start = NULL;
		end = NULL;
	}
	else if (p == start) {
		start = start->next;
		start->prev = NULL;
	}
	else if (p == end) {
		end = end->prev;
		end->next = NULL;
	}
	else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete p;
}

template<typename T>
void DList<T>::print()
{
	elem_link2<T> *p = start;
	while (p) {
		cout << p->inf << " ";
		p = p->next;
	}
	cout << endl;
}

template<typename T>
void DList<T>::print_reverse()
{
	elem_link2<T> *p = end;
	while (p) {
		cout << p->inf << " ";
		p = p->prev;
	}
	cout << endl;
}

template<typename T>
int DList<T>::length()
{
	int n = 0;
	elem_link2<T> *p = start;
	while (p) {
		n++;
		p = p->next;
	}
	return n;
}

int main()
{
	int n;
	cin >> n;
	cin.ignore();
	DList<char> L;
	string s;
	string *res = new string[n];
	for (int i = 0; i < n; i++) {
		getline(cin, s);

		int j = 0;
		while (j < s.length()) {
			L.ToEnd(s[j]);
			j++;
		}
		L.IterStart();
		L.IterEnd();
		elem_link2<char> *p = L.IterNext();
		elem_link2<char> *q = L.IterPrev();

		bool check = false;
		int l = 1;
		cout << L.length() / 2 << endl;
		while (l <= L.length() / 2) {
			if (p->inf == '{' && q->inf == '}') check = true;
			else if (p->inf == '[' && q->inf == ']') check = true;
			else if (p->inf == '(' && q->inf == ')') check = true;
			else check = false;

			p = L.IterNext();
			q = L.IterPrev();
			l++;
		}
		if (check == true) res[i] = "YES";
		else res[i] = "NO";

		L.ResetList();
	}

	for (int i = 0; i < n; i++) {
		cout << res[i] << endl;
	}
	system("pause");
	return 0;
}