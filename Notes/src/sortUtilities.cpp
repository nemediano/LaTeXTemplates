#include "pch.h"
#include "sortUtilities.h"

using namespace std;

void print_vector(const vector<int>& v) {
    if (v.empty()) {
        return;
    }
    for (size_t i = 0; i < v.size() - 1; ++i) {
        cout << v[i] << " ";
    }
    cout << v[v.size() - 1] << endl;
}

void create_input(vector<int>& v, bool unique) {
    const size_t SIZE = 10;
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    cout << "Seed: " << seed << endl;
    std::default_random_engine generator(seed);

    v.clear(); // Making sure output parameter is empty

    if (unique) {
        // Create ordered consecutive elements
        for (size_t i = 0; i < SIZE; ++i) {
            v.push_back(i + 1);
        }
        // shuffle them
        shuffle(v.begin(), v.end(), generator);
    }
    else {
        std::uniform_int_distribution<int> distribution(1, int(2 * SIZE));
        // Create the input
        for (size_t i = 0; i < SIZE; ++i) {
            v.push_back(distribution(generator));
        }
    }
}