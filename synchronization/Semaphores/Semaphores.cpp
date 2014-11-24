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

#include "BufferOf7.h"
#include "CountingUtils.h"

static bool isExitRequest = false;

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

/* mutex awaiting mutex */
static Semaphore mutexAwaitingLock = Semaphore(1);

/* critical section mutex */
static Semaphore mutex = Semaphore(1);

/* input/output mutex */
static Semaphore ioMutex = Semaphore(1);

void print(int id, const char* output)
{
	ioMutex.p();
	std::cout << "Thread id=" << id << " says: " << output << std::endl;
	ioMutex.v();
}

void printC(int id, const char* output)
{
	ioMutex.p();
	std::cout << "Consumer id=" << id << " says: " << output << std::endl;
	ioMutex.v();
}

void printC(int id, const char* output, char c)
{
	ioMutex.p();
	std::cout << "Consumer id=" << id << " says: " << output << c << std::endl;
	ioMutex.v();
}

void printP(int id, const char* output)
{
	ioMutex.p();
	std::cout << "Producer id=" << id << " says: " << output << std::endl;
	ioMutex.v();
}

void printP(int id, const char* output, char c)
{
	ioMutex.p();
	std::cout << "Producer id=" << id << " says: " << output << c << std::endl;
	ioMutex.v();
}

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

DWORD WINAPI Producer(_In_ LPVOID lpParameter)
{
	int id = reinterpret_cast<int>(lpParameter);
	char product = (id % 2) == 0 ? 'A' : 'a';
	printP(id, "started with letter ", product);
	try
	{
		while (!isExitRequest)
		{
			produce(id, product);
			product = product == 'Z' ? 'A' : (product == 'z' ? 'a' : (product + 1));
		}
	}
	catch (...)
	{
		printP(id, "blown out.");
	}
	printP(id, "quitting.");
	return 0;
}

DWORD WINAPI Consumer(_In_ LPVOID lpParameter)
{
	int id = reinterpret_cast<int>(lpParameter);
	printC(id, "started.");
	try
	{
		while (!isExitRequest)
		{
			consume(id);
		}
	}
	catch (...)
	{
		printC(id, "blown out.");
	}
	printC(id, "quitting.");
	return 0;
}

#define PRODUCERS_COUNT 2
#define CONSUMERS_COUNT 2

int _tmain(int argc, _TCHAR* argv[])
{
	BufferOf7<char>::init();
	HANDLE threads[PRODUCERS_COUNT + CONSUMERS_COUNT];
	int id = 1;
	for (; id <= PRODUCERS_COUNT; ++id)
	{
		threads[id - 1] = CreateThread(nullptr, 0, &Producer, (LPVOID)id, 0, nullptr);
	}
	for (; id <= PRODUCERS_COUNT + CONSUMERS_COUNT; ++id)
	{
		threads[id - 1] = CreateThread(nullptr, 0, &Consumer, (LPVOID)id, 0, nullptr);
	}
	_gettchar();
	isExitRequest = true;
	Sleep(1000l);
	_gettchar();
	return 0;
}

