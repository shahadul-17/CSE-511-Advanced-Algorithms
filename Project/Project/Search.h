#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <time.h>

using namespace std;

class Search
{
public:
	Search(int, int *);
	~Search();

	void setArray(int, int *);
	void resetArray();
	int linearSearch(int);
	int bringFrontSearch(bool, int);
	void print();

	static int generateRandomNumber(int, int);

private:
    int temporaryValue, windowIndex, windowLength, arrayLength, *unsortedArray, *initialUnsortedArray;
    void circularIncrementWindowIndex();
	int bringFrontSearch(int);
    int randomizedBringFrontSearch(int);

	static void swap(int *, int *);
	static void swapByAddition(int *, int *);
	static void swapByXOR(int *, int *);
};