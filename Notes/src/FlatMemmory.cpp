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
	size_t x;
	size_t y;
};

struct Vector3D {
	size_t x;
	size_t y;
	size_t z;
};
// 2D case
const Vector2D indexToIndices(const size_t& index, const size_t& width, const size_t& height);
const size_t indicesToIndex(const Vector2D& indices, const size_t& width, const size_t& height);
// 3D case
const Vector3D indexToIndices3D(const size_t& index, const size_t& width, const size_t& height, const size_t& depth);
const size_t indicesToIndex3D(const Vector3D& indices, const size_t& width, const size_t& height, const size_t& depth);

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
	for (size_t k = 0; k < H; ++k) {
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

const Vector2D indexToIndices(const size_t& index, const size_t& width, const size_t& height) {
	Vector2D indices;
	indices.x = indices.y = 0U;
	// Validate input
	if (width < 2 || height < 2) {
		cerr << "Invalid limits! data is not 2 dimensional" << endl;
		return indices;
	}
	if (index < 0 || index >= (width * height)) {
		cerr << "Invalid index!" << endl;
		return indices;
	}

	indices.x = index % width;
	indices.y = index / width;

	return indices;
}

const size_t indicesToIndex(const Vector2D& indices, const size_t& width, const size_t& height) {
	// Validate input
	if (indices.x < 0 || indices.x >= width || indices.y < 0 || indices.y >= height) {
		cerr << "Invalid indices!" << endl;
		return 0U;
	}
	if (width < 2 || height < 2) {
		cerr << "Invalid limits! data is not 2 dimensional" << endl;
		return 0U;
	}

	//Actual calculation
	size_t index = (width * indices.y) + indices.x;

	return index;
}

const Vector3D indexToIndices3D(const size_t& index, const size_t& width, const size_t& height, const size_t& depth) {
	Vector3D indices;
	indices.x = indices.y = indices.z = 0U;
	// Validate input
	if (width < 2 || height < 2 || depth <= 2) {
		cerr << "Invalid limits! data is not 3 dimensional" << endl;
		return indices;
	}
	if (index < 0 || index >= (width * height * depth)) {
		cerr << "Invalid index!" << endl;
		return indices;
	}

	size_t slice_size = width * height;

	indices.x = index % width;
	indices.y = (index / width) % height;
	indices.z = index / slice_size;

	return indices;
}

const size_t indicesToIndex3D(const Vector3D& indices, const size_t& width, const size_t& height, const size_t& depth) {
	// Validate input
	if (indices.x < 0 || indices.x >= width ||
		indices.y < 0 || indices.y >= height ||
		indices.z < 0 || indices.z >= depth) {
		cerr << "Invalid indices!" << endl;
		return 0U;
	}
	if (width < 2 || height < 2 || depth < 2) {
		cerr << "Invalid limits! data is not 3 dimensional" << endl;
		return 0U;
	}

	//Actual calculation
	size_t slice_size = width * height;
	size_t index = slice_size * indices.z + width * indices.y + indices.x;

	return index;
}
