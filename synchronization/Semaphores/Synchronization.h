#pragma once

#include "BufferOf7.h"
#include "CountingUtils.h"
#include "Print.h"


/* buffer declarations */

void push(char c)
{
	BufferOf7<char>::push(c);
}

char pop()
{
	return BufferOf7<char>::pop();
}

bool canProduce()
{
	return !BufferOf7<char>::isFull();
}

bool canConsume()
{
	return !BufferOf7<char>::isEmpty();
}

/* critical section mutex */
static Semaphore mutex = Semaphore(1);


void releaseMutex(int id)
{
	if (!isZeroAwaitingConsumers() && canConsume())
	{
		print(id, "waking consumers.");
		awaitingConsumersLock.v();
	}
	else if (!isZeroAwaitingProducers && canProduce())
	{
		print(id, "waking producers.");
		awaitingProducersLock.v();
	}
	else
	{
		mutex.v();
	}
}

void produce(int id, char product)
{
	mutex.p();
	if (!canProduce()
		|| (!isZeroMutexAwaitingConsumers() || !isZeroAwaitingConsumers())
		&& canConsume())
	{
		printP(id, "can't produce, WAITING.");
		increaseAwaitingProducers();
		mutex.v();
		awaitingProducersLock.p();
		printP(id, "WAKED, producing.");
		decreaseAwaitingProducers();
	}
	push(product);
	printP(id, "produced ", product);

	releaseMutex(id);
}

void consume(int id)
{
	char result;
	increaseMutexAwaitingConsumers();
	mutex.p();
	decreaseMutexAwaitingConsumers();
	if (!canConsume())
	{
		printC(id, "can't consume, WAITING.");
		increaseAwaitingConsumers();
		mutex.v();
		awaitingConsumersLock.p();
		decreaseAwaitingConsumers();
		printC(id, "WAKED, consuming.");
	}

	result = pop();
	printC(id, "consumed ", result);

	releaseMutex(id);
}