#include <stdio.h>

int customized_binary_search(int startIndex, int endIndex, int elementToSearch, int arrayToSearch[])
{
    static int leftMostIndex = -1;

    if (endIndex < startIndex)
    {
        return leftMostIndex;
    }

    int middleIndex = startIndex + (endIndex - startIndex) / 2;

    if (elementToSearch == arrayToSearch[middleIndex])
    {
        leftMostIndex = middleIndex;

        return customized_binary_search(startIndex, middleIndex - 1, elementToSearch, arrayToSearch);
    }
    else if (elementToSearch < arrayToSearch[middleIndex])
    {
        return customized_binary_search(startIndex, middleIndex - 1, elementToSearch, arrayToSearch);
    }
    else
    {
        return customized_binary_search(middleIndex + 1, endIndex, elementToSearch, arrayToSearch);
    }
}

int main()
{
    // sample input: arrayLength = 10, elements = 1 2 3 5 5 5 5 5 8 12
    int arrayLength;

    printf("Enter the length of array: ");
    scanf("%d", &arrayLength);

    if (arrayLength <= 0)
    {
        printf("error: invalid input for \'length of array\'.\n");

        return -1;
    }

    int elementToSearch = 0, arrayToSearch[arrayLength];

    printf("Enter sorted array: ");

    for (int i = 0; i < arrayLength; i++)
    {
        scanf("%d", & arrayToSearch[i]);
    }

    printf("\nElements:\t");

    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d\t", arrayToSearch[i]);
    }

    printf("\n           \t");

    for (int i = 0; i < arrayLength; i++)
    {
        printf("|\t");
    }

    printf("\nIndices :\t");

    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d\t", i);
    }

    printf("\n\nEnter target: ");
    scanf("%d", &elementToSearch);
    printf("\nLeftmost index of target \'%d\' is: %d\n", elementToSearch, customized_binary_search(0, arrayLength - 1, elementToSearch, arrayToSearch));

    return 0;
}
