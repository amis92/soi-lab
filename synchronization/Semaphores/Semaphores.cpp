// Semaphores.cpp : Defines the entry point for the console application.
//

/* Instructions:
 * Przy realizacji zadania do synchronizacji nale�y wykorzysta� semafor 
 * (tylko operacje p i v) � klasa Semaphore zdefiniowana w pliku monitor.h
 * znajduj�cym si� na stronie przedmiotu. Zadanie nale�y wykona� z u�yciem
 * w�tk�w (korzystaj�c ze zmiennych globalnych).
 *
 * Bufor 7 elementowy FIFO. Dw�ch konsument�w i dw�ch producent�w. Konsumenci
 * maj� pierwsze�stwo w dost�pie do bufora. Pierwsze�stwo oznacza, �e je�li
 * bufor jest zaj�ty przez producenta i konsument nie mo�e si� do niego dosta�,
 * to dost�p do bufora jako nast�pny musi uzyska� oczekuj�cy konsument.
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

