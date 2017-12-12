#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T inf;
	Node<T> *left, *right;
};

template <typename T>
class BinTree
{
	Node<T> *root;

	void DeleteBinTree(Node<T> *) const;
	void Copy(Node<T> * &, Node<T> * const&) const;
	void CopyBinTree(BinTree<T> const&);
	void pr(const Node<T> *) const;
	void CreateBinTree(Node<T> * &)const;

public:
	BinTree();
	BinTree(BinTree<T> const&);
	BinTree& operator=(BinTree<T> const&);
	~BinTree();

	T RootBinTree() const;
	BinTree<T> LeftBinTree() const;
	BinTree<T> RightBinTree() const;
	Node<T>* GetRoot();

	bool empty() const;
	void print() const;

	void Create();
	void Create3(T, BinTree<T>, BinTree<T>);
};

template<typename T>
void BinTree<T>::DeleteBinTree(Node<T> *p) const
{
	if (p) {

		DeleteBinTree(p->left);
		DeleteBinTree(p->right);
		delete p;
		p = NULL;
	}
}

template<typename T>
void BinTree<T>::Copy(Node<T> * &pos, Node<T>* const &r) const
{
	pos = NULL;

	if (r) {
		pos = new Node<T>;
		pos->inf = r->inf;
		Copy(pos->left, r->left);
		Copy(pos->right, r->right);
	}
}

template<typename T>
void BinTree<T>::CopyBinTree(BinTree<T> const &r)
{
	Copy(root, r.root);
}

template<typename T>
void BinTree<T>::pr(const Node<T> *p) const
{
	if (p) {
		pr(p->left);
		cout << p->inf << " ";
		pr(p->right);
	}
}

template<typename T>
void BinTree<T>::CreateBinTree(Node<T>* & pos) const
{
	T x;
	char c;
	cout << "root: ";
	cin >> x;

	pos = new Node<T>;
	pos->inf = x;
	pos->left = NULL;
	pos->right = NULL;

	cout << "Left BinTree of: " << x << " y/n? ";
	cin >> c;
	if (c == 'y') CreateBinTree(pos->left);

	cout << "Right BinTree of: " << x << " y/n? ";
	cin >> c;
	if (c == 'y') CreateBinTree(pos->right);
}

template<typename T>
BinTree<T>::BinTree()
{
	root = NULL;
}

template<typename T>
BinTree<T>::BinTree(BinTree<T> const &r)
{
	CopyBinTree(r);
}

template<typename T>
BinTree<T> & BinTree<T>::operator=(BinTree<T> const &r)
{
	if (this != &r) {
		DeleteBinTree(root);
		CopyBinTree(r);
	}
	return *this;
}

template<typename T>
BinTree<T>::~BinTree()
{
	DeleteBinTree(root);
}

template<typename T>
T BinTree<T>::RootBinTree() const
{
	return root->inf;
}

template<typename T>
BinTree<T> BinTree<T>::LeftBinTree() const
{
	BinTree<T> t;
	Copy(t.root, root->left);

	return t;
}

template<typename T>
BinTree<T> BinTree<T>::RightBinTree() const
{
	BinTree<T> t;
	Copy(t.root, root->right);

	return t;
}

template<typename T>
Node<T>* BinTree<T>::GetRoot()
{
	return root;
}

template<typename T>
bool BinTree<T>::empty() const
{
	return root == NULL;
}

template<typename T>
void BinTree<T>::print() const
{
	pr(root);
}

template<typename T>
void BinTree<T>::Create()
{
	CreateBinTree(root);
}

template<typename T>
void BinTree<T>::Create3(T x, BinTree<T> l, BinTree<T> r)
{
	root = new Node<T>;
	root->inf = x;
	Copy(root->left, l.root);
	Copy(root->right, r.root);
}

int main()
{
	BinTree<int> binTree;
	binTree.Create();
	binTree.print();

	system("pause");
	return 0;
}