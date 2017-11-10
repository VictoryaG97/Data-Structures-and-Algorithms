#include<iostream>

using namespace std;

const int MAX = 1000;

int f[MAX] = { 0 };

int Fib(int n)
{
	if (n == 0)
		return n;
	if (n == 1 || n == 2)
		return 1;
	if (f[n])
		return f[n];

	int k = (n & 1) ? (n + 1) / 2 : n / 2;

	f[n] = (n & 1) ? (Fib(k)*Fib(k) + Fib(k - 1)*Fib(k - 1)) : (2 * Fib(k - 1) + Fib(k))*Fib(k);

	return f[n];
}

int main()
{
	int n;
	cin >> n;
	
	cout << Fib(n) << endl;

	return 0;
}