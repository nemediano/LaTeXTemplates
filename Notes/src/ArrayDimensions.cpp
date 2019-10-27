//============================================================================
// Name        : ArrayDimensions.cpp
// Author      : Jorge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <cstdlib>

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  vector<int> a = {2, 4, 6, 8, 10};
  cout << "One dimension example" << endl;
  // Remember zero based indices in C++
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << " "; // read access via index
    a[i] = 2 * a[i] + 1; // modify via index
  }

  // Type is vector of int vectors
  vector< vector<int> > b = {
      {2, 4, 6, 8, 10},
      {3, 5, 7, 9, 11},
      {1, 3, 5, 7, 13},
      {0, 2, 4, 6, 8}
  };
  cout << endl;
  cout << "Two dimensional example" << endl;
  for (size_t j = 0; j < b.size(); ++j) {
    for (size_t i = 0; i < b[j].size(); ++i) {
      cout << b[j][i] << " ";    // read access via pair of indices
      b[j][i] = 2 * b[j][i] + 1; // modify via pair of indices
    }
    cout << endl;
  }

  // long type: vector of vectors of int vectors
  vector< vector< vector<int> > > c(3);

  // Allocation itself becomes tricky
  for (size_t j = 0; j < c.size(); ++j) {
    vector< vector<int> > tmpB(4);
    c[j] = tmpB;
    for (size_t i = 0; i < c[j].size(); ++i) {
      vector<int> tmpA(5, i + j);
      c[j][i] = tmpA;
    }
  }

  cout << endl;
  cout << "Three dimensional example" << endl;
  for (size_t k = 0; k < c.size(); ++k) {
    cout << "Next slice..." << endl;
    for (size_t j = 0; j < c[k].size(); ++j) {
      for (size_t i = 0; i < c[k][j].size(); ++i) {
        cout << c[k][j][i] << " ";       // read access via triplet of indices
        c[k][j][i] = 2 * c[k][j][i] + 1; // modify via triplet of indices
      }
      cout << endl;
    }
  }

  return EXIT_SUCCESS;
}
