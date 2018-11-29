#pragma once

#include <iostream>
#include <time.h>

using namespace std;

class Search
{
public:
	Search(int, const int *);
	~Search();

	void setArray(int, const int *);
	int linearSearch(int);
	int bringFrontSearch(bool, int);
	void print();

	static void setRandomNumberSeed();
	static int generateRandomNumber(int, int);

private:
    int temporaryValue, windowIndex, windowLength, arrayLength, *unsortedArray;
    void circularIncrementWindowIndex();
	int bringFrontSearch(int);
    int randomizedBringFrontSearch(int);

	static void swap(int *, int *);
	static void swapByAddition(int *, int *);
	static void swapByXOR(int *, int *);
};