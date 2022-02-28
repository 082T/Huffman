#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<queue>
#include"functions.h"



Node::Node()
{
	left = NULL;
	right = NULL;
}

Node::Node(pcd input_data)
{
	data.first = std::string(1, input_data.first);
	data.second = input_data.second;
	
	left = NULL;
	right = NULL;
}

Node::Node(Node* a, Node* b)
{
	data.first = a->data.first + b->data.first;
	data.second = a->data.second + b->data.second;
	
	left = a;
	right = b;
}

std::vector<pcd> count_probabilities(std::string user_input)
{
	std::vector<char> letter_vector;
	std::vector<int> number_vector;

	int len = user_input.length();
	for (int i = 0; i < len; i++)
	{
		char a = tolower(user_input[i]);
		std::vector<char>::iterator it;
		for (it = letter_vector.begin(); it != letter_vector.end(); it++)
		{
			if (*it == a) 
			{
				int index = it - letter_vector.begin();
				number_vector[index]++;
				break;
			}
		}
		if (it == letter_vector.end())
		{
			letter_vector.push_back(a);
			number_vector.push_back(1);
		}
	}

	std::vector <pcd> joint_vector;
	for (int i = 0; i < number_vector.size(); i++)
	{
		pcd place;
		place.first = letter_vector[i];
		place.second = (double)number_vector[i] / len;
		joint_vector.push_back(place);
	}

	return joint_vector;
}

void print_probabilities(std::vector<pcd> pairs)
{
	for (std::vector<pcd>::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
}

Node* create_tree(std::vector<pcd> pairs)
{
	std::priority_queue<Node*, std::vector<Node*>, myComp> pq;
	
	for (std::vector<pcd>::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		Node* a = new Node(*it);
		pq.push(a);
	}
	
	Node* n1, *n2;
	while (1)
	{
		n1 = pq.top();
		pq.pop();

		if (pq.empty() == 1) break;

		n2 = pq.top();
		pq.pop();

		Node* n3 = new Node(n2, n1);

		pq.push(n3);
	}

	return n1;
}

void print_tree(Node* root, std::string prefix, bool left, std::string value)
{
	if (root == NULL) return;

	std::cout << prefix;

	std::cout << "|--";
	

	std::cout << root->data.first << ", weight: " << root->data.second << ", code = " << value << std::endl;

	std::string t;
	if (left == 1) t = "|   ";
	else t = "    ";
	print_tree(root->left, prefix + t, 1, value + '1');
	print_tree(root->right, prefix + t, 0, value + '0');
}

std::string character_value(char c, Node* root, std::string value)
{
	if (std::string(1, c) == root->data.first) return value;

	if (root->left != NULL)
	{
		if (root->left->data.first.find(c) != std::string::npos)
		{
			return character_value(c, root->left, value + '1');
		}
	}
	return character_value(c, root->right, value + '0');
}

std::string huffman_alg(std::string user_input, Node* root)
{
	std::string coded_string;

	for (int i = 0; i < user_input.length(); i++)
	{
		coded_string += character_value(tolower(user_input[i]), root, "");
	}
	return coded_string;
}


