#include "Search.h"

Search::Search(int arrayLength, int *unsortedArray)
{
	initialUnsortedArray = NULL;

	setArray(arrayLength, unsortedArray);
    srand(time(NULL));
}

Search::~Search()
{
	delete [] unsortedArray;
	delete [] initialUnsortedArray;
}

void Search::setArray(int arrayLength, int *unsortedArray)
{
    windowIndex = 0;
    windowLength = arrayLength / 4;		// window length should be quarter of the array length...

	this->arrayLength = arrayLength;
    this->unsortedArray = unsortedArray;

	if (initialUnsortedArray != NULL)
	{
		delete [] initialUnsortedArray;
	}

	initialUnsortedArray = new int[arrayLength];

	memcpy(initialUnsortedArray, unsortedArray, arrayLength * sizeof(int));		// keeping a copy of unsorted array...
}

void Search::resetArray()
{
	windowIndex = 0;

	memcpy(unsortedArray, initialUnsortedArray, arrayLength * sizeof(int));		// copying original array...
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
				if (i > windowLength)           // O (1)
				{
					/*
					* if one element with same value as query already exists within the window...
					* we should increment index of window by 1...
					*/
					if (query == unsortedArray[windowIndex])       // O (1)
					{
						circularIncrementWindowIndex();       // O (1)
					}

					// can be replaced by any kind of swap...
					swapByXOR(unsortedArray + i, unsortedArray + windowIndex);

					i = windowIndex;              // O (1)

					circularIncrementWindowIndex();        // O (1)
				}

				return i;
			}

			return -1;
		}
	}
}

int Search::randomizedBringFrontSearch(int query)		// this performs worst...
{
	if (query == unsortedArray[windowLength])
	{
		return windowLength;
	}

	int i = 0, temporaryValue = unsortedArray[windowLength];
	unsortedArray[windowLength] = query;

	for ( ; ; i++)
	{
		if (query == unsortedArray[i])
		{
			unsortedArray[windowLength] = temporaryValue;

			if (i < windowLength)
			{
				return i;
			}

			break;
		}
	}

	int randomIndex = -1;
	const int lastIndex = arrayLength - 1;

	if (query == unsortedArray[lastIndex])
	{
		return lastIndex;
	}
	
	temporaryValue = unsortedArray[lastIndex];
	unsortedArray[lastIndex] = query;

	for ( ; ; i++)
	{
		randomIndex = generateRandomNumber(i, lastIndex);

		if (query == unsortedArray[randomIndex])
		{
			unsortedArray[lastIndex] = temporaryValue;

			if (randomIndex < lastIndex)
			{
				if (randomIndex > windowLength)           // O (1)
				{
					/*
					* if one element with same value as query already exists within the window...
					* we should increment index of window by 1...
					*/
					if (query == unsortedArray[windowIndex])       // O (1)
					{
						circularIncrementWindowIndex();       // O (1)
					}

					// can be replaced by any kind of swap...
					swapByXOR(unsortedArray + randomIndex, unsortedArray + windowIndex);

					randomIndex = windowIndex;              // O (1)

					circularIncrementWindowIndex();        // O (1)
				}

				return randomIndex;
			}

			return -1;
		}
		else
        {
            swapByXOR(unsortedArray + i, unsortedArray + randomIndex);
        }
	}
}

int Search::bringFrontSearch(bool randomized, int query)
{
	if (randomized)
	{
		return randomizedBringFrontSearch(query);
	}
	else
	{
		return bringFrontSearch(query);
	}
}

void Search::print()
{
    for (int i = 0; i < arrayLength; i++)
    {
        cout << unsortedArray[i] << ", ";
    }

    cout << endl << endl;
}

void Search::swap(int *firstElement, int *secondElement)
{
	if (*firstElement == *secondElement)
	{
		return;
	}

	int temporaryValue = *firstElement;
	*firstElement = *secondElement;
	*secondElement = temporaryValue;
}

void Search::swapByAddition(int *firstElement, int *secondElement)
{
	if (*firstElement == *secondElement)
	{
		return;
	}

	*firstElement += *secondElement;
	*secondElement = *firstElement - *secondElement;
	*firstElement -= *secondElement;
}

void Search::swapByXOR(int *firstElement, int *secondElement)
{
	if (*firstElement == *secondElement)
	{
		return;
	}

	*firstElement ^= *secondElement;
	*secondElement ^= *firstElement;
	*firstElement ^= *secondElement;
}

int Search::generateRandomNumber(int minimum, int maximum)
{
    return (rand() % (maximum - minimum + 1)) + minimum;
}