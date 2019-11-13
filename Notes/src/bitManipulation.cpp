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

template<typename T>
static size_t bitSize(const T& x);

int main(int argc, char* argv[]) {

	unsigned char a = 0b101010;
	unsigned int b = 9;
	int c = 0xFF00FF08;

	cout << "size in bits of unsigned char: " << bitSize(a) << endl;
	cout << "size in bits of unsigned int: " << bitSize(b) << endl;
	cout << "size in bits of int: " << bitSize(c) << endl;
	cout << "binary representation of a: " << binStr(a) << endl;
	cout << "binary representation of b: " << binStr(b) << endl;
	cout << "binary representation of c: " << binStr(c) << endl;

  unsigned char d = a << 3;
  unsigned char e = a >> 3;
  unsigned char f = a >> bitSize(a);
  unsigned char g = a << bitSize(a);
  cout << "a: " << binStr(a) << " = " << int(a) << endl;
  cout << "d: " << binStr(d) << " = " << int(d) << endl;
  cout << "e: " << binStr(e) << " = " << int(e) << endl;
  cout << "f: " << binStr(f) << " = " << int(f) << endl;
  cout << "g: " << binStr(g) << " = " << int(g) << endl;

	return EXIT_SUCCESS;
}

template<typename T>
static size_t bitSize(const T& x) {
  return sizeof(x) * BITS_PER_BYTE;
}

template<typename T>
static std::string binStr(const T& x)
{
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * BITS_PER_BYTE>(x);
    return ss.str();
}


