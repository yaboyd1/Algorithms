#include <cstdio>    // Provides printf()
#include <cstdlib>   // Provides rand()
#include <vector>    // Provides vector
#include <algorithm> // Provides swap()
using namespace std;

void quickSort(vector<int>& V, int left, int right);
int partition(vector<int>& V, int left, int right);
void print(const vector<int>& V);

int main() {
	vector<int> V = {4,5,2,1,5,7,2,6};
	quickSort(V, 0, V.size() - 1);
	print(V);

	return 0;
}

void quickSort(vector<int>& V, int left, int right) {
	if (left >= right) return;

	int pivotIndex = partition2(V, left, right);

	quickSort(V, left, pivotIndex - 1);
	quickSort(V, pivotIndex + 1, right);
}

int partition(vector<int>& V, int left, int right) {
	// Choose pivot, swap with end. V[right] is pivot
	int pivotIndex = (left + right) / 2;
	swap(V[pivotIndex], V[right]);

	// Reset pivotIndex to find new swaps
	pivotIndex = left;
	for (int i = left; i < right; ++i) {
		if (V[i] <= V[right]) {
			swap(V[i], V[pivotIndex]);
			++pivotIndex;
		}
	}

	// Swap pivot to correct place and return
	swap(V[pivotIndex], V[right]);
	return pivotIndex;
}

void print(const vector<int>& V) {
	printf("[");
	for (int i = 0; i < V.size() - 1; ++i) 
		printf("%i, ", V[i]);
	printf("%i]\n", V[V.size() - 1]);
}