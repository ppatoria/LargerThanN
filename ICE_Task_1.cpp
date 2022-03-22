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

	void insert(double data)
	{
		_total_nodes = _total_nodes + 1;
		_root = insert(_root, data);
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
	
	int getPercent(double x)
	{
		auto rank = getRank(x);
		float fraction = (rank / _total_nodes);
		float percent =  fraction * 100;
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

namespace random
{
	double number()
	{
		constexpr int MIN = 10;
		constexpr int MAX = 100;
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_real_distribution<double> distr(MIN, MAX);
		return distr(eng);
	}
}

 std::vector<double> get_input(int n = 128000000)
{
	std::vector<double> v(n);
	for (int i = 0; i < n;  i++)
	{
		v[i] = random::number();
	}
	return v;
}

int main()
{
	bst tree;
	
	for (const auto& num : get_input(1000))
	{
		std::cout << num << std::endl;
		tree.insert(num);
		auto percent = tree.getPercent(num);
		if (percent == 95)
		{
			std::cout << "smallest number that is larger than 95 % of numbers encountered so far: " << num << " percentage: " << percent << std::endl;
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}
