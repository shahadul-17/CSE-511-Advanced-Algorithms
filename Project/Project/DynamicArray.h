#pragma once

template <class Type>
class DynamicArray
{
public:
	DynamicArray(int);
	~DynamicArray();

	int length();
	void insert(Type);
	Type get(int);
	int search(Type);
	void dispose();

private:
	struct Node
	{
		int index;		// index of the node...
		
		Type value;		// value of the node...

		struct Node *leftNode, *rightNode;

		Node()		// constructor...
		{
			leftNode = rightNode = nullptr;
		}
	};

	int currentIndex, allocationUnit, arrayLength;

	typename DynamicArray<Type>::Node *rootNode, **indices;

	static typename DynamicArray<Type>::Node * insert(int, Type, typename DynamicArray<Type>::Node *, typename DynamicArray<Type>::Node **);
	static typename DynamicArray<Type>::Node * search(Type, typename DynamicArray<Type>::Node *);
	static typename DynamicArray<Type>::Node ** allocate(int, int, typename DynamicArray<Type>::Node **);
	static void dispose(typename DynamicArray<Type>::Node *);
};