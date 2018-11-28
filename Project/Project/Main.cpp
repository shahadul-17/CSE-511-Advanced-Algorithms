#include <conio.h>
#include <cstring>
#include <ctime>
#include <iostream>

#include "Search.h"		// our Search.h header file...

#define UNSORTED_ARRAY_LENGTH 10000
#define QUERIES_LENGTH UNSORTED_ARRAY_LENGTH / 2

using namespace std;

void bestCaseScenario(int *queries, int *unsortedArray)		// every single query is for the first index of the array...
{
	for (int i = 0; i < QUERIES_LENGTH; i++)
	{
		queries[i] = unsortedArray[0];
	}
}

void averageCaseScenario(int *queries, int *unsortedArray)
{
	for (int i = 0, j = 1; i < QUERIES_LENGTH; i++)
    {
        if (j == 51)
        {
            j = 1;
        }

		queries[i] = unsortedArray[UNSORTED_ARRAY_LENGTH - j]; // bringFrontSearch.generateRandomNumber(1, 10000);

        if (i % 2 == 0)
        {
            j++;
        }
    }
}

void worstCaseScenario(int *queries, int *unsortedArray)		// every single query is for the last index of the array...
{
	for (int i = 0; i < QUERIES_LENGTH; i++)
	{
		queries[i] = unsortedArray[UNSORTED_ARRAY_LENGTH - 1];
	}
}

int main(int argc, char **argv)
{
	int selection = 0, *queries = new int[QUERIES_LENGTH], *unsortedArray = new int[UNSORTED_ARRAY_LENGTH];
	
	clock_t time;

	Search search(UNSORTED_ARRAY_LENGTH, unsortedArray);

	cout << "status: generating random unsorted array." << endl;

	unsortedArray[UNSORTED_ARRAY_LENGTH - 1] = UNSORTED_ARRAY_LENGTH + QUERIES_LENGTH;

	for (int i = UNSORTED_ARRAY_LENGTH - 2; i > -1; i--)
    {
		unsortedArray[i] = Search::generateRandomNumber(1, UNSORTED_ARRAY_LENGTH);
    }

	cout << "status: random unsorted array generated successfully." << endl;
	cout << "prompt: please select a scenario\n\t[1] best case scenario\n\t[2] average case scenario\n\t[3] worst case scenario-\nselection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		bestCaseScenario(queries, unsortedArray);

		break;
	case 2:
		averageCaseScenario(queries, unsortedArray);

		break;
	case 3:
		worstCaseScenario(queries, unsortedArray);

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
	cout << "status: randomized bring front search running on random unsorted array." << endl;

	search.resetArray();		// restoring the unsorted array to initial state...

	time = clock();

	for (int i = 0; i < QUERIES_LENGTH; i++)
    {
		search.bringFrontSearch(true, queries[i]);
    }

    time = clock() - time;

	cout << "status: randomized bring front search finished in: " << (double)time / CLOCKS_PER_SEC << " seconds." << endl;

	delete [] queries;

	_getch();

	return 0;
}