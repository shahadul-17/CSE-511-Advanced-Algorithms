#include "DynamicArray.h"

template <class Type>
DynamicArray<Type>::DynamicArray(int allocationUnit)
{
	this->allocationUnit = allocationUnit;
	currentIndex = -1;
	arrayLength = 0;
	rootNode = nullptr;
	indices = nullptr;
}

template <class Type>
DynamicArray<Type>::~DynamicArray()
{
	dispose();
}

template <class Type>
int DynamicArray<Type>::length()
{
	return currentIndex + 1;
}

template <class Type>
void DynamicArray<Type>::insert(Type value)
{
	currentIndex++;

	if (currentIndex == arrayLength)
	{
		indices = allocate(allocationUnit, arrayLength, indices);
	}
	
	rootNode = insert(currentIndex, value, rootNode, indices);
}

template <class Type>
Type DynamicArray<Type>::get(int index)
{
	if (index > currentIndex)
	{
		throw -1;
	}

	return indices[index]->value;
}

template <class Type>
int DynamicArray<Type>::search(Type value)
{
	typename DynamicArray<Type>::Node *node = search(value, rootNode);

	if (node == nullptr)
	{
		return -1;
	}

	return node->index;
}

template <class Type>
void DynamicArray<Type>::dispose()
{
	dispose(rootNode);

	rootNode = nullptr;

	delete [] indices;
	
	indices = nullptr;
}

template <class Type>
typename DynamicArray<Type>::Node * DynamicArray<Type>::insert(int index, Type value,
															   typename DynamicArray<Type>::Node *node,
															   typename DynamicArray<Type>::Node **indices)
{
	if (node == nullptr)
	{
		node = new typename DynamicArray<Type>::Node;
		node->index = index;
		node->value = value;

		indices[node->index] = node;		// keeping the address of the node...

		return node;
	}

	if (value <= node->value)
	{
		node->leftNode = insert(index, value, node->leftNode, indices);
	}
	else
	{
		node->rightNode = insert(index, value, node->rightNode, indices);
	}

	return node;
}

template <class Type>
typename DynamicArray<Type>::Node * DynamicArray<Type>::search(Type value,
															   typename DynamicArray<Type>::Node *node)
{
	if (node == nullptr || value == node->value)
	{
		return node;
	}
	else if (value < node->value)
	{
		return search(value, node->leftNode);
	}
	else
	{
		return search(value, node->rightNode);
	}
}

template <class Type>
typename DynamicArray<Type>::Node ** DynamicArray<Type>::allocate(int allocationUnit, int arrayLength,
																  typename DynamicArray<Type>::Node **indices)
{
	int newlyAllocatedArrayLength = arrayLength + allocationUnit;

	typename DynamicArray<Type>::Node **newlyAllocatedIndices =
		new typename DynamicArray<Type>::Node*[newlyAllocatedArrayLength];

	if (indices != nullptr)
	{
		for (int i = 0; i < arrayLength; i++)
		{
			newlyAllocatedIndices[i] = indices[i];
		}

		delete [] indices;
	}

	arrayLength = newlyAllocatedArrayLength;

	return newlyAllocatedIndices;
}

template <class Type>
void DynamicArray<Type>::dispose(typename DynamicArray<Type>::Node *node)
{
	if (node == nullptr)
	{
		return;
	}
	
	dispose(node->leftNode);
	dispose(node->rightNode);

	delete node;

	node = nullptr;
}