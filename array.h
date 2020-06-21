#ifndef __ARRAY
#define __ARRAY

#include <iostream>
using namespace std;

template<class T>
class Array
{
	int logSize, phySize;
	char delimiter;
	T* arr;

public:
	Array(int size = 10, char delimiter = ' '); //c'tor
	~Array();

	bool isEmpty() const;
    int size() const;
	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);
	const T& operator[](const int index) const;
	friend ostream& operator<<(ostream& os, const Array& arr)
	{
		for (int i = 0; i < arr.logSize; i++)
		{
			os << arr.arr[i] << arr.delimiter;
		}
		return os;
	}
};
#endif // !__ARRAY

template<class T>
Array<T>::Array(int size, char delimiter) : phySize(size), logSize(0), delimiter(delimiter) //C'tor
{
	arr = new T[phySize];
}

template<class T>
const Array<T>& Array<T>:: operator=(const Array& other)
{
	if (this != &other)
	{
		delete[]arr;
		phySize = other.phySize;
		logSize = other.logSize;
		delimiter = other.delimiter;
		arr = new T[phySize];
		for (int i = 0; i < logSize; i++)
			arr[i] = other.arr[i];
	}
	return *this;
}

template <class T>
T* reallocArray(T* arr, int oldSize, int newSize)
//This function make the ballot array bigger.
{
	int i;
	T* newArr = new T[newSize];//allocate new memory according to a given size.
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];//copy data.
	}

	delete[] arr;//deallocate old memory.
	return newArr;
}

template<class T>
const Array<T>& Array<T>:: operator+=(const T& newVal)
{
	if (logSize == phySize)
	{
		phySize *= 2;
		arr = reallocArray(arr, logSize, phySize);
	}
	arr[logSize] = newVal;
	logSize++;
	return *this;
}

template<class T>
const T& Array<T>::operator[](const int index) const
{
	return arr[index];
}

template<class T>
bool Array <T>::isEmpty() const
{
	return arr == nullptr;
}

template<class T>
int Array <T>::size() const
{
	return logSize;
}

template<class T>
Array<T>:: ~Array()
{
	delete[]arr;
}