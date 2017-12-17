#include <iostream>

using namespace std;

const int INITIAL = 16;

template <typename T>
class TABinTree
{
	T *values;
	int *leftSubTree, *rightSubTree;
	int rootIndex, capacity;
	int indexV = -1, indexL = -1, indexR = -1;

	bool full() const;
	void re(T *&);
	void resize();
	void DeleteBinTree();
	void Copy(T *&, T const*);
	void CopyBinTree(TABinTree<T> const&);
	void pr(T);

public:
	TABinTree();
	TABinTree(TABinTree<T> const&);
	TABinTree& operator=(TABinTree<T> const&);
	~TABinTree();

	T GetRoot() const;
	bool empty();
	void print();
	void printArrays();
	void Create();
};

template<typename T>
bool TABinTree<T>::full() const
{
	return indexA == capacity - 1;
}

template<typename T>
void TABinTree<T>::re(T * &p)
{
	T *oldp = p;
	p = new T[capacity * 2];
	Copy(p, oldp);
	delete[] oldp;
}

template<typename T>
void TABinTree<T>::resize()
{
	re(values);
	re(leftSubTree);
	re(rightSubTree);
	
	capacity *= 2;
}

template<typename T>
void TABinTree<T>::DeleteBinTree()
{
	delete[] values;
	delete[] leftSubTree;
	delete[] rightSubTree;
}

template<typename T>
void TABinTree<T>::Copy(T * &p, T const *other)
{
	for (int i = 0; i < capacity; i++)
		p[i] = other[i];
}

template<typename T>
void TABinTree<T>::CopyBinTree(TABinTree<T> const &ot)
{
	rootIndex = ot.rootIndex;
	capacity = ot.capacity;
	indexV = ot.indexV;
	indexL = ot.indexL;
	indexR = ot.indexR;

	values = new T[capacity];
	Copy(values, ot.values);
	leftSubTree = new T[capacity];
	Copy(leftSubTree, ot.leftSubTree);
	rightSubTree = new T[capacity];
	Copy(rightSubTree, ot.rightSubTree);
}

template<typename T>
void TABinTree<T>::pr(T index)
{
	if (leftSubTree[index] != -1)
		pr(leftSubTree[index]);
	cout << values[index] << " ";
	if (rightSubTree[index] != -1)
		pr(rightSubTree[index]);
}

template<typename T>
TABinTree<T>::TABinTree() : rootIndex(0), capacity(INITIAL)
{
	values = new T[capacity];
	leftSubTree = new T[capacity];
	rightSubTree = new T[capacity];
}

template<typename T>
TABinTree<T>::TABinTree(TABinTree<T> const &t)
{
	CopyBinTree(t);
}

template<typename T>
TABinTree<T> & TABinTree<T>::operator=(TABinTree<T> const &t)
{
	if (this != &t) {
		DeleteBinTree();
		CopyBinTree(t);
	}
	return *this;
}

template<typename T>
TABinTree<T>::~TABinTree()
{
	DeleteBinTree();
}

template<typename T>
T TABinTree<T>::GetRoot() const
{
	return values[rootIndex];
}

template<typename T>
bool TABinTree<T>::empty()
{
	return indexV == -1;
}

template<typename T>
void TABinTree<T>::print()
{
	pr(rootIndex);
}

template<typename T>
void TABinTree<T>::printArrays()
{
	for (int i = 0; i < indexV; i++)
		cout << values[i] << " ";
	cout << endl;
	for (int i = 0; i < indexL; i++)
		cout << leftSubTree[i] << " ";
	cout << endl;
	for (int i = 0; i < indexR; i++)
		cout << rightSubTree[i] << " ";
	cout << endl;
}

template<typename T>
void TABinTree<T>::Create()
{
	T x;
	char p;
	if (indexV == -1) {
		indexV = 0;
		indexL = 0;
		indexR = 0;
	}
	int i = indexV;

	cout << "root: ";
	cin >> x;
	values[indexV] = x;
	rightSubTree[indexR] = -1;
	indexV++;
	indexR++;

	cout << "Left tree of: " << x << " y/n? ";
	cin >> p;
	if (p == 'y') {
		leftSubTree[indexL] = indexV;
		indexL++;
		Create();
	}
	else if (p == 'n') {
		leftSubTree[indexL] = -1;
		indexL++;
	}

	cout << "Right tree of: " << x << " y/n? ";
	cin >> p;
	if (p == 'y') {
		rightSubTree[i] = indexV;
		Create();
	}
	else if (p == 'n') {
		rightSubTree[i] = -1;
	}
}


int main()
{
	TABinTree<int> t;
	t.Create();
	t.printArrays();

	system("pause");
	return 0;
}
