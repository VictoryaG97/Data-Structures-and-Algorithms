#include<iostream>
#include<stack>

using namespace std;

int main()
{
	stack<int> a, b, tempA, tempB;

	int g, m, n, x, elA, elB, sum = 0, moves = 0;

	cin >> g;
	cin >> n >> m >> x;

	for (int i = 0; i < n; i++)
	{
		cin >> elA;
		tempA.push(elA);
	}
	for (int i = 0; i < m; i++)
	{
		cin >> elB;
		tempB.push(elB);
	}

	for (int i = 0; i < n; i++)
	{
		a.push(tempA.top());
		tempA.pop();
	}
	for (int i = 0; i < m; i++)
	{
		b.push(tempB.top());
		tempB.pop();
	}
	while (sum <= x)
	{
		if (a.top() < b.top()) {
			if (sum + a.top() <= x) {
				sum += a.top();
				a.pop();
				moves++;
			} else break;
		}
		else if(b.top() < a.top()){
			if (sum + b.top() <= x) {
				sum += b.top();
				b.pop();
				moves++;
			} else break;
		}
		else {
			if (sum + a.top() <= x) {
				int top = a.top();
				a.pop();
				b.pop();
				sum += top;
				if (a.top() < b.top())
					b.push(top);
				else a.push(top);
				moves++;
			} else break;
		}

	}
	cout << moves << endl;

	return 0;
}
