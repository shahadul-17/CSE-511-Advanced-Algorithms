#include <stdio.h>
#include <string.h>         // for memcpy function...
#include <limits.h>         // for using INT_MAX...

int merge_and_count_inversions(int startIndex, int middleIndex, int endIndex, int arrayToSort[])
{
    int inversions = 0, lengths[] = {
        middleIndex - startIndex + 1,
        endIndex - middleIndex
    },
    leftSubArray[lengths[0] + 1],
    rightSubArray[lengths[1] + 1];

    leftSubArray[lengths[0]] = rightSubArray[lengths[1]] = INT_MAX;

    memcpy(leftSubArray, arrayToSort + startIndex, lengths[0] * sizeof(int));
    memcpy(rightSubArray, arrayToSort + middleIndex + 1, lengths[1] * sizeof(int));

    for (int i = startIndex, j = 0, k = 0; i <= endIndex; i++)
    {
        if (leftSubArray[j] <= rightSubArray[k])
        {
            arrayToSort[i] = leftSubArray[j];

            j++;
        }
        else
        {
            arrayToSort[i] = rightSubArray[k];
            inversions += lengths[0] - j;

            k++;
        }
    }

    return inversions;
}

int count_inversions(int startIndex, int endIndex, int arrayToSort[])
{
    if (startIndex < endIndex)
    {
        int inversions = 0, middleIndex = (startIndex + endIndex) / 2;

        inversions += count_inversions(startIndex, middleIndex, arrayToSort);
        inversions += count_inversions(middleIndex + 1, endIndex, arrayToSort);
        inversions += merge_and_count_inversions(startIndex, middleIndex, endIndex, arrayToSort);

        return inversions;
    }

    return 0;
}

int main()
{
    // sample input: length = 4, elements = 12 3 15 4
    int arrayLength;

    printf("Enter the length of array: ");
    scanf("%d", &arrayLength);

    if (arrayLength <= 0)
    {
        printf("error: invalid input for \'length of array\'.\n");

        return -1;
    }

    int arrayToSort[arrayLength];

    printf("Enter sorted array: ");

    for (int i = 0; i < arrayLength; i++)
    {
        scanf("%d", & arrayToSort[i]);
    }

    printf("\nNumber of inversions: %d\n", count_inversions(0, arrayLength - 1, arrayToSort));

    return 0;
}
