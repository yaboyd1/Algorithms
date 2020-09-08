#include <cstdio>    // Provides printf()
#include <cstdlib>   // Provides size_t
#include <vector>    // Provides vector or dynamic array
#include <algorithm> // Provides swap()
using namespace std;

// Helper functions to test out sorting algos
vector<int> generateRandom(size_t length = 10, size_t min = 1, size_t max = 100);
bool isSorted(const vector<int>& V);
void print(const vector<int>& V);

// Swap current index with the next minimum index
void selectionSort(vector<int>& V);
void selectionSort2(vector<int>& V); 

int main() {
	// Generate N random numbers
	const int N = 1e4;

	printf("Original:\n");
	vector<int> V = generateRandom(N);
	vector<int> V2(V);
	print(V);

	// Test first algorithm
	printf("Algorithm 1:\n");
	selectionSort(V);
	print(V);

	printf("%s\n", isSorted(V) ? "Successful!" : "Unsuccessful :(");

	// Test second algorithm
	printf("Algorithm 2:\n");
	selectionSort2(V2);
	print(V2);

	printf("%s\n", isSorted(V2) ? "Successful!" : "Unsuccessful :(");
}

void selectionSort(vector<int>& V) {
	for (size_t i = 0; i < V.size() - 1; ++i)
		for (size_t j = i + 1; j < V.size(); ++j)
			if (V[j] < V[i])
				swap(V[j], V[i]);
}

void selectionSort2(vector<int>& V) {
	for (size_t i = 0; i < V.size() - 1; ++i) {
		size_t minIndex = i;
		for (size_t j = i + 1; j < V.size(); ++j) {
			if (V[j] < V[minIndex])
				minIndex = j;
		}
		if (i != minIndex) // No unnecessary swaps
			swap(V[i], V[minIndex]);
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

