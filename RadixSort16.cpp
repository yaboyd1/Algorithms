#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

// PRECONDITION: A is an array of integers less than 2^32, n is the non-negative size of the array
// and implementation of "Bucket", my own Linked List that just inserts at the tail
// POSTCONDITION: Sorts froms least to greatest
// ALGORITHM: Add each digit value to a corresponding bucket. Copy every bucket back into array. Again.
void sort(int *A, int n);

void print(int* a, int n); // Prints the contents of the array "[1, 2.. n]"

int main() {
	const int N = 1e7; // Amount of numbers to sort

	int i, offset, j;
	int *B = new int[N];
	time_t t;
	srand((unsigned)time(&t));
	offset = rand() % N;

	for (i = 0; i < N; i++)
		B[i] = ((91 * i) % N) + offset;

	printf("Prepared array of %i integers; Calling sort()\n", N);
	sort(B, N);
	printf("Finished sort(), now checking results\n");

	for (i = 0, j = 0; i < N; i++)
		if (B[i] != i + offset)
			j++;

	if (j == 0)
		printf("Passed Test\n");
	else
		printf("Failed Test. %d numbers wrong.\n", j);

	time_t now;
	time(&now);
	printf("%i seconds!\n", int(now - t));

	return 0;
}

// Node for Singly Linked List
struct node {
	int data;
	node* next;
	node(const int& d = 0, node* n = NULL) : data(d), next(n) {}
};

// Linked List but more limited (inserts at the tail only)
class Bucket {
private:
	node *head, *tail;
public:
	Bucket() {
		head = tail = NULL;
	}

	// Inserts items at the tail or end of the Linked List
	void insert(const int& value) {
		if (head == NULL)
			head = tail = new node(value);
		else
			tail = tail->next = new node(value);
	}

	// Clears all items of the Linked List
	void clear() {
		node* i;
		while(head != NULL) {
			i = head;
			head = head->next;
			delete i;
		}
		head = tail = NULL;
	}

	// I didn't want to make the head public for some reason so...
	node* getHead() {
		return head;
	}

	// Prints the contents of the Linked List "( 1, 2.. n )"
	void print() const {
		printf("( ");
		for(node* i = head; i != NULL; i = i->next)
			printf("%i ", i->data);
		printf(")\n");
	}
};

void sort(int *A, int n) {
	// Create 16^4 buckets
	const int BUCKETS = 16 * 16 * 16 * 16;
	Bucket* buckets = new Bucket[BUCKETS];

	for (int shift = 0; shift <= 16; shift += 16) {
		// Add first digit or 0xFFFF digit into each bucket
		for (int i = 0; i < n; ++i)
			buckets[(A[i] >> shift) & 0xFFFF].insert(A[i]);
		
		// Copy buckets back into the array
		int index = 0;
		for (int i = 0; i < BUCKETS; ++i)
			for (node* j = buckets[i].getHead(); j != NULL; j = j->next)
				A[index++] = j->data;

		// Clear buckets for next iteration
		for (int i = 0; i < BUCKETS; ++i)
			buckets[i].clear();
	}
}

void print(int* a, int n) {
	printf("[");
	for (int i = 0; i < n - 1; ++i)
		printf("%i, ", a[i]);
	printf("%i]\n", a[n - 1]);
}