#include <cstdio>  // Provides printf()
#include <cstdlib> // Provides size_t
#include <vector>  // Provides vector or dynamic array
using namespace std;

// Helper functions to test out sorting algos
vector<int> generateRandom(size_t length = 10, size_t min = 1, size_t max = 100);
bool isSorted(const vector<int>& V);
void print(const vector<int>& V);

void mergeSort(vector<int>& V);
void merge(const vector<int>& firstHalf, const vector<int>& secondHalf, vector<int>& V);

int main() {
	// Generate N random numbers
	const int N = 1e1;

	printf("Original:\n");
	vector<int> V = generateRandom(N);
	print(V);

	// Test merge sort
	printf("Merge Sorted:\n");
	mergeSort(V);
	print(V);

	printf("%s\n", isSorted(V) ? "Successful!" : "Unsuccessful :(");
	return 0;
}

void mergeSort(vector<int>& V) {
	if (V.size() <= 1) return;

	vector<int> firstHalf;
	for (int i = 0; i < V.size() / 2; ++i)
		firstHalf.push_back(V[i]);

	vector<int> secondHalf;
	for (int i = V.size() / 2; i < V.size(); ++i)
		secondHalf.push_back(V[i]);

	mergeSort(firstHalf);
	mergeSort(secondHalf);

	merge(firstHalf, secondHalf, V);
}

void merge(const vector<int>& first, const vector<int>& second, vector<int>& V) {
	// Resize to make sure both vector lengths fit
	const size_t FIRST = first.size(), SECOND = second.size();
	V.resize(FIRST + SECOND);

	// Index of where to insert item (at the start)
	size_t index = 0;

	// Put the smaller item at the start of the new vector
	size_t i = 0, j = 0;
	while (i < FIRST && j < SECOND) {
		if (first[i] < second[j])
			V[index++] = first[i++];
		else 
			V[index++] = second[j++];
	}

	// Finish the other array if they are not the same size
	while (i < FIRST)
		V[index++] = first[i++];

	while (j < SECOND)
		V[index++] = second[j++];
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