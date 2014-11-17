// Semaphores.cpp : Defines the entry point for the console application.
//

/* Instructions:
 * Przy realizacji zadania do synchronizacji nale¿y wykorzystaæ semafor 
 * (tylko operacje p i v) – klasa Semaphore zdefiniowana w pliku monitor.h
 * znajduj¹cym siê na stronie przedmiotu. Zadanie nale¿y wykonaæ z u¿yciem
 * w¹tków (korzystaj¹c ze zmiennych globalnych).
 *
 * Bufor 7 elementowy FIFO. Dwóch konsumentów i dwóch producentów. Konsumenci
 * maj¹ pierwszeñstwo w dostêpie do bufora. Pierwszeñstwo oznacza, ¿e jeœli
 * bufor jest zajêty przez producenta i konsument nie mo¿e siê do niego dostaæ,
 * to dostêp do bufora jako nastêpny musi uzyskaæ oczekuj¹cy konsument.
 */



#include "stdafx.h"

/* buffer declarations */

template <class T>
/*
 * Static circled buffer with just isEmpty, isFull, push, pop operations.
 * init() clears buffer.
 */
class Buffer
{
public:
	static void init()
	{
		_begin = 0;
		_end = 0;
	}

	static bool isEmpty()
	{
		return (_begin == _end);
	}

	static bool isFull()
	{
		/* if end is at last possible index */
		return (_begin == modIncrement(_end));
	}

	static void push(T item)
	{
		_end = (_end + 1) % _size;
		_buffer[_end] = item;
	}

	static T pop()
	{
		T item = _buffer[_begin];
		_begin = (_begin + 1) % _size;
		return item;
	}

private:
	/* position of first element to pop */
	static int _begin;
	/* first free position */
	static int _end;
	/* number of available slots*/
	static const int _size = 7;
	/* buffer holding elements with one additional overflow token space */
	static const T _buffer[_size + 1];

	/* increases value by 1 and does modulo size */
	static int modIncrement(int value)
	{
		return value == _size ? 0 : value + 1;
	}
};

/* critical section mutex */
Semaphore mutex = Semaphore(1);


DWORD WINAPI Producer(_In_ LPVOID lpParameter)
{
	return 0;
}

DWORD WINAPI Consumer(_In_ LPVOID lpParameter)
{
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE threads[4];
	LPVOID consumerParams;
	threads[0] = CreateThread(nullptr, 0, &Consumer, consumerParams, 0, nullptr);
	return 0;
}

