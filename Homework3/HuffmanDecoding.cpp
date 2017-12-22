#include <iostream>
#include <string>

using namespace std;

struct node
{
	int freq;
	char data;
	node *left;
	node *right;
};

void decode_huff(node *root, string s)
{
	string decoded;
	node *temp = root;
	int i = 0;
	while (i < s.length()) {
		if (s[i] == 0)
			temp = temp->left;
		else if (s[i] == 1)
			temp = temp->right;

		if (!temp->left && !temp->right) {
			decoded += temp->data;
			temp = root;
		}
	}
	cout << decoded << endl;
}