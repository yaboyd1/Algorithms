#include <cstdio>    // Provides printf()
#include <cstdlib>   // Provides size_t
#include <vector>    // Provides vector or dynamic array
#include <climits>   // Provides INT_MAX
#include <algorithm> // Provides swap()
using namespace std;

// Helper functions to test out sorting algos
vector<int> generateRandom(size_t length = 10, size_t min = 1, size_t max = 100);
bool isSorted(const vector<int>& V);
void print(const vector<int>& V);

void mergeSort(vector<int>& V);
void merge(const vector<int>& first, const vector<int>& second, const vector<int>& third, vector<int>& V);

int main() {
	// Generate N random numbers
	const int N = 1e1;

	printf("Original:\n");
	vector<int> V = generateRandom(N);
	print(V);

	// Test merge sort 
	printf("Merge Sort:\n");
	mergeSort(V);
	print(V);

	printf("%s\n", isSorted(V) ? "Successful!" : "Unsuccessful :(");
	return 0;

	// // Testing merge function
	// vector<int> F = {1,1,1,1,2,3,4,5};
	// vector<int> S = {2,4,6};
	// vector<int> T = {1,2,3,23,34};
	// vector<int> output;
	// merge(F, S, T, output);
	// print(output);
}

void mergeSort(vector<int>& V) {
	if (V.size() <= 1) {
		return;
	}
	if (V.size() == 2) {
		if (V[0] > V[1]) {
			swap(V[0], V[1]);
		}
		return;
	}

	// Splicing vector into thirds using iterator constructor
	const size_t THIRD = V.size() / 3;
	vector<int> first(V.begin(), V.begin() + THIRD);
	vector<int> second(V.begin() + THIRD, V.begin() + 2 * THIRD);
	vector<int> third(V.begin() + 2 * THIRD, V.end());

	mergeSort(first);
	mergeSort(second);
	mergeSort(third);

	merge(first, second, third, V);
}

void merge(const vector<int>& first, const vector<int>& second, const vector<int>& third, vector<int>& V) {
	const size_t FIRST = first.size();
	const size_t SECOND = second.size();
	const size_t THIRD = third.size();

	V.resize(FIRST + SECOND + THIRD);

	size_t i = 0, j = 0, k = 0;
	bool iempty = false, jempty = false, kempty = false;

	size_t min = INT_MAX;
	size_t* minIndex = &i;

	for (size_t index = 0; index < V.size(); ++index) {
		// If empty, don't find the minimum of that number
		// Find the minimum of 3/2/1 numbers
		// Add the minimum into the array
		if (i >= FIRST)
			iempty = true;
		if (j >= SECOND)
			jempty = true;
		if (k >= THIRD)
			kempty = true;

		if (!iempty && first[i] < min) {
			min = first[i];
			minIndex = &i;
		}
		if (!jempty && second[j] < min) {
			min = second[j];
			minIndex = &j;
		}
		if (!kempty && third[k] < min) {
			min = third[k];
			minIndex = &k;
		}

		V[index] = min;
		(*minIndex)++;

		min = INT_MAX;
	}
}

vector<int> generateRandom(size_t length, size_t min, size_t max) {
	vector<int> V(length);
	for (size_t i = 0; i < length; ++i)
		V[i] = rand() % max + min;
	return V;
}

bool isSorted(const vector<int>& V) {
	for (size_t i = 1; i < V.size(); ++i)
		if (V[i] < V[i - 1])
			return false;
	return true;
}

void print(const vector<int>& V) {
	for (int i : V) 
		printf("%i ", i);
	printf("\n");
}