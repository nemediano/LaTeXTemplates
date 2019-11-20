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

	unsigned char aChar = 0b101010;
	unsigned int aUnsigInt = 9;
	int anInt = 0xFF00FF08;

	cout << "size in bits of unsigned char: " << bitSize(aChar) << endl;
	cout << "size in bits of unsigned int: " << bitSize(aUnsigInt) << endl;
	cout << "size in bits of int: " << bitSize(anInt) << endl;
	cout << "binary representation of aChar: " << binStr(aChar) << endl;
	cout << "binary representation of aUnsigInt: " << binStr(aUnsigInt) << endl;
	cout << "binary representation of anInt: " << binStr(anInt) << endl;

  cout << endl << "Bit shifting sample" << endl;
  unsigned char a = aChar;
  unsigned char b = a << 3;
  unsigned char c = a >> 3;
  unsigned char d = a >> bitSize(a);
  unsigned char e = a << bitSize(a);
  unsigned char f = a;

  cout << "a: " << binStr(a) << " = " << int(a) << endl;
  cout << "b: " << binStr(b) << " = " << int(b) << endl;
  cout << "c: " << binStr(c) << " = " << int(c) << endl;
  cout << "d: " << binStr(d) << " = " << int(d) << endl;
  cout << "e: " << binStr(e) << " = " << int(e) << endl;

  cout << endl << "Bitwise binary operations sample" << endl;
  a = 0b10101101;
  b = 0b11100110;
  c = a & b;
  d = a | b;
  e = a ^ b;
  f = ~a;

  cout << "c = a & b" << endl;
  cout << "a: " << binStr(a) << endl;
  cout << "b: " << binStr(b) << endl;
  cout << "c: " << binStr(c) << endl;
  cout << "d = a | b" << endl;
  cout << "a: " << binStr(a) << endl;
  cout << "b: " << binStr(b) << endl;
  cout << "d: " << binStr(d) << endl;
  cout << "e = a ^ b" << endl;
  cout << "a: " << binStr(a) << endl;
  cout << "b: " << binStr(b) << endl;
  cout << "e: " << binStr(e) << endl;
  cout << "f = ~a" << endl;
  cout << "a: " << binStr(a) << endl;
  cout << "f: " << binStr(f) << endl;

	return EXIT_SUCCESS;
}

template<typename T>
static size_t bitSize(const T& x) {
  return sizeof(x) * BITS_PER_BYTE;
}

template<typename T>
static std::string binStr(const T& x) {
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * BITS_PER_BYTE>(x);
    return ss.str();
}


