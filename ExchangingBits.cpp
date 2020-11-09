#include <cstdio>
#include <iostream>
#include <bitset>
using namespace std;

// Exhange the first n bits of two integers
void exch(int *a, int *b, unsigned int n = 0xFF);

int main() {
	// Two values we want to swap
	int x = 515;
	int y = 1028;
	
	// Pointers to the values
	int* a = &x;
	int* b = &y;
	
	// Visual the bits
	bitset<16> aBits(*a);
	bitset<16> bBits(*b);
	printf("a: %i, b: %i \n", *a, *b);
	cout << "a: " << aBits << endl << "b: " << bBits << endl;
	
	exch(a, b);
	
	// Visual the bits after the exhange
	bitset<16> axBits(*a);
	bitset<16> byBits(*b);
	printf("a: %i, b: %i \n", *a, *b);
	cout << "a: " << axBits << endl << "b: " << byBits << endl;

	return 0;
}

void exch(int *a, int *b, unsigned int n) {
	int temp = (*a ^ *b) & n;
	*a ^= temp;
	*b ^= temp;
}