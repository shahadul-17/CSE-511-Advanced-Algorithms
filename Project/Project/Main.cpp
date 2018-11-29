// standard c++ header files...
#include <conio.h>
#include <sstream>

// user defined c++ header files...
#include "Search.h"		// our Search.h header file...

#define SCENARIOS 6
#define MAXIMUM_CHARACTERS 19
#define UNSORTED_ARRAY_LENGTH 100000
#define QUERIES_LENGTH UNSORTED_ARRAY_LENGTH / 2

void bestCaseScenario(int *queries, int *unsortedArray)		// every single query is for the first index of the array...
{
	for (int i = 0; i < QUERIES_LENGTH; i++)
	{
		queries[i] = unsortedArray[0];
	}
}

void firstAverageCaseScenario(int *queries, int *unsortedArray)		// same queries are repeated every 100 iterations...
{
	for (int i = 0, j = 1; i < QUERIES_LENGTH; i++, j++)
    {
		queries[i] = unsortedArray[UNSORTED_ARRAY_LENGTH - j];

		if (j == UNSORTED_ARRAY_LENGTH / 100)
		{
			j = 1;
		}
    }
}

void secondAverageCaseScenario(int *queries, int *unsortedArray)		// queries start from the last element of the array...
{
	for (int i = 0, j = 1; i < QUERIES_LENGTH; i++)
    {
		queries[i] = unsortedArray[UNSORTED_ARRAY_LENGTH - j];
    }
}

void firstWorstCaseScenario(int *queries, int *unsortedArray)		// every single query is for the second last index of the array...
{
	for (int i = 0; i < QUERIES_LENGTH; i++)
	{
		queries[i] = unsortedArray[UNSORTED_ARRAY_LENGTH - 2];
	}
}

void secondWorstCaseScenario(int *queries, int *unsortedArray)		// none of the queries exists in the array...
{
	for (int i = 0; i < QUERIES_LENGTH; i++)
	{
		queries[i] = unsortedArray[UNSORTED_ARRAY_LENGTH - 2] + 1;
	}
}

void randomScenario(int *queries, int *unsortedArray)		// generates random queries...
{
	for (int i = 0, j = 1; i < QUERIES_LENGTH; i++)
    {
		queries[i] = Search::generateRandomNumber(1, UNSORTED_ARRAY_LENGTH);
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
	unsigned short characters = 0;
	int scenario = 0, *queries = new int[QUERIES_LENGTH], *unsortedArray = new int[UNSORTED_ARRAY_LENGTH];
	double timeInSeconds = 0.0, totalTimeInSeconds = 0.0;

	clock_t timeTakenByLinearSearch, timeTakenByBringFrontSearch;
	string scenarios[] =
	{
		"           best case", "  first average case",
		" second average case", "    first worst case",
		"   second worst case", "              random"
	};
	stringstream stringStream;

	cout << "status: generating random unsorted array of length " << UNSORTED_ARRAY_LENGTH << "." << endl;

	unsortedArray[UNSORTED_ARRAY_LENGTH - 1] = UNSORTED_ARRAY_LENGTH + QUERIES_LENGTH;		// last element of the array is distinct...
	unsortedArray[UNSORTED_ARRAY_LENGTH - 2] = unsortedArray[UNSORTED_ARRAY_LENGTH - 1] + 1;		// second last element of the array is distinct...

	Search::setRandomNumberSeed();		// sets seed for generating random numbers...

	for (int i = UNSORTED_ARRAY_LENGTH - 3; i > -1; i--)
    {
		unsortedArray[i] = Search::generateRandomNumber(1, UNSORTED_ARRAY_LENGTH);
    }

	cout << "status: random unsorted array generated successfully." << endl;
	cout << "note: we will run " << QUERIES_LENGTH << " queries for each algorithm per scenario." << endl;
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
			bestCaseScenario(queries, unsortedArray);				// every single query is for the first index of the array...

			break;
		case 2:
			firstAverageCaseScenario(queries, unsortedArray);		// same queries are repeated every 100 iterations...

			break;
		case 3:
			secondAverageCaseScenario(queries, unsortedArray);		// queries start from the last element of the array...

			break;
		case 4:
			firstWorstCaseScenario(queries, unsortedArray);			// every single query is for the second last index of the array...

			break;
		case 5:
			secondWorstCaseScenario(queries, unsortedArray);		// none of the queries exist in array...

			break;
		case 6:
			randomScenario(queries, unsortedArray);					// generates random queries...

			break;
		default:
			break;
		}

		Search search(UNSORTED_ARRAY_LENGTH, unsortedArray);		// creating new instance...

		timeTakenByLinearSearch = clock();			// clock starts for linear search...

		for (int j = 0; j < QUERIES_LENGTH; j++)
		{
			search.linearSearch(queries[j]);			// performing linear search...
		}

		timeTakenByLinearSearch = clock() - timeTakenByLinearSearch;			// clock stops for linear search...

		cout << getTimeInSecondsString((double)timeTakenByLinearSearch / CLOCKS_PER_SEC, &stringStream) << "| ";	// prints time taken by linear search...

		timeTakenByBringFrontSearch = clock();			// clock starts for bring front search...

		for (int j = 0; j < QUERIES_LENGTH; j++)
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