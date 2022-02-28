#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include"functions.h"


int main()
{
	std::string input_string, output_string;

	std::getline(std::cin, input_string);

	std::vector<pcd> count = count_probabilities(input_string);
	Node* root = create_tree(count);
	
	std::cout << std::endl;
	print_tree(root, "", 0, "");
	std::cout << std::endl;

	std::cout << "Huffman code: " << std::endl;
	std::cout << huffman_alg(input_string, root) << std::endl;

	return 0;
}
