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
  unsigned int a = 0xa92471c3;
  cout << "a: " << binStr(a) << endl;
  unsigned int mask = 0x0003c00f;
  cout << "m: " << binStr(mask) << endl;
  cout << "Setting bits using mask" << endl;
  a |= mask;
  cout << "m: " << binStr(mask) << endl;
  cout << "a: " << binStr(a) << endl;
  cout << "Clearing bits using mask" << endl;
  a &= ~mask;
  cout << "m: " << binStr(mask) << endl;
  cout << "a: " << binStr(a) << endl;
  cout << "Toggling bits using mask" << endl;
  a ^= mask;
  cout << "m: " << binStr(mask) << endl;
  cout << "a: " << binStr(a) << endl;

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


