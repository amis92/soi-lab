#pragma once

template <typename T>
/*
* Static circled buffer with just isEmpty, isFull, push, pop operations.
* init() clears buffer.
*/
class BufferOf7
{

private:
	/* position of first element to pop */
	static int _begin;
	/* first free position */
	static int _end;
	/* number of available slots*/
	static const int _size = 7;
	/* buffer holding elements */
	static T _buffer[_size];

	/* increases value by 1 and does modulo size */
	static int modIncrement(int value);

public:
	static void init();

	static bool isEmpty();

	static bool isFull();

	static void push(T item);

	static T pop();
};

template <typename T>
int BufferOf7<T>::_begin = 0;

template <typename T>
int BufferOf7<T>::_end = 0;

template <typename T>
char BufferOf7<T>::_buffer[_size];

template <typename T>
int BufferOf7<T>::modIncrement(int value)
{
	return value == _size ? 0 : value + 1;
}

template <typename T>
void BufferOf7<T>::init()
{
	_begin = 0;
	_end = 0;
}

template <typename T>
bool BufferOf7<T>::isEmpty()
{
	return (_begin == _end);
}

template <typename T>
bool BufferOf7<T>::isFull()
{
	return (_begin == modIncrement(_end));
}

template <typename T>
void BufferOf7<T>::push(T item)
{
	_buffer[_end] = item;
	_end = modIncrement(_end);
}

template <typename T>
T BufferOf7<T>::pop()
{
	T item = _buffer[_begin];
	_begin = modIncrement(_begin);
	return item;
}