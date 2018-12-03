// standard c++ header files...
#include <conio.h>
#include <sstream>

// user defined c++ header files...
#include "Search.h"		// our Search.h header file...

#define SCENARIOS 6
#define MAXIMUM_CHARACTERS 19

using namespace std;

void bestCaseScenario(int queriesLength, int *queries, int *unsortedArray)		// every single query is for the first index of the array...
{
	for (int i = 0; i < queriesLength; i++)
	{
		queries[i] = unsortedArray[0];
	}
}

void firstAverageCaseScenario(int queriesLength, int unsortedArrayLength, int *queries, int *unsortedArray)		// same queries are repeated every 100 iterations...
{
	for (int i = 0, j = 1; i < queriesLength; i++, j++)
    {
		queries[i] = unsortedArray[unsortedArrayLength - j];

		if (j == unsortedArrayLength / 100)
		{
			j = 1;
		}
    }
}

void secondAverageCaseScenario(int queriesLength, int unsortedArrayLength, int *queries, int *unsortedArray)		// queries start from the last element of the array...
{
	for (int i = 0; i < queriesLength; i++)
    {
		queries[i] = unsortedArray[unsortedArrayLength - i - 1];
    }
}

void firstWorstCaseScenario(int queriesLength, int unsortedArrayLength, int *queries, int *unsortedArray)		// every single query is for the second last index of the array...
{
	for (int i = 0; i < queriesLength; i++)
	{
		queries[i] = unsortedArray[unsortedArrayLength - 2];
	}
}

void secondWorstCaseScenario(int queriesLength, int unsortedArrayLength, int *queries, int *unsortedArray)		// none of the queries exists in the array...
{
	for (int i = 0; i < queriesLength; i++)
	{
		queries[i] = unsortedArray[unsortedArrayLength - 2] + 1;
	}
}

void randomScenario(int queriesLength, int unsortedArrayLength, int *queries, int *unsortedArray)		// generates random queries...
{
	for (int i = 0, j = 1; i < queriesLength; i++)
    {
		queries[i] = Search::generateRandomNumber(1, unsortedArrayLength);
    }
}

void clearStringStream(stringstream *stringStream)		// clears the stringstream buffer...
{
	stringStream->clear();
	stringStream->str(string());
}

string getTimeInSecondsString(double timeInSeconds, stringstream *stringStream)			// converts the time to string and adds necessary padding...
{
	clearStringStream(stringStream);		// we need to clear the string stream everytime to re-use...

	*stringStream << timeInSeconds << " s";

	for (int i = stringStream->str().size(); i < MAXIMUM_CHARACTERS; i++)
	{
		*stringStream << " ";		// appending space...
	}

	return stringStream->str();
}

int main(int argc, char **argv)
{
	int unsortedArrayLength = 0;

	if (argc > 1)
	{
		unsortedArrayLength = atoi(argv[1]);
	}

	while (unsortedArrayLength < 100)
	{
		cout << "prompt: enter the length of the unsorted array (must be greater than 9,999).\nlength: ";
		cin >> unsortedArrayLength;
		cout << endl;
	}

	int queriesLength = unsortedArrayLength / 2, *queries = new int[queriesLength], *unsortedArray = new int[unsortedArrayLength];
	double timeInSeconds = 0.0, totalTimeInSeconds = 0.0;

	clock_t timeTakenByLinearSearch, timeTakenByBringFrontSearch;
	string scenarios[] =
	{
		"           best case", "  first average case",
		" second average case", "    first worst case",
		"   second worst case", "              random"
	};
	stringstream stringStream;

	cout << "status: generating random unsorted array of length " << unsortedArrayLength << "." << endl;

	unsortedArray[unsortedArrayLength - 1] = unsortedArrayLength + queriesLength;		// last element of the array is distinct...
	unsortedArray[unsortedArrayLength - 2] = unsortedArray[unsortedArrayLength - 1] + 1;		// second last element of the array is distinct...

	Search::setRandomNumberSeed();		// sets seed for generating random numbers...

	for (int i = unsortedArrayLength - 3; i > -1; i--)
    {
		unsortedArray[i] = Search::generateRandomNumber(1, unsortedArrayLength);
    }

	Search search(unsortedArrayLength, unsortedArray);		// creating instance of Search...

	cout << "status: random unsorted array generated successfully." << endl;
	cout << "note: we will run " << queriesLength << " queries for each algorithm per scenario." << endl;
	cout << "note: unit for time is represented in seconds (denoted by 's')." << endl;
	cout << "status: starting benchmark." << endl << endl;
	cout << "[#]            scenario | linear search      | bring front search | difference" << endl;
	cout << "----------------------- + ------------------ + ------------------ + ------------------" << endl;

	for (int i = 1; i <= SCENARIOS; i++)
	{
		cout << "[" << i << "]" << scenarios[i - 1] << " | ";

		switch (i)
		{
		case 1:
			bestCaseScenario(queriesLength, queries, unsortedArray);				// every single query is for the first index of the array...

			break;
		case 2:
			firstAverageCaseScenario(queriesLength, unsortedArrayLength, queries, unsortedArray);		// same queries are repeated every 100 iterations...

			break;
		case 3:
			secondAverageCaseScenario(queriesLength, unsortedArrayLength, queries, unsortedArray);		// queries start from the last element of the array...

			break;
		case 4:
			firstWorstCaseScenario(queriesLength, unsortedArrayLength, queries, unsortedArray);			// every single query is for the second last index of the array...

			break;
		case 5:
			secondWorstCaseScenario(queriesLength, unsortedArrayLength, queries, unsortedArray);		// none of the queries exist in array...

			break;
		case 6:
			randomScenario(queriesLength, unsortedArrayLength, queries, unsortedArray);					// generates random queries...

			break;
		default:
			break;
		}

		timeTakenByLinearSearch = clock();			// clock starts for linear search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.linearSearch(queries[j]);			// performing linear search...
		}

		timeTakenByLinearSearch = clock() - timeTakenByLinearSearch;			// clock stops for linear search...

		cout << getTimeInSecondsString((double)timeTakenByLinearSearch / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by linear search...

		timeTakenByBringFrontSearch = clock();			// clock starts for bring front search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.bringFrontSearch(false, queries[j]);			// performing bring front search...
		}

		timeTakenByBringFrontSearch = clock() - timeTakenByBringFrontSearch;			// clock stops for bring front search...

		cout << getTimeInSecondsString((double)timeTakenByBringFrontSearch / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

		clearStringStream(&stringStream);		// clearing the stringstream buffer...

		timeInSeconds = (double)(timeTakenByBringFrontSearch - timeTakenByLinearSearch) / CLOCKS_PER_SEC;		// calculates time difference between linear and bring front search...
		totalTimeInSeconds += timeInSeconds;		// adding the current time difference to total time difference...

		if (timeInSeconds > 0.0)		// checks if current time difference in greater than zero...
		{
			stringStream << '+';		// if greater than zero, we are adding a '+' sign before the value...
		}

		stringStream << timeInSeconds << " s";
		cout << stringStream.str() << endl;

		search.reset();			// resets the unsorted array to its initial state...
	}

	delete [] queries;			// releasing the resource occupied by the dynamically allocated 'queries' array...
	delete [] unsortedArray;	// releasing the resource occupied by the dynamically allocated unsorted array...

	cout << endl;

	// printing how much one algorithm is faster or slower than another...
	if (totalTimeInSeconds == 0.0)
	{
		cout << "note: both linear search and bring front search completed in " << totalTimeInSeconds << " seconds." << endl;
	}
	else
	{
		string comparison;

		if (totalTimeInSeconds < 0)
		{
			totalTimeInSeconds *= -1.0;
			comparison = "faster";
		}
		else
		{
			comparison = "slower";
		}
		
		cout << "result: on average, bring front search is " << totalTimeInSeconds / SCENARIOS << " seconds " << comparison << " than linear search." << endl;
		cout << "result: bring front search is total " << totalTimeInSeconds << " seconds " << comparison << " than linear search." << endl;
	}

	cout << "status: benchmarking completed." << endl;

	_getch();

	return 0;
}