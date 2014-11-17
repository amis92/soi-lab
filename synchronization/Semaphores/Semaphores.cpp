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

