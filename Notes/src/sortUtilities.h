#pragma once

// In case we need to debug the sorting algorithms
template <typename Iterator>
void print_collection(const Iterator& begin, const Iterator& end) {
	for (Iterator it = begin; it != end; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void print_vector(const std::vector<int>& v);
void create_input(std::vector<int>& v, bool unique = true);
