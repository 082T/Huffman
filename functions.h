#pragma once
#include<vector>
#include<string>
#include<utility>

typedef std::pair<std::string, double> psd;
typedef std::pair<char, double> pcd;

class Node
{
public:
	psd data;

	class Node* left;
	class Node* right;

	Node();
	Node(pcd input_data);
	Node(Node* a, Node* b);
};

struct myComp {
    constexpr bool operator()( Node* const& a, Node* const&b) const noexcept
    {
        return a->data.second > b->data.second || a->data.second == b->data.second && a->data.first > b->data.first;
    }
};


std::vector<pcd > count_probabilities(std::string user_input);

void print_probabilities(std::vector<pcd> pairs);

Node* create_tree(std::vector<pcd> pairs);

void print_tree(Node* root, std::string prefix, bool left, std::string value);

std::string character_value(char c, Node* root, std::string value);

std::string huffman_alg(std::string user_input, Node* root);

