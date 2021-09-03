#include "pch.h"

#include "sortUtilities.h"
#include "sortAlgorithms.h"
using namespace std;

int main(int argc, char *argv[]) {

	vector<int> input;
	// Populate the input
	create_input(input, false);
	// Order the input using std, to create the "expected output"
	vector<int> expected_output = input; // copy
	sort(expected_output.begin(), expected_output.end());
	// Copy input in output since our algorithm should be in place
	vector<int> output = input;
	// Before we start we show the input
	cout << "Input:" << endl;
	print_vector(input);

	// sort output using the tested method
	heap_sort(output.begin(), output.end());

	// See the results
	if (output == expected_output) {
		cout << "Output:" << endl;
		print_vector(output);
		cout << "Success!" << endl;
	} else {
		cout << "Expected output:" << endl;
		print_vector(expected_output);
		cout << "Output:" << endl;
		print_vector(output);
		cout << "Fail!" << endl;
	}

	return EXIT_SUCCESS;
}
