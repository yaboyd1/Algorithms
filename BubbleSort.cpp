#include <cstdio>    // Provides printf()
#include <cstdlib>   // Provides size_t and NULL
#include <vector>    // Provides vector or dynamic array
#include <algorithm> // Provides swap()
using namespace std;

// Simple node structure for linked list
struct node { 
	int data;
	node* next;
	node(const int& d = 0, node* n = NULL) : data(d), next(n) {}
};

// O(n^2): Swaps values until sorted
void bubbleSort(vector<int>& v); 
void bubbleSort(node*& L);

// Helper functions to print the contents of the array and linked list
void print(const vector<int>& v); 
void print(node * L); 

int main() {

	/* Testing bubble sort with array */
	vector<int> v = {5, 7, 8, 9, 2, 1};

	printf("Original Array:\n");
	print(v);

	bubbleSort(v);

	printf("Bubble Sorted:\n");
	print(v);

	/* Testing bubble sort with linked list */
	node* L = new node(5, new node(7, new node(8, new node(9, new node(2, new node(1))))));

	printf("Original Linked List:\n");
	print(L);

	bubbleSort(L);

	printf("Bubble Sorted:\n");
	print(L);
}

/* Bubble sort keeps swapping values until it is finished */
void bubbleSort(vector<int>& v) {
	bool done = false;
	while (!done) {
		done = true;
		for (size_t i = 1; i < v.size(); ++i) {
			// Swap if the prev item is greater
			if (v[i] < v[i - 1]) {
				swap(v[i], v[i - 1]);
				done = false; // Keep swapping until it can't
			}
		}
	}
}

/* Bubble sort for a linked list includes a pointer to the previous or next item in the linked list */
void bubbleSort(node*& L) {
	if (L == NULL) return; // Empty list
	bool done = false;
	while (!done) {
		done = true;
		for (node *prev = L, *curr = prev->next; curr != NULL; curr = curr->next) {
			// Swap if the prev item is greater
			if (prev->data > curr->data) {
				swap(prev->data, curr->data);
				done = false; // Keep swapping until it can't
			}
			prev = curr; // I can't put two assignments in the for loop :(
		}
	}
}

/* Helper functions using printf instead of cout */
void print(const vector<int>& v) {
	for (int i : v) 
		printf("%i ", i);
	printf("\n");
}

void print(node * L) {
	for (node* i = L; i != NULL; i = i->next)
		printf("%i ", i->data);
	printf("\n");
}
