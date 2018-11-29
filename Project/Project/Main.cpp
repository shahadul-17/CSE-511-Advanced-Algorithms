#include <conio.h>
#include <cstring>
#include <ctime>
#include <iostream>

#include "Search.h"		// our Search.h header file...

#define UNSORTED_ARRAY_LENGTH 100000
#define QUERIES_LENGTH UNSORTED_ARRAY_LENGTH / 2

using namespace std;

void bestCaseScenario(int *queries, int *unsortedArray)		// every single query is for the first index of the array...
{
	for (int i = 0; i < QUERIES_LENGTH; i++)
	{
		queries[i] = unsortedArray[0];
	}
}

void firstAverageCaseScenario(int *queries, int *unsortedArray)		// queries are repeated every 100 times...
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

void randomScenario(int *queries, int *unsortedArray)
{
	for (int i = 0, j = 1; i < QUERIES_LENGTH; i++)
    {
		queries[i] = Search::generateRandomNumber(1, UNSORTED_ARRAY_LENGTH);
    }
}

int main(int argc, char **argv)
{
	int selection = 0, *queries = new int[QUERIES_LENGTH], *unsortedArray = new int[UNSORTED_ARRAY_LENGTH];
	
	clock_t time;

	Search search(UNSORTED_ARRAY_LENGTH, unsortedArray);

	cout << "status: generating random unsorted array." << endl;

	unsortedArray[UNSORTED_ARRAY_LENGTH - 1] = UNSORTED_ARRAY_LENGTH + QUERIES_LENGTH;		// last element of the array is distinct...
	unsortedArray[UNSORTED_ARRAY_LENGTH - 2] = unsortedArray[UNSORTED_ARRAY_LENGTH - 1] + 1;		// second last element of the array is distinct...

	for (int i = UNSORTED_ARRAY_LENGTH - 3; i > -1; i--)
    {
		unsortedArray[i] = Search::generateRandomNumber(1, UNSORTED_ARRAY_LENGTH);
    }

	cout << "status: random unsorted array generated successfully." << endl << endl;
	cout << "prompt: please select a scenario-\n\t[1] best case scenario\n\t[2] first average case scenario"
		<< "\n\t[3] second average case scenario\n\t[4] first worst case scenario"
		<< "\n\t[5] second worst case scenario\n\t[6] random scenario\nselection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		bestCaseScenario(queries, unsortedArray);

		break;
	case 2:
		firstAverageCaseScenario(queries, unsortedArray);

		break;
	case 3:
		secondAverageCaseScenario(queries, unsortedArray);

		break;
	case 4:
		firstWorstCaseScenario(queries, unsortedArray);

		break;
	case 5:
		secondWorstCaseScenario(queries, unsortedArray);		// none of the queries exist in array...

		break;
	case 6:
		randomScenario(queries, unsortedArray);

		break;
	default:
		cout << "error: query generation failed due to invalid input." << endl;

		_getch();

		return -1;
	}

	cout << endl;
	cout << "status: generating queries." << endl;
	cout << "status: queries generated successfully." << endl << endl;
	cout << "status: linearly searching through random unsorted array." << endl;

	time = clock();

	for (int i = 0; i < QUERIES_LENGTH; i++)
    {
		search.linearSearch(queries[i]);
    }

    time = clock() - time;

	cout << "status: linear search finished in: " << (double)time / CLOCKS_PER_SEC << " seconds." << endl << endl;
	cout << "status: bring front search running on random unsorted array." << endl;

	time = clock();

	for (int i = 0; i < QUERIES_LENGTH; i++)
    {
		search.bringFrontSearch(false, queries[i]);
    }

    time = clock() - time;

	cout << "status: bring front search finished in: " << (double)time / CLOCKS_PER_SEC << " seconds." << endl << endl;

	delete [] queries;

	cout << "status: completed" << endl;

	_getch();

	return 0;
}