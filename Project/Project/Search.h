#pragma once

#include <iostream>
#include <time.h>
#include <unordered_map>
#include <map>

#include "DynamicArray.h"
#include "DynamicArray.cpp"

class Search
{
public:
	Search(int, int *);
	~Search();

	void setUnsortedArray(int, int *);
	void reset();

	int unoptimizedLinearSearch(int);
	int optimizedLinearSearch(int);
	int bringFrontSearch(int);
	int unorderedMapSearch(int);
	int orderedMapSearch(int);
	int dynamicArraySearch(int);

	int unorderedMapSearchByIndex(int);
	int orderedMapSearchByIndex(int);
	int dynamicArraySearchByIndex(int);

	static void setRandomNumberSeed();
	static int generateRandomNumber(int, int);

private:
    int windowIndex, windowLength, arrayLength, *unsortedArray, *initialUnsortedArray;
	
	std::unordered_map<int, int> unorderedMap;
	std::map<int, int> orderedMap;

	DynamicArray<int> *dynamicArray;

    void circularIncrementWindowIndex();

	static void swap(int *, int *);
	static void swapByAddition(int *, int *);
	static void swapByXOR(int *, int *);
};