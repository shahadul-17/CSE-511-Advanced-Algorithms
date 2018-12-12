// standard c++ header files...
#include <conio.h>
#include <sstream>

// user defined c++ header files...
#include "Search.h"		// our Search.h header file...

#define SCENARIOS 6
#define MAXIMUM_CHARACTERS 12
#define QUERIES_LENGTH_DIVISOR 100

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
	for (int i = 0; i < queriesLength; i++)
    {
		queries[i] = Search::generateRandomNumber(1, unsortedArrayLength);
    }
}

void randomIndicesScenario(int queriesLength, int unsortedArrayLength, int *queries, int *unsortedArray)		// generates random indices...
{
	for (int i = 0; i < queriesLength / QUERIES_LENGTH_DIVISOR; i++)
    {
		queries[i] = Search::generateRandomNumber(0, (queriesLength / 4) - 1);
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

void printResult(bool searchByIndex, double timeInSeconds)
{
	// printing how much one algorithm is faster or slower than another...
	if (timeInSeconds == 0.0)
	{
		cout << "note: 'DAS' completed in " << timeInSeconds << " seconds with no improvement over other algorithms." << endl;
	}
	else
	{
		string comparison;

		if (timeInSeconds < 0)
		{
			timeInSeconds *= -1.0;
			comparison = "faster";
		}
		else
		{
			comparison = "slower";
		}
		
		if (searchByIndex)
		{
			cout << "result: search by index on dynamic array is " << timeInSeconds << " seconds " << comparison << " than other tree based algorithms." << endl;
		}
		else
		{
			cout << "result: on average, dynamic array search is " << timeInSeconds / SCENARIOS << " seconds " << comparison << " than all other algorithms." << endl;
			cout << "result: dynamic array search is total " << timeInSeconds << " seconds " << comparison << " than all other algorithms." << endl;
		}
	}
}

int main(int argc, char **argv)
{
	int unsortedArrayLength = 0;
	
	if (argc > 1)
	{
		unsortedArrayLength = atoi(argv[1]);
	}

	while (unsortedArrayLength < 10000)
	{
		cout << "prompt: enter the length of the unsorted array (must be greater than 9,999).\nlength: ";
		cin >> unsortedArrayLength;
		cout << endl;
	}

	int queriesLength = unsortedArrayLength / 2, *queries = new int[queriesLength], *unsortedArray = new int[unsortedArrayLength];
	double timeInSeconds = 0.0, totalTimeInSeconds = 0.0;

	clock_t temporaryTimeTaken, minimumTimeTaken, timeTakenByDynamicArraySearch;
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
	cout << "note: for 'UMS', 'OMS' and 'DAS', we will additionally search " << queriesLength / QUERIES_LENGTH_DIVISOR << " indices." << endl;
	cout << "note: unit for time is represented in seconds (denoted by 's')." << endl << endl;

	cout << "note: 'ULS' -> unoptimized linear search." << endl << "note: 'OLS' -> optimized linear search." << endl;
	cout << "note: 'BFS' -> bring front search." << endl << "note: 'DAS' -> dynamic array search." << endl;
	cout << "note: 'OMS' -> ordered map search (using binary search tree)." << endl << "note: 'UMS' -> unordered map search (using hash map)." << endl << endl;

	cout << "note: 'delta' is the difference between time taken by 'DAS' and minimum time taken by any other algorithm." << endl;
	cout << "status: starting benchmark." << endl << "status: starting search by value." << endl << endl;
	cout << "[#]            scenario |     ULS     |     OLS     | **  BFS  ** |     UMS     |     OMS     | *** DAS *** |  [ delta ] " << endl;
	cout << "----------------------- + ----------- + ----------- + ----------- + ----------- + ----------- + ----------- + -----------" << endl;

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

		minimumTimeTaken = clock();			// clock starts for linear search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.unoptimizedLinearSearch(queries[j]);			// performing linear search...
		}

		minimumTimeTaken = clock() - minimumTimeTaken;			// clock stops for linear search...

		cout << getTimeInSecondsString((double)minimumTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by linear search...

		temporaryTimeTaken = clock();			// clock starts for bring front search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.optimizedLinearSearch(queries[j]);			// performing bring front search...
		}

		temporaryTimeTaken = clock() - temporaryTimeTaken;			// clock stops for bring front search...

		cout << getTimeInSecondsString((double)temporaryTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

		if (temporaryTimeTaken < minimumTimeTaken)
		{
			minimumTimeTaken = temporaryTimeTaken;
		}

		temporaryTimeTaken = clock();			// clock starts for bring front search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.bringFrontSearch(queries[j]);			// performing bring front search...
		}

		temporaryTimeTaken = clock() - temporaryTimeTaken;			// clock stops for bring front search...

		cout << getTimeInSecondsString((double)temporaryTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

		if (temporaryTimeTaken < minimumTimeTaken)
		{
			minimumTimeTaken = temporaryTimeTaken;
		}

		temporaryTimeTaken = clock();			// clock starts for bring front search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.unorderedMapSearch(queries[j]);			// performing bring front search...
		}

		temporaryTimeTaken = clock() - temporaryTimeTaken;			// clock stops for bring front search...

		cout << getTimeInSecondsString((double)temporaryTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

		if (temporaryTimeTaken < minimumTimeTaken)
		{
			minimumTimeTaken = temporaryTimeTaken;
		}

		temporaryTimeTaken = clock();			// clock starts for bring front search...

		for (int j = 0; j < queriesLength; j++)
		{
			search.orderedMapSearch(queries[j]);			// performing bring front search...
		}

		temporaryTimeTaken = clock() - temporaryTimeTaken;			// clock stops for bring front search...

		cout << getTimeInSecondsString((double)temporaryTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

		if (temporaryTimeTaken < minimumTimeTaken)
		{
			minimumTimeTaken = temporaryTimeTaken;
		}

		timeTakenByDynamicArraySearch = clock();

		for (int j = 0; j < queriesLength; j++)
		{
			search.dynamicArraySearch(queries[j]);			// performing dynamic array search...
		}

		timeTakenByDynamicArraySearch = clock() - timeTakenByDynamicArraySearch;

		cout << getTimeInSecondsString((double)timeTakenByDynamicArraySearch / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by dynamic array search...

		clearStringStream(&stringStream);		// clearing the stringstream buffer...

		timeInSeconds = (double)(timeTakenByDynamicArraySearch - minimumTimeTaken) / CLOCKS_PER_SEC;		// calculates time difference between dynamic array search and any other algorithm that takes less time...
		totalTimeInSeconds += timeInSeconds;		// adding the current time difference to total time difference...

		if (timeInSeconds > 0.0)		// checks if current time difference in greater than zero...
		{
			stringStream << '+';		// if greater than zero, we are adding a '+' sign before the value...
		}

		stringStream << timeInSeconds << " s";
		cout << stringStream.str() << endl;

		search.reset();			// resets the unsorted array to its initial state...
	}

	cout << endl;

	printResult(false, totalTimeInSeconds);
	randomIndicesScenario(queriesLength, unsortedArrayLength, queries, unsortedArray);					// generates random indices...

	cout << endl << "status: starting search by indices." << endl << endl;
	cout << "[#]            scenario |     UMS     |     OMS     | *** DAS *** |  [ delta ] " << endl;
	cout << "----------------------- + ----------- + ----------- + ----------- + -----------" << endl;
	cout << "[7]      random indices | ";

	minimumTimeTaken = clock();			// clock starts for bring front search...

	for (int j = 0; j < queriesLength / QUERIES_LENGTH_DIVISOR; j++)
	{
		search.unorderedMapSearchByIndex(queries[j]);			// performing bring front search...
	}

	minimumTimeTaken = clock() - minimumTimeTaken;			// clock stops for bring front search...

	cout << getTimeInSecondsString((double)minimumTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

	temporaryTimeTaken = clock();			// clock starts for bring front search...

	for (int j = 0; j < queriesLength / QUERIES_LENGTH_DIVISOR; j++)
	{
		search.orderedMapSearchByIndex(queries[j]);			// performing bring front search...
	}

	temporaryTimeTaken = clock() - temporaryTimeTaken;			// clock stops for bring front search...

	cout << getTimeInSecondsString((double)temporaryTimeTaken / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

	if (temporaryTimeTaken < minimumTimeTaken)
	{
		minimumTimeTaken = temporaryTimeTaken;
	}

	timeTakenByDynamicArraySearch = clock();

	for (int j = 0; j < queriesLength / QUERIES_LENGTH_DIVISOR; j++)
	{
		search.dynamicArraySearchByIndex(queries[j]);			// performing bring front search...
	}

	timeTakenByDynamicArraySearch = clock() - timeTakenByDynamicArraySearch;			// clock stops for bring front search...

	cout << getTimeInSecondsString((double)timeTakenByDynamicArraySearch / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by bring front search...

	clearStringStream(&stringStream);		// clearing the stringstream buffer...

	timeInSeconds = (double)(timeTakenByDynamicArraySearch - minimumTimeTaken) / CLOCKS_PER_SEC;		// calculates time difference between dynamic array search and any other algorithm that takes less time...

	if (timeInSeconds > 0.0)		// checks if current time difference in greater than zero...
	{
		stringStream << '+';		// if greater than zero, we are adding a '+' sign before the value...
	}

	stringStream << timeInSeconds << " s";
	cout << stringStream.str() << endl << endl;

	printResult(true, timeInSeconds);

	delete [] queries;			// releasing the resource occupied by the dynamically allocated 'queries' array...
	delete [] unsortedArray;	// releasing the resource occupied by the dynamically allocated unsorted array...

	cout << endl << "status: benchmarking completed." << endl;

	_getch();

	return 0;
}