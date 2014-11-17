#pragma once

template <class T>
/*
* Static circled buffer with just isEmpty, isFull, push, pop operations.
* init() clears buffer.
*/
class BufferOf7
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
		return (_begin == modIncrement(_end));
	}

	static void push(T item)
	{
		_buffer[_end] = item;
		_end = modIncrement(_end);
	}

	static T pop()
	{
		T item = _buffer[_begin];
		_begin = modIncrement(_begin);
		return item;
	}

private:
	/* position of first element to pop */
	static int _begin;
	/* first free position */
	static int _end;
	/* number of available slots*/
	static const int _size = 7;
	/* buffer holding elements */
	static T _buffer[];

	/* increases value by 1 and does modulo size */
	static int modIncrement(int value)
	{
		return value == _size ? 0 : value + 1;
	}
};

