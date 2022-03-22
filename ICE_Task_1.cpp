/**
*   Interview Question:
*   Write a program that does the following:
*   Read a double precision number (from stdin) and print the smallest number that is larger than 95% of numbers encountered so far.
*   Run program on input size = 128,000,000 and provide the time taken. Provide the time taken for this random input along with the solution.
**/
#include<iostream>
#include <memory>
#include <random>

using namespace std;

struct node
{
	double	data;
	node	*left, * right;
	int		left_size;

	node(double data) : 
		data(data), 
		left(nullptr), 
		right(nullptr), 
		left_size(0)
	{}
};


class bst
{
	float _total_nodes;
	node* _root;

public:

	bst() :_total_nodes(0), _root(nullptr)
	{}

	bool insert_while(int larger_than_percent, double data)
	{
		_total_nodes = _total_nodes + 1;
		_root = insert(_root, data);
		return (getPercent(data) >= 95);
	}

	node* insert(node*& root, double data)
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

	int getRank(double x)
	{
		return getRank(_root, x);
	}
	
	double getPercent(double x)
	{
		auto rank = getRank(x);
		double fraction = (rank / _total_nodes);
		double percent =  fraction * 100;
		return percent;
	}

	int getRank(node* root, double x)
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
};

int main()
{
	constexpr int MIN = 10;
	constexpr int MAX = 100;
	bst tree;
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(MIN, MAX);
	double input = distr(eng);
	std::cout << input << std::endl;		
	while(!tree.insert_while(95, input));
	return 0;
}
