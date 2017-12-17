#include <iostream>

using namespace std;

const int INITIAL = 16;

template <typename T>
class PABinTree
{
	T *parents, *values;
	int index, capacity;

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
	T *oldp = parents;
	T *oldv = values;
	parents = new T[capacity * 2];
	values = new T[capacity * 2];
	Copy(parents, oldp);
	Copy(values, oldv);
	capacity *= 2;
	delete[] oldp;
	delete[] oldv;
}

template<typename T>
void PABinTree<T>::DeleteBinTree()
{
	delete[] parents;
	delete[] values;
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
	parents = new T[capacity];
	values = new T[capacity];
	Copy(parents, ot.parents);
	Copy(values, ot.values);
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
		parents[index] = -1;
	}
	else {
		cout << "vertex: ";
		cin >> x;
		if (full()) resize();
		parents[index] = prev;
	}
	values[index] = x;
	index++;
	int check = 0;
	cout << "Left tree of " << x << " y/n? ";
	cin >> c;
	if (c == 'y')
		CreateBinTree(x);

	cout << "Right tree of " << x << " y/n? ";
	cin >> c;
	if (c == 'y')
		CreateBinTree(x);
}

template<typename T>
PABinTree<T>::PABinTree() : index(-1), capacity(INITIAL)
{
	parents = new T[capacity];
	values = new T[capacity];
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
		if (parents[i] == -1) return parents[i];
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
		cout << parents[i] << " ";
	cout << endl;
	for (int i = 0; i < index; i++)
		cout << values[i] << " ";
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
