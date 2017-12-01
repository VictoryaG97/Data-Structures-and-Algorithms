#include<iostream>
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

	void ResetStack() {
		eraseLStack();
	}

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
		//cerr << "Empty stack!" << endl;
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
		//cerr << "Empty stack!" << endl;
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

int calculate(int a, char operation, int b = 0, int c = 0)
{
	int result = 0;

	if (operation == '+')
		result = a + b;
	else if (operation == '-')
		result = a - b;
	else if (operation == '*')
		result = a * b;
	else if (operation == '/')
		result = a / b;
	else if (operation == 'x')
		result = (a * a) + b;
	else if (operation == 'y')
		result = (2 * a) + 1;
	else if (operation == 'z')
		result = a + (2 * b) + (3 * c);

	return result;
}

int main()
{
	int n;
	cin >> n;
	cin.ignore();

	LStack<int> numbers;
	string s;
	string *results = new string[n];

	for (int i = 0; i < n; i++) {
		getline(cin, s);
		int index = 0;

		int a, b, c, num, res;
		char op;
		bool check = true;
		while (index < s.length()) {
			if (s[index] >= '0' && s[index] <= '9') {
				if (s[index + 1] >= '0' && s[index + 1] <= '9') {
					num = ((int)s[index] - '0') * 10 + ((int)s[index + 1] - '0');
					index++;
				}
				else num = (int)s[index] - '0';
				numbers.push(num);
			}
			else if (s[index] == '-' && s[index + 1] >= '0' && s[index + 1] <= '9') {
				index++;
				num = ((int)s[index] - '0') - (2 * ((int)s[index] - '0'));
				numbers.push(num);
			}
			else {
				op = s[index];
				bool checkA = false, checkB = false, checkC = false;
				if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'x') {
					if (!numbers.empty()) {
						b = numbers.pop();
						checkB = true;
					}
					if (!numbers.empty()) {
						a = numbers.pop();
						checkA = true;
					}
					if (checkA == true && checkB == true) res = calculate(a, op, b);
					else check = false;
				}
				else if (op == 'y') {
					if (!numbers.empty()) {
						a = numbers.pop();
						checkA = true;
					}
					if (checkA) res = calculate(a, op);
					else check = false;
				}
				else if (op == 'z') {
					if (!numbers.empty()) {
						c = numbers.pop();
						checkC = true;
					}
					if (!numbers.empty()) {
						b = numbers.pop();
						checkB = true;
					}
					if (!numbers.empty()) {
						a = numbers.pop();
						checkA = true;
					}
					if (checkA && checkB && checkC) res = calculate(a, op, b, c);
					else check = false;
				}
				if (check) numbers.push(res);
			}
			index += 2;
			if (check == true) results[i] = to_string(numbers.top());
			else results[i] = "NO";
		}
		numbers.ResetStack();
	}

	for (int i = 0; i < n; i++)
		cout << results[i] << endl;

	system("pause");
	return 0;
}