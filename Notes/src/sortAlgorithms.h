#pragma once

template<typename Iterator>
Iterator partition(const Iterator left, const Iterator right) {
	// In our implementation the pivot it's the last element
	// of the interval
	const Iterator pivot_place = right - 1;
	// We start assuming all the elements are greater than the pivot
	// in other words: the partition point it's at the beginning
	Iterator partition_place = left;
	// We transverse the interval minus the pivot (which it's at the end)
	for (auto it = left; it != pivot_place; ++it) {
		// If this element is smaller than the pivot
		if (*it <= *pivot_place) {
			// swap it with the one at the partition point
			std::swap(*partition_place, *it);
			// move the partition point
			++partition_place;
		}
	}
	// put the pivot in his corresponding place
	std::swap(*partition_place, *pivot_place);
	// return the partition place
	return partition_place;
}

template<typename Iterator>
void quick_sort(const Iterator begin, const Iterator end) {
	// If the interval contains more than one element
	if (std::distance(begin, end) > 1) {
		// Make a partition of the collection
		Iterator partition_place = partition(begin, end);
		// After the previous call, the only element granted to be
		// in his position it's the pivot (which is at the partition point)
		// Sort the left subinterval
		quick_sort(begin, partition_place);
		// Sort the right subinterval
		quick_sort(partition_place + 1, end);
	}
}

template<typename Iterator>
void selection_sort(const Iterator begin, const Iterator end) {
	// Transverse the whole range
	for (auto jt = begin; jt != end; ++jt) {
		Iterator minElemIter = jt; // Assume minimum is at the start
		// Search for the actual minimum in the remainder of the interval
		for (auto it = (jt + 1); it != end; ++it) {
			if (*it < *minElemIter) {
				minElemIter = it;
			}
		}
		// If the minimum it's not at the start
		if (minElemIter != jt) {
			// swap the two elements
			std::swap(*minElemIter, *jt);
		}
	}
}

// Take an array in which his individual halves are sorted
// an merge it in a complete sorted array
template<typename Iterator>
void merge(const Iterator begin, const Iterator middle, const Iterator end) {
	Iterator lowHalfIt = begin; // index of the lower (left) half
	Iterator highHalfIt = middle; // index of the upper (right) half
	//Create a temporary merge buffer
	std::vector<typename Iterator::value_type> buffer(std::distance(begin, end));
	// Merge the two halves into the buffer
	for (auto it = buffer.begin(); it != buffer.end(); ++it) {
		// If the lower half list is not over and (the second list is over OR the minimum)
		// Look for the minimum element of both list current indices
		if (lowHalfIt != middle	&& (highHalfIt == end || *lowHalfIt <= *highHalfIt)) {
			// Take the one from the lower half
			*it = *lowHalfIt;
			lowHalfIt++;
		} else {
			// Take the one from the higher half
			*it = *highHalfIt;
			highHalfIt++;
		}
	}
	// Copy the contents of the buffer back to the input
	auto bufferIt = buffer.begin();
	for (auto it = begin; it < end; ++it) {
		*it = *bufferIt;
		bufferIt++;
	}
}

template<typename Iterator>
void merge_sort(const Iterator begin, const Iterator end) {
	// If this array has more than one element (otherwise it's already sorted)
	if (std::distance(begin, end) > 1) {
		// Calculate the middle point of the array
		Iterator middle = begin;
		std::advance(middle, std::distance(begin, end) / 2);
		// Sort the lower half
		merge_sort(begin, middle);
		// Sort the upper half
		merge_sort(middle, end);
		// Merge the sorted halves to create a complete sorted array
		merge(begin, middle, end);
	}
}

// Since we are using an implicit heap in the array we use the
// following helper functions.
// Return an iterator to the the left child or end if it does not exist
template<typename Iterator>
inline Iterator left_child(const Iterator &parentIter, const Iterator &begin, const Iterator &end) {
	Iterator result = parentIter;
	// Maximum valid advance of the current iterator
	size_t max_move = std::distance(parentIter, end);
	// Needed advance to get to the left child
	size_t move = std::distance(begin, parentIter) + 1;
	// If there is no room for the needed advance (you don't have left child)
	// just return the end
	if (move >= max_move) {
		result = end;
	} else {
		// You do have a left child, advance to it
		std::advance(result, move);
	}
	return result;
}
// Return an iterator to the the right child or end if it does not exist
template<typename Iterator>
inline Iterator right_child(const Iterator &parentIter, const Iterator &begin,
		const Iterator &end) {
	Iterator leftChild = left_child(parentIter, begin, end);
	return (leftChild != end) ? (leftChild + 1) : end;
}
// Return an iterator to the parent node
template<typename Iterator>
inline Iterator parent_of(const Iterator &childIter, const Iterator &begin) {
	Iterator result = begin;
	std::advance(result, std::distance(begin + 1, childIter) / 2);
	return result;
}
// Restore the heap property from the sub heap rooted at currentRoot
// The heap its stored in the collection from begin to end.
// Begin is inclusive and end is exclusive i. e [begin, end)
template<typename Iterator>
void sift_down(const Iterator &currentRoot, const Iterator &begin,
		const Iterator &end) {
	Iterator currentIter = currentRoot;
	// While the root has at least one child
	while (left_child(currentIter, begin, end) != end) {
		// The first candidate to swap it's you
		// this means no swap needed
		Iterator toSwapIter = currentIter;
		Iterator leftChildIter = left_child(currentIter, begin, end);
		// If you are smaller than left child
		if (*toSwapIter < *leftChildIter) {
			// your candidate to swap it's the left child
			toSwapIter = leftChildIter;
		}
		// Unless, there is a right child and it's smaller than the candidate
		Iterator rightChilldIter = right_child(currentIter, begin, end);
		if (rightChilldIter != end && *toSwapIter < *rightChilldIter) {
			// then, you need to swap with the right child
			toSwapIter = rightChilldIter;
		}
		// There is no more possible swaps we are done
		if (toSwapIter == currentIter) {
			return;
		} else {
			// perform a swap and move to the next node
			std::swap(*currentIter, *toSwapIter);
			currentIter = toSwapIter;
		}
	}
}
// Transform the input collection into a max heap
template<typename Iterator>
void heapify(const Iterator &begin, const Iterator &end) {
	// Find an iterator to the parent of the last element in the collection
	Iterator currentNodeIter = parent_of(end - 1, begin);
	// Build the heap from bottom to top
	// Do this while current node it not the root
	while (std::distance(begin, currentNodeIter) >= 0) {
		// Sift down the nodes to the left of the current one
		// so they are in heap order
		sift_down(currentNodeIter, begin, end);
		// Go to the next parent node
		currentNodeIter--;
	}
}

// Order the given collection range using heap sort
template<typename Iterator>
void heap_sort(const Iterator &begin, const Iterator &end) {
	// Start by creating a valid in place heap of the array
	heapify(begin, end);
	Iterator lastElementIter = end - 1;
	while (std::distance(begin, lastElementIter) > 0) {
		// Since the range is a max heap the first element it's the largest
		// put it in his place
		std::swap(*begin, *lastElementIter);
		// The swap ruined the heap, restore it
		// end is exclusive [begin, end), this will not affect lastElementIter
		sift_down(begin, begin, lastElementIter);
		// The heap size is reduced by one
		lastElementIter--;
	}
}

namespace vecsort {
void selection_sort(std::vector<int> &v);
void quick_sort(std::vector<int> &v);
void merge_sort(std::vector<int> &v);
void heap_sort(std::vector<int> &v);
}
