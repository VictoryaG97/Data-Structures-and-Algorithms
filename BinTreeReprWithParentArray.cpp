#include <iostream>

using namespace std;

const int INITIAL = 16;

template <typename T>
class PABinTree
{
	T *p, *h;
	int index, hIndex, capacity;

	bool full() const;
	void resize();
	void DeleteBinTree();
	void Copy(T *&, T const*);
	void CopyBinTree(PABinTree<T> const&);
	void CreateBinTree(T prev = 0);

public:
	PABinTree();
	PABinTree(PABinTree<T> const&);
	PABinTree<T> operator=(PABinTree<T> const&);
	~PABinTree();

	T GetRoot() const;
	bool empty();
	void printArray();
	void Create();
};

template<typename T>
bool PABinTree<T>::full() const
{
	return index == capacity - 1;
}

template<typename T>
void PABinTree<T>::resize()
{
	T *oldp = p;
	T *oldh = h;
	p = new T[capacity * 2];
	h = new T[capacity * 2];
	Copy(p, oldp);
	Copy(h, oldh);
	capacity *= 2;
	delete[] oldp;
	delete[] oldh;
}

template<typename T>
void PABinTree<T>::DeleteBinTree()
{
	delete[] p;
	delete[] h;
}

template<typename T>
void PABinTree<T>::Copy(T * &c, T const *other)
{
	for (int i = 0; i < capacity; i++)
		c[i] = other[i];
}

template<typename T>
void PABinTree<T>::CopyBinTree(PABinTree<T> const &ot)
{
	index = ot.index;
	capcity = ot.capacity;
	p = new T[capacity];
	h = new T[capacity];
	Copy(p, ot.p);
	Copy(h, ot.h);
}

template<typename T>
void PABinTree<T>::CreateBinTree(T prev = 0)
{
	if (index == -1) index = 0;

	T x;
	char c;
	if (index == 0) {
		cout << "root: ";
		cin >> x;
		p[index] = -1;
	}
	else {
		cout << "vertex: ";
		cin >> x;
		if (full()) resize();
		p[index] = prev;
	}
	index++;
	int check = 0;
	cout << "Left tree of " << x << " y/n? ";
	cin >> c;
	if (c == 'y')
		CreateBinTree(x);
	else if (c == 'n')
		check++;

	cout << "Right tree of " << x << " y/n? ";
	cin >> c;
	if (c == 'y')
		CreateBinTree(x);
	else if (c == 'n')
		check++;

	if (check == 2) {
		h[hIndex] = x;
		hIndex++;
	}
}

template<typename T>
PABinTree<T>::PABinTree() : index(-1), hIndex(0), capacity(INITIAL)
{
	p = new T[capacity];
	h = new T[capacity];
}

template<typename T>
PABinTree<T>::PABinTree(PABinTree<T> const &t)
{
	CopyBinTree(t);
}

template<typename T>
PABinTree<T> PABinTree<T>::operator=(PABinTree<T> const &t)
{
	if (this != &t) {
		DeleteBinTree();
		CopyBinTree(t);
	}
	return *this;
}

template<typename T>
PABinTree<T>::~PABinTree()
{
	DeleteBinTree();
}

template<typename T>
T PABinTree<T>::GetRoot() const
{
	for (int i = 0; i <= index; i++) {
		if (p[i] == -1) return p[i];
	}
}

template<typename T>
bool PABinTree<T>::empty()
{
	return index == -1;
}

template<typename T>
void PABinTree<T>::printArray()
{
	for (int i = 0; i < index; i++)
		cout << p[i] << " ";
	cout << endl;
	for (int i = 0; i < hIndex; i++)
		cout << h[i] << " ";
	cout << endl;
}

template<typename T>
void PABinTree<T>::Create()
{
	CreateBinTree();
}

int main()
{
	PABinTree<int> t;
	t.Create();
	t.printArray();

	system("pause");
	return 0;
}
