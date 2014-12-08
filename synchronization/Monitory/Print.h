#pragma once
#include <iostream>
#include "monitor.h"

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