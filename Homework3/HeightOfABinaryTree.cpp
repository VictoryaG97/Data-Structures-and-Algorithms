struct Node
{
	int data;
	Node *left, *right;
};

int height(Node *root) {
	int maxLeft = 0, maxRight = 0;

	if (root->left)
		maxLeft = 1 + height(root->left);
	if (root->right)
		maxRight = 1 + height(root->right);
	if (maxLeft > maxRight) return maxLeft;
	return maxRight;
}