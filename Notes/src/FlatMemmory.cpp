//============================================================================
// Name        : FlatMemmory.cpp
// Author      : Jorge Garcia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

struct Vector2D {
  int x;
  int y;
};

struct Vector3D {
  int x;
  int y;
  int z;
};
// 2D case
const Vector2D indexToIndices(const int& index, const int& WIDTH, const int& HEIGHT);
const int indicesToIndex(const Vector2D& indices, const int& WIDTH, const int& HEIGHT);
// 3D case
const Vector3D indexToIndices3D(const int& index, const int& WIDTH, const int& HEIGHT, const int& DEPTH);
const int indicesToIndex3D(const Vector3D& indices, const int& WIDTH, const int& HEIGHT, const int& DEPTH);

int main() {
  const size_t W = 5U; // Max Width of the tensor
  const size_t H = 4U; // Max Height of the tensor
  const size_t D = 3U; // Max Depth of the tensor

  vector<int> b(W * H); // Since we do flat memory

  // Testing first function
  cout << "First function" << endl;
  for (size_t i = 0; i < (W * H); ++i) {
    Vector2D tmp = indexToIndices(i, W, H);
    cout << i << ": => \t(" << tmp.x << ", " << tmp.y << ")" << endl;
  }
  cout << endl;

  // testing second function
  cout << "Second function" << endl;
  for (size_t j = 0; j < H; ++j) {
    for (size_t i = 0; i < W; ++i) {
      Vector2D tmpIndices;
      tmpIndices.x = i;
      tmpIndices.y = j;
      size_t tmp = indicesToIndex(tmpIndices, W, H);
      cout << "(" << tmpIndices.x << ", " << tmpIndices.y << "): => \t " << tmp << endl;
    }
  }
  cout << endl;

  // Testing third function
  cout << "3D case" << endl;
  cout << "Third function" << endl;
  for (size_t i = 0; i < (W * H * D); ++i) {
    Vector3D tmp = indexToIndices3D(i, W, H, D);
    cout << i << ": => \t(" << tmp.x << ", " << tmp.y << ", " << tmp.z << ")" << endl;
  }
  cout << endl;

  // testing fourth function
  cout << "Fourth function function" << endl;
  for (size_t k = 0; k < D; ++k) {
    for (size_t j = 0; j < H; ++j) {
      for (size_t i = 0; i < W; ++i) {
        Vector3D tmpIndices;
        tmpIndices.x = i;
        tmpIndices.y = j;
        tmpIndices.z = k;
        size_t tmp = indicesToIndex3D(tmpIndices, W, H, D);
        cout << "(" << tmpIndices.x << ", " << tmpIndices.y << ", " << tmpIndices. z << "): => \t " << tmp << endl;
      }
    }
  }
  cout << endl;

  return EXIT_SUCCESS;
}

const Vector2D indexToIndices(const int& index, const int& WIDTH, const int& HEIGHT) {
  Vector2D indices;
  indices.x = indices.y = -1;
  // Validate input
  if (WIDTH < 2 || HEIGHT < 2) {
    cerr << "Invalid limits! data is not 2 dimensional" << endl;
    return indices;
  }
  if (index < 0 || index >= (WIDTH * HEIGHT)) {
    cerr << "Invalid index!" << endl;
    return indices;
  }
  //Actual calculation
  indices.x = index % WIDTH;
  indices.y = index / WIDTH;

  return indices;
}

const int indicesToIndex(const Vector2D& indices, const int& WIDTH, const int& HEIGHT) {
  // Validate input
  if (indices.x < 0 || indices.x >= WIDTH || indices.y < 0 || indices.y >= HEIGHT) {
    cerr << "Invalid indices!" << endl;
    return -1;
  }
  if (WIDTH < 2 || HEIGHT < 2) {
    cerr << "Invalid limits! data is not 2 dimensional" << endl;
    return -1;
  }
  //Actual calculation
  const int index = (WIDTH * indices.y) + indices.x;

  return index;
}

const Vector3D indexToIndices3D(const int& index, const int& WIDTH, const int& HEIGHT, const int& DEPTH) {
  Vector3D indices;
  indices.x = indices.y = indices.z = -1;
  // Validate input
  if (WIDTH < 2 || HEIGHT < 2 || DEPTH < 2) {
    cerr << "Invalid limits! data is not 3 dimensional" << endl;
    return indices;
  }
  if (index < 0 || index >= (WIDTH * HEIGHT * DEPTH)) {
    cerr << "Invalid index!" << endl;
    return indices;
  }
  //Helper variable
  const int slice_size = WIDTH * HEIGHT;
  //Actual calculations
  indices.x = index % WIDTH;
  indices.y = (index / WIDTH) % HEIGHT;
  indices.z = index / slice_size;

  return indices;
}

const int indicesToIndex3D(const Vector3D& indices, const int& WIDTH, const int& HEIGHT, const int& DEPTH) {
  // Validate input
  if (indices.x < 0 || indices.x >= WIDTH ||
      indices.y < 0 || indices.y >= HEIGHT ||
      indices.z < 0 || indices.z >= DEPTH) {
    cerr << "Invalid indices!" << endl;
    return -1;
  }
  if (WIDTH < 2 || HEIGHT < 2 || DEPTH < 2) {
    cerr << "Invalid limits! data is not 3 dimensional" << endl;
    return -1;
  }
  //Helper variable
  const int slice_size = WIDTH * HEIGHT;
  //Actual calculation
  const int index = slice_size * indices.z + WIDTH * indices.y + indices.x;

  return index;
}

/*
const int indicesToIndex3D(const Vector3D& indices, const int& WIDTH, const int& HEIGHT, const int& DEPTH) {
  // Validate input
  if (indices.x < 0 || indices.x >= WIDTH ||
      indices.y < 0 || indices.y >= HEIGHT ||
      indices.z < 0 || indices.z >= DEPTH) {
    cerr << "Invalid indices!" << endl;
    return -1;
  }
  if (WIDTH < 2 || HEIGHT < 2 || DEPTH < 2) {
    cerr << "Invalid limits! data is not 3 dimensional" << endl;
    return -1;
  }
  //Actual calculation
  const int index =
                             1 * indices.x +
                         WIDTH * indices.y +
              (WIDTH * HEIGHT) * indices.z;

  return index;
}

const Vector3D indexToIndices3D(const int& index, const int& WIDTH, const int& HEIGHT, const int& DEPTH) {
  Vector3D indices;
  indices.x = indices.y = indices.z = -1;
  // Validate input
  if (WIDTH < 2 || HEIGHT < 2 || DEPTH <= 2) {
    cerr << "Invalid limits! data is not 3 dimensional" << endl;
    return indices;
  }
  if (index < 0 || index >= (WIDTH * HEIGHT * DEPTH)) {
    cerr << "Invalid index!" << endl;
    return indices;
  }
  //Actual calculation
  indices.x =                (index / 1) % WIDTH;
  indices.y =            (index / WIDTH) % HEIGHT;
  indices.z = (index / (WIDTH * HEIGHT)) % DEPTH;

  return indices;
}
*/
