#pragma once

template <typename T>
/*
* Static circled buffer with just isEmpty, isFull, push, pop operations.
* init() clears buffer.
*/
class BufferOf7 : private Monitor
{

private:
	/* position of first element to pop */
	int _begin;
	/* first free position */
	int _end;
	/* number of available slots*/
	static const int MY_BUFFER_SIZE = 7;
	/* buffer holding elements */
	T _buffer[MY_BUFFER_SIZE];

	Condition _consumers, _producers;

	int _waitingConsumers;

	/* increases value by 1 and does modulo size */
	int modIncrement(int value);

	void doPush(T item);

	T doPop();

	void doSignaling();

public:
	BufferOf7();

	bool isEmpty();

	bool isFull();

	void push(T item);

	T pop();
};

template <typename T>
int BufferOf7<T>::modIncrement(int value)
{
	return value == MY_BUFFER_SIZE ? 0 : value + 1;
}

template <typename T>
void BufferOf7<T>::doPush(T item)
{
	_buffer[_end] = item;
	_end = modIncrement(_end);
}

template <typename T>
T BufferOf7<T>::doPop()
{
	T item = _buffer[_begin];
	_begin = modIncrement(_begin);
	return item;
}

template <typename T>
void BufferOf7<T>::doSignaling()
{
	if (!isEmpty() && _waitingConsumers > 0)
		signal(_consumers);
	else if (!isFull())
		signal(_producers);
}

template <typename T>
BufferOf7<T>::BufferOf7()
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
	enter();
	if (isFull() || _waitingConsumers > 0)
		wait(_producers);
	doPush(item);
	doSignaling();
	leave();
}

template <typename T>
T BufferOf7<T>::pop()
{
	enter();
	if (isEmpty())
	{
		++_waitingConsumers;
		wait(_consumers);
		--_waitingConsumers;
	}
	T item = doPop();
	doSignaling();
	leave();
	return item;
}