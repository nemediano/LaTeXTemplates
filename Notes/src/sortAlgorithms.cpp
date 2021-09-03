#include "pch.h"
#include "sortAlgorithms.h"

using namespace std;

namespace vecsort {
void selection_sort(vector<int> &v) {
	// Transverse the whole range
	for (size_t j = 0; j < v.size(); ++j) {
		size_t minElemIndex = j; // Assume minimum is at the start
		// Search for the actual minimum in the remainder of the interval
		for (size_t i = j + 1; i < v.size(); ++i) {
			if (v[i] < v[minElemIndex]) {
				minElemIndex = i;
			}
		}
		// If the minimum it's not at the start
		if (minElemIndex != j) {
			// swap the two elements
			std::swap(v[minElemIndex], v[j]);
		}
	}
}

/*
 The interval is in usual iterator range
 i. e: [left, right)
 The last element in the interval is one before the end
 */
size_t partition(vector<int> &v, const size_t left, const size_t right) {
	// In our implementation the pivot it's the last element
	// of the interval
	const size_t pivot_index = right - 1;
	// We start assuming all the elements are greater than the pivot
	// In other words the partition point it's at the beginning
	size_t partition_point = left;
	// We traverse the interval minus the pivot (which it's at the end)
	for (auto i = left; i < pivot_index; ++i) {
		// If this element is smaller than the pivot
		if (v[i] <= v[pivot_index]) {
			// swap it with the one at the partition point
			swap(v[partition_point], v[i]);
			// Move the partition point
			++partition_point;
		}
	}
	// Put the pivot in his corresponding place
	swap(v[partition_point], v[pivot_index]);
	// return the partition point
	return partition_point;
}
/*
 The interval is in usual iterator range
 i. e: [left, right)
 The last element in the interval is one before the end
 */
void quick_sort(vector<int> &v, size_t begin, size_t end) {
	// If the interval contains more than one element
	if ((end - begin) > 1) {
		// Partition the collection
		size_t partition_index = partition(v, begin, end);
		// After the previous call, the only element granted to be
		// in his position is the pivot (which it's at the partition point)
		// Sort the left subinterval
		quick_sort(v, begin, partition_index);
		// Sort the right subinterval
		quick_sort(v, partition_index + 1, end);
	}
}

// Wrapper method to make the first recursive call
void quick_sort(vector<int> &v) {
	// Sort the whole array
	quick_sort(v, 0, v.size());
}

// Take an array in here his individual halves are sorted
// an merge it in a complete sorted array
void merge(vector<int> &input, size_t begin, size_t middle, size_t end) {
	size_t lowHalfIndex = begin; // index of the lower (left) half
	size_t highHalfIndex = middle; // index of the upper (right) half
	//Create a temporary merge buffer
	vector<int> buffer(end - begin);
	// Merge the two halves into the buffer
	for (size_t i = 0; i < buffer.size(); ++i) {
		// If the lower half list is not over and (the second list is over OR the minimum)
		// Look for the minimum element of both list current indices
		if (lowHalfIndex < middle
				&& (highHalfIndex >= end
						|| input[lowHalfIndex] <= input[highHalfIndex])) {
			// Take the one from the lower half
			buffer[i] = input[lowHalfIndex];
			lowHalfIndex++;
		} else {
			// Take the one from the higher half
			buffer[i] = input[highHalfIndex];
			highHalfIndex++;
		}
	}
	// Copy the contents of the buffer back to the input
	size_t bufferIndex = 0;
	for (size_t i = begin; i < end; ++i) {
		input[i] = buffer[bufferIndex++];
	}
}

void merge_sort(vector<int> &input, size_t begin, size_t end) {
	// If this array has more than one element (otherwise it's already sorted)
	if ((end - begin) > 1) {
		// Calculate the middle point of the array
		size_t middle = (begin + end) / 2;
		// Sort the lower half
		merge_sort(input, begin, middle);
		// Sort the upper half
		merge_sort(input, middle, end);
		// Merge the sorted halves to create a complete sorted array
		merge(input, begin, middle, end);
	}
}

// Wrapper method to make the first recursive call
void merge_sort(vector<int> &v) {
	// Sort the whole array
	merge_sort(v, 0, v.size());
}
// Since we are using an implicit heap in the array we use the
// following helper functions. Remember, C++ it's a zero based index language
// Return the index of the left child
size_t left_child(const size_t &parentIndex) {
	return 2 * parentIndex + 1;
}
// Return the index of the right child
size_t right_child(const size_t &parentIndex) {
	return 2 * parentIndex + 2;
}
// Return the index of the parent node
size_t parent_of(const size_t &childIndex) {
	return (childIndex - 1) / 2;
}
// Restore the heap property from the subtree rooted at begin
void sift_down(vector<int> &v, const size_t begin, const size_t end) {
	size_t currentRootIndex = begin;
	// While the root has at least one child
	while (left_child(currentRootIndex) < end) {
		size_t toSwapIndex = currentRootIndex;
		size_t leftChildIndex = left_child(currentRootIndex);
		// If you are smaller than left child
		if (v[toSwapIndex] < v[leftChildIndex]) {
			// you need to swap with the left child
			toSwapIndex = leftChildIndex;
		}
		// Unless, there is a right child and it's also smaller
		size_t rightChilldIndex = right_child(currentRootIndex);
		if (rightChilldIndex < end && v[toSwapIndex] < v[rightChilldIndex]) {
			// then, you need to swap with the right child
			toSwapIndex = rightChilldIndex;
		}
		// There is no more possible swaps we are done
		if (toSwapIndex == currentRootIndex) {
			return;
		} else {
			// perform a swap and move to the next node
			std::swap(v[currentRootIndex], v[toSwapIndex]);
			currentRootIndex = toSwapIndex;
		}
	}
}

// Transform the input array into a max heap
void heapify(vector<int> &v) {
	// Find the index of the parent of the last element in the array
	int currentNodeIndex = parent_of(v.size() - 1);
	// Build the heap from bottom to top
	// Do this while current node it not the root
	while (currentNodeIndex >= 0) {
		// Sift down the nodes to the left of the current one
		// so they are in heap order
		sift_down(v, currentNodeIndex, v.size());
		// Go to the next parent node
		currentNodeIndex--;
	}
}

void heap_sort(std::vector<int> &v) {
	// Start by creating a valid in place heap of the array
	heapify(v);
	size_t lastElementIndex = v.size() - 1;
	while (lastElementIndex > 0) {
		// Since v is a max heap the first element it's the largest
		// put it in his place
		std::swap(v[0], v[lastElementIndex]);
		// The swap ruined the heap, restore it
		sift_down(v, 0, lastElementIndex);
		// The heap size is reduced by one
		lastElementIndex--;
	}
}

}
