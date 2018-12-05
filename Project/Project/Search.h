#pragma once

#include <iostream>
#include <time.h>

class Search
{
public:
	Search(int, int *);
	~Search();

	void setUnsortedArray(int, int *);
	void reset();
	int linearSearch(int);
	int bringFrontSearch(int);

	static void setRandomNumberSeed();
	static int generateRandomNumber(int, int);

private:
    int windowIndex, windowLength, arrayLength, *unsortedArray, *initialUnsortedArray;

    void circularIncrementWindowIndex();

	static void swap(int *, int *);
	static void swapByAddition(int *, int *);
	static void swapByXOR(int *, int *);
};