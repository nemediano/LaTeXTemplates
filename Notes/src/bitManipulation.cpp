/*
 * bitManipulation.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: jorgeg
 */
#include <bitset>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

const size_t BITS_PER_BYTE = 8U;

template<typename T>
static std::string binStr(const T& x);

int main(int argc, char* argv[]) {
	unsigned char a = 1;
	unsigned int b = 1;
	int c = 0xFF00FF08;

	cout << "size of a: " << sizeof(a) * BITS_PER_BYTE << endl;
	cout << "size of b: " << sizeof(b) * BITS_PER_BYTE << endl;
	cout << "size of c: " << sizeof(c) * BITS_PER_BYTE << endl;
	cout << "a = " << binStr(a) << endl;
	cout << "b = " << binStr(b) << endl;
	cout << "c = " << binStr(c) << endl;

	return EXIT_SUCCESS;
}

template<typename T>
static std::string binStr(const T& x)
{
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * BITS_PER_BYTE>(x);
    return ss.str();
}


