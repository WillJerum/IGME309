#ifndef __MYQUEUE_H_
#define __MYQUEUE_H_

#include <stdio.h>
#include <iostream>

template <typename T>
class MyQueue
{
public:

	// initialize required vars
	int size = 0; // size of queue
	int index = 0; // tracks index
	T* data = nullptr; // data will be stored here

	MyQueue()
	{
		size = 2;
		index = 0;
		data = new T[size];
	}
	~MyQueue() // destructor
	{
		Destroy();
	}

	void Destroy(void) // when destructor is called
	{
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}
	}

	void CopyData(MyQueue& source) // copies data from source
	{
		this->size = source.size;
		this->index = source.index;
		this->data = new T[size];
		memcpy(this->data, source.data, sizeof(T) * index);
	}

	MyQueue(MyQueue& source)
	{
		if (this != source)
		{
			CopyData(source);
		}
	}

	MyQueue& operator=(MyQueue& source)
	{
		if (this != &source)
		{
			Destroy();
			CopyData(source);
		}

	}
};


#endif //__MYQUEUE_H__
