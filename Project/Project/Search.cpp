#include "Search.h"

using namespace std;

Search::Search(int arrayLength, int *unsortedArray)
{
	this->unsortedArray = NULL;

	setUnsortedArray(arrayLength, unsortedArray);
}

Search::~Search()
{
	delete [] unsortedArray;		// releasing the resource occupied by the dynamically allocated unsorted array...
}

void Search::setUnsortedArray(int arrayLength, int *unsortedArray)
{
    windowIndex = 0;
	initialUnsortedArray = unsortedArray;

	if (this->arrayLength != arrayLength)
	{
		if (this->unsortedArray != NULL)
		{
			delete [] this->unsortedArray;		// deleting previously allocated array...
		}

		windowLength = arrayLength / 4;		// window length should be quarter of the array length...
		this->arrayLength = arrayLength;
		this->unsortedArray = new int[arrayLength];
	}

	memcpy(this->unsortedArray, unsortedArray, arrayLength * sizeof(int));
}

void Search::reset()
{
	setUnsortedArray(arrayLength, initialUnsortedArray);
}

// most optimized linear search (minimized number of comparisons)...
// original source: https://www.geeksforgeeks.org/search-element-unsorted-array-using-minimum-number-comparisons/
int Search::linearSearch(int query)
{
	const int lastIndex = arrayLength - 1;

	if (query == unsortedArray[lastIndex])
	{
		return lastIndex;
	}

	int temporaryValue = unsortedArray[lastIndex];
	unsortedArray[lastIndex] = query;

	for (int i = 0; ; i++)
	{
		if (query == unsortedArray[i])
		{
			unsortedArray[lastIndex] = temporaryValue;

			if (i < lastIndex)
			{
				return i;
			}

			return -1;
		}
	}
}

void Search::circularIncrementWindowIndex()       // O (1)
{
    if (windowIndex < windowLength)        // O (1)
    {
        windowIndex++;                   // O (1)
    }
    else
    {
        windowIndex = 0;                   // O (1)
    }
}

int Search::bringFrontSearch(int query)		// based on most optimized linear search (minimized number of comparisons)...
{
	int index = linearSearch(query);

	if (index > windowLength)           // O (1)
	{
		/*
		* if one element with same value as query already exists within the window...
		* we should increment index of window by 1...
		*/
		while (query == unsortedArray[windowIndex])       // O (n) -> but in reality it, probability of 'n' being large is very small...
		{
			circularIncrementWindowIndex();       // O (1)
		}

		// swapping the index i'th element with the index windowIndex'th element...
		// note: can be replaced by any kind of swap...
		swapByXOR(unsortedArray + index, unsortedArray + windowIndex);

		index = windowIndex;              // O (1)

		circularIncrementWindowIndex();        // O (1)
	}

	return index;
}

void Search::swap(int *firstElement, int *secondElement)
{
	int temporaryValue = *firstElement;
	*firstElement = *secondElement;
	*secondElement = temporaryValue;
}

void Search::swapByAddition(int *firstElement, int *secondElement)
{
	*firstElement += *secondElement;
	*secondElement = *firstElement - *secondElement;
	*firstElement -= *secondElement;
}

void Search::swapByXOR(int *firstElement, int *secondElement)
{
	*firstElement ^= *secondElement;
	*secondElement ^= *firstElement;
	*firstElement ^= *secondElement;
}

void Search::setRandomNumberSeed()
{
	srand(time(NULL));
}

int Search::generateRandomNumber(int minimum, int maximum)
{
    return (rand() % (maximum - minimum + 1)) + minimum;
}