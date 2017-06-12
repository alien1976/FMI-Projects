#pragma once
typedef unsigned char Byte;
template<class T>
class HashTable {
public:
	HashTable();
	HashTable(const HashTable&rhs);
	HashTable &operator=(const HashTable&rhs);
	~HashTable();
public:
	void makeTable(size_t size);
	void hashFunc(T&item,Byte c);
	T& getCode(Byte item);
private:
	size_t size;
	T *arr;
};

template<class T>
inline HashTable<T>::HashTable()
{
	size = 0;
	arr = NULL;
}

template<class T>
inline HashTable<T>::HashTable(const HashTable & rhs)
{
	size = rhs.size;
	arr = new T[size];
	for (size_t i = ; i < size; i++)
		arr[i] = rhs.arr[i];
}

template<class T>
inline HashTable<T> & HashTable<T>::operator=(const HashTable & rhs)
{
	if (this = &rhs)return *this;
	size = rhs.size;
	delete[]arr;
	arr = new T[size];
	for (size_t i = ; i < size; i++)
		arr[i] = rhs.arr[i];
	return *this;
}

template<class T>
inline HashTable<T>::~HashTable()
{
	delete[] arr;
	arr = NULL;
}

template<class T>
inline void HashTable<T>::makeTable(size_t size)
{
	this->size = size;
	arr = new T[size];
}

template<class T>
inline void HashTable<T>::hashFunc( T & item,Byte c)
{
	arr[c%size] = item;
}

template<class T>
inline T & HashTable<T>::getCode(Byte item)
{
	return arr[item%size];
}
