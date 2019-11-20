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

  unsigned char a = 0b10101011;
  cout << binStr(a) << endl;

  cout << "Setting the bit at position 2" << endl;
  a |= 1 << 2;
  cout << binStr(a) << endl;

  cout << "Setting the bit at position 0 (nothing happens since was already set)" << endl;
  a |= 1;
  cout << binStr(a) << endl;

  cout << "Clearing the bit at position 3" << endl;
  a &= ~(1 << 3);
  cout << binStr(a) << endl;

  cout << "Clearing the bit at position 6 (nothing happens since was already clear)" << endl;
  a &= ~(1 << 6);
  cout << binStr(a) << endl;

  cout << "Toggling the bit at position 2" << endl;
  a ^= 1 << 2;
  cout << binStr(a) << endl;

  cout << "The bit at position 4 is " << (a & (1 << 4) ? "set" : "unset") << endl;
  cout << binStr(a) << endl;

  cout << "The bit at position 5 is " << (a & (1 << 5) ? "set" : "unset") << endl;
  cout << binStr(a) << endl;

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


