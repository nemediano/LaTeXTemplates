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
  
  cout << "Bit manipulation sample..." << endl;

  cout << "Original value" << endl;
  unsigned char a = 0b00101010;
  cout << "a: " << binStr(a) << endl;
  
  cout << "Create a mask for the bit at position 2" << endl;
  unsigned char mask = 1 << 2;
  cout << "m: " << binStr(mask) << endl;
  
  cout << "Variable to show the reult" << endl;
  unsigned char r = 0;
  cout << "r: " << binStr(r) << endl;

  cout << "Setting a bit: r = a | mask" << endl;
  r = a | mask;
  cout << "a: " << binStr(a) << endl;
  cout << "m: " << binStr(mask) << endl;
  cout << "r: " << binStr(r) << endl;

  cout << "Clearing a bit: r = a & (~mask)" << endl;
  r = a & (~mask);
  cout << "a: " << binStr(a) << endl;
  cout << "m: " << binStr(mask) << endl;
  cout << "~m:" << binStr(char(~mask)) << endl;
  cout << "r: " << binStr(r) << endl;

  cout << "Toggling a bit: r = a ^ mask" << endl;
  r = a ^ mask;
  cout << "a: " << binStr(a) << endl;
  cout << "m: " << binStr(mask) << endl;
  cout << "r: " << binStr(r) << endl;

  cout << "Query a bit: q = ((a & mask) != 0)" << endl;
  bool q = ((a & mask) != 0);
  cout << "The bit is " << (q ? "true" : "false") << endl;


  cout << endl << "Repeat all with a diferent bit" << endl;
  cout << "Original value" << endl;
  cout << "a: " << binStr(a) << endl;
  
  cout << "Create a mask for the bit at position 3" << endl;
  mask = 1 << 3;
  cout << "m: " << binStr(mask) << endl;
  
  cout << "Variable to show the reult" << endl;
  r = 0;
  cout << "r: " << binStr(r) << endl;
  
  cout << "Setting a bit: r = a | mask" << endl;
  r = a | mask;
  cout << "a: " << binStr(a) << endl;
  cout << "m: " << binStr(mask) << endl;
  cout << "r: " << binStr(r) << endl;

  cout << "Clearing a bit: r = a & (~mask)" << endl;
  r = a & (~mask);
  cout << "a: " << binStr(a) << endl;
  cout << "m: " << binStr(mask) << endl;
  cout << "~m:" << binStr(char(~mask)) << endl;
  cout << "r: " << binStr(r) << endl;

  cout << "Toggling a bit: r = a ^ mask" << endl;
  r = a ^ mask;
  cout << "a: " << binStr(a) << endl;
  cout << "m: " << binStr(mask) << endl;
  cout << "r: " << binStr(r) << endl;

  cout << "Query a bit: q = ((a & mask) != 0)" << endl;
  q = ((a & mask) != 0);
  cout << "The bit is " << (q ? "true" : "false") << endl;

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


