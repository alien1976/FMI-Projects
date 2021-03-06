#pragma once
#ifndef _DYNAMIC_ARR_INCLUDED_
#define _DYNAMIC_ARR_INCLUDED_
#include <iostream>
template <class Type>
class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(const DynamicArray &rhs);
	DynamicArray & operator=(const DynamicArray &rhs);
	~DynamicArray();
	DynamicArray &operator+=(const Type &item);
	DynamicArray &operator--();
	const Type &operator[](size_t index)const;
	Type &operator[](size_t index);
	void AddItem(const Type &item);
	void DeleteLast();
	void Print();
	Type& getData(int index)const { return arr[index]; }
	size_t getSize()const { return Size; }
	size_t getCapacity()const { return Capacity; }

private:
	void resize(size_t newsize);
	void checksize(size_t size);
	Type *arr;
	size_t Size;
	size_t Capacity;
};
template<class Type>
std::ostream &operator<<(std::ostream &out, const DynamicArray<Type> &rhs)
{
		out << rhs;
	return out;
}
template<class Type>
inline DynamicArray<Type>::DynamicArray()
{
	arr = NULL;
	Size = 0;
	Capacity = 2;
}
template<class Type>
inline DynamicArray<Type>::DynamicArray(const DynamicArray & rhs)
{
	Size = rhs.Size;
	Capacity = rhs.Capacity;
	arr = new Type[Capacity];
	for (size_t i = 0; i < Size; i++)
	{
		arr[i] = rhs.arr[i];
	}
}
template<class Type>
inline DynamicArray<Type> & DynamicArray<Type>::operator=(const DynamicArray & rhs)
{
	if (this != &rhs)
	{
		delete[]arr;
		Size = rhs.Size;
		Capacity = rhs.Capacity;
		arr = new Type[Capacity];
		for (size_t i = 0; i < Size; i++)
		{
			arr[i] = rhs.arr[i];
		}
	}
	return *this;
}
template<class Type>
inline DynamicArray<Type>::~DynamicArray()
{
	delete[] arr;
	arr = NULL;
	Size = 0;
	Capacity = 0;
}
template<class Type>
inline DynamicArray<Type> & DynamicArray<Type>::operator+=(const Type & item)
{
	AddItem(item);
	return *this;
}
template<class Type>
inline DynamicArray<Type> &DynamicArray<Type>::operator--()
{
	DeleteLast();
	return *this;
}
template<class Type>
inline const Type & DynamicArray<Type>::operator[](size_t index) const
{
	if(index>=Size)throw std::invalid_argument("Illegal index");
	return arr[index];
}
template<class Type>
inline Type & DynamicArray<Type>::operator[](size_t index)
{
	if (index >= Size)throw std::invalid_argument("Illegal index");
	return arr[index];
}
template<class Type>
inline void DynamicArray<Type>::AddItem(const Type &item)
{
	checksize(Size + 1);
	arr[Size++] = item;
}
template<class Type>
inline void DynamicArray<Type>::DeleteLast()
{
	if (Size > 0) {
		Size--;
		checksize(Size);
	}
	else std::cout << "Array is emty!\n";
}
template<class Type>
inline void DynamicArray<Type>::Print()
{
	std::cout << "Capacity is: " << Capacity<< " Size is: " << Size << std::endl<<"Array is: ";
	for (size_t i = 0; i < Size; i++)
		std::cout << arr[i]<<" ";
	std::cout << std::endl<<std::endl;
}
template<class Type>
inline void DynamicArray<Type>::checksize(size_t size)
{
	if (size >= Capacity)
	{
		while (Capacity < size)
		{
			if (size >= Capacity)
			{
				Capacity *= 2;
			}
		}
		resize(Capacity);
	}
	else
	{
		size_t copyCapacity = Capacity;
		while (true)
		{
			if (Capacity == 2) break;
			else if (size <= copyCapacity/2)
			{
				copyCapacity /= 2;
			}
			else if (size > copyCapacity/2)break;
		}
		if (Capacity == 2)resize(Capacity);
		else if(copyCapacity!=Capacity)
				resize(copyCapacity);
	}
}
template<class Type>
inline void DynamicArray<Type>::resize(size_t newsize)
{
	Type *temp = new Type[newsize];
	for (size_t i = 0; i < Size; i++)
		temp[i] = arr[i];
	delete[]arr;
	arr = temp;
	Capacity = newsize;
}
#endif