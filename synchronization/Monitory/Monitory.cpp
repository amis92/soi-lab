// Monitory.cpp : Defines the entry point for the console application.

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
#include "Synchronization.h"

#define PRODUCERS_COUNT 2
#define CONSUMERS_COUNT 2

static bool isExitRequest = false;
static Semaphore* threadSemaphores[PRODUCERS_COUNT + CONSUMERS_COUNT];
static HANDLE threads[PRODUCERS_COUNT + CONSUMERS_COUNT];

DWORD WINAPI Producer(_In_ LPVOID lpParameter)
{
	int id = reinterpret_cast<int>(lpParameter);
	char product = (id % 2) == 0 ? 'A' : 'a';
	printP(id, "started with letter ", product);
	try
	{
		while (!isExitRequest)
		{
#ifdef _DEBUG
			threadSemaphores[id - 1]->p();
#endif
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
#ifdef _DEBUG
			threadSemaphores[id - 1]->p();
#endif
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

bool exec()
{
	char command;
	print(0, "Enter command (s X - do step with thread X / q - quit):");
	std::cin >> command;
	switch (command)
	{
	case 's':
		int id;
		std::cin >> id;
		if (id > PRODUCERS_COUNT + CONSUMERS_COUNT || id < 1)
		{
			print(0, "No such thread.");
			return false;
		}
		threadSemaphores[id - 1]->v();
		break;
	case 'q':
		print(0, "Exiting now.");
		return true;
	default:
		break;
	}
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	BufferOf7<char>::init();
	for (int i = 0; i < PRODUCERS_COUNT + CONSUMERS_COUNT; ++i)
	{
		threadSemaphores[i] = new Semaphore(0);
	}
	int id = 1;
	for (; id <= PRODUCERS_COUNT; ++id)
	{
		threads[id - 1] = CreateThread(nullptr, 0, &Producer, (LPVOID)id, 0, nullptr);
	}
	for (; id <= PRODUCERS_COUNT + CONSUMERS_COUNT; ++id)
	{
		threads[id - 1] = CreateThread(nullptr, 0, &Consumer, (LPVOID)id, 0, nullptr);
	}
#ifdef _DEBUG
	bool isExit = false;
	do
	{
		isExit = exec();
	} while (!isExit);
#else
	_gettchar();
	isExitRequest = true;
	Sleep(1000l);
#endif //debug
	_gettchar();
	return 0;
}

