#pragma once
#include<iostream>
template <class T>
class Queue {
public:
	Queue();
	Queue(const Queue<T>& rhs);
	Queue& operator=(const Queue<T>& rhs);
	~Queue();
private:
	struct Box
	{
		T data;
		Box *pNext;
	};
	void copy(const Queue<T> &rhs);
	void clean();
public:
	T& Front()const;
	T& Back()const;
	void enqueue(const T& element);
	void dequeue();
	bool isEmpty()const;
	size_t getSize()const { return size; }
private:
	size_t size;
	Box *pHead;
	Box *pTail;
};

template<class T>
inline Queue<T>::Queue()
{
	pHead = NULL;
	pTail = NULL;
	size = 0;
}

template<class T>
inline Queue<T>::Queue(const Queue<T> & rhs)
{
	copy(rhs);
}

template<class T>
inline Queue<T> & Queue<T>::operator=(const Queue<T> & rhs)
{
	if (this != *rhs)
	{
		clean();
		copy(rhs);
	}
	return *this;
}

template<class T>
inline Queue<T>::~Queue()
{
	clean();
}

template<class T>
inline void Queue<T>::copy(const Queue<T> & rhs)
{
	if (rhs.isEmpty())
		return;
	try {
		pHead = new Box;
		pHead->pNext = NULL;
		pHead->data = rhs.pHead->data;
		Box *pCurRhs = rhs.pHead;
		Box *pCurThis = pHead;
		while (pCurRhs->pNext != NULL)
		{
			pCurRhs = pCurRhs->pNext;
			pCurThis->pNext = new Box;
			pCurThis = pCurThis->pNext;
			pCurThis->data = pCurRhs->data;
			pCurThis->pNext = NULL;
		}
		pTail = pCurThis;
		size = rhs.size;
	}
	catch (std::bad_alloc&)
	{
		clean();
		throw;
	}
}

template<class T>
inline void Queue<T>::clean()
{
	Box *temp;
	while (pHead != NULL)
	{
		temp = pHead;
		pHead = pHead->pNext;
		delete temp;
	}
	pHead = NULL;
	pTail = NULL;
	size = 0;
}

template<class T>
inline T & Queue<T>::Front()const
{
	if (isEmpty())
	{
		throw "The queue is empty!";
	}
	return pHead->data;
}

template<class T>
inline T & Queue<T>::Back()const
{
	if (isEmpty())
	{
		throw "The queue is empty!";
	}
	return pTail->data;
}

template<class T>
inline void Queue<T>::enqueue(const T& element)
{
	if (isEmpty())
	{
		pHead = new Box;
		pTail = pHead;
		pHead->data = element;
		pHead->pNext = NULL;
		size++;
		return;
	}
	Box *newBox = new Box;
	newBox->data = element;
	if (pHead->data->frequency>=element->frequency)
	{
		newBox->pNext = pHead;
		pHead = newBox;
	}
	else if (pTail->data->frequency <=element->frequency)
	{
		newBox->pNext = NULL;
		pTail->pNext = newBox;
		pTail = newBox;
	}
	else {
		Box *temp = pHead;
		while (temp)
		{
			if (temp->pNext&&newBox->data->frequency <= temp->pNext->data->frequency)
			{
				newBox->pNext = temp->pNext;
				temp->pNext = newBox;
				break;
			}
			temp = temp->pNext;
		}
	}
	/*newBox->pNext = NULL;
	pTail->pNext = newBox;
	pTail = pTail->pNext;*/
	size++;
	
}

template<class T>
inline void Queue<T>::dequeue()
{
	if (isEmpty())
	{
		std::cout << "The queue is empty!\n";
		return;
	}
	Box *temp = pHead;
	pHead = pHead->pNext;
	delete temp;
	size--;
}

template<class T>
inline bool Queue<T>::isEmpty()const
{
	if (size == 0)return true;
	return false;
}
