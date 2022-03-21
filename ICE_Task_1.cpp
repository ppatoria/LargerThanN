// CPP program to find rank of an
// element in a stream.
//#include <bits/stdc++.h>
#include<iostream>
#include <memory>

using namespace std;

struct node
{
	int data;
	node* left, * right;
	int left_size;

	node(int data) : data(data), left(nullptr), right(nullptr), left_size(0)
	{}

};

node* insert(node*& root, int data)
{
	if (!root)
		return new node(data);

	if (data <= root->data)
	{
		root->left = insert(root->left, data);
		root->left_size++;
	}
	else
	{
		root->right = insert(root->right, data);
	}
	return root;
}

int getRank(node* root, int x)
{
	if (root->data == x)
		return root->left_size;

	if (x < root->data)
	{
		return (root->left == nullptr)
			? -1
			: getRank(root->left, x);
	}
	else
	{
		if (!root->right)
			return -1;
		else {
			int right_size = getRank(root->right, x);
			if (right_size == -1) return -1;
			return root->left_size + 1 + right_size;
		}
	}
}

int main()
{
	int arr[] = { 5, 1, 4, 4, 5, 9, 7, 13, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 4;

	node* root = NULL;
	for (int i = 0; i < n; i++)
		root = insert(root, arr[i]);

	std::cout << "Rank of " << x << " in stream is: "
		<< getRank(root, x) << std::endl;

	x = 13;
	cout << "Rank of " << x << " in stream is: "
		<< getRank(root, x) << endl;

	x = 8;
	cout << "Rank of " << x << " in stream is: "
		<< getRank(root, x) << endl;
	return 0;
}
