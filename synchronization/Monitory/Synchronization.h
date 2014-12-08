#pragma once

#include "BufferOf7.h"
#include "Print.h"

BufferOf7<char> buffer;

/* buffer declarations */

void push(char c)
{
	buffer.push(c);
}

char pop()
{
	return buffer.pop();
}


void produce(int id, char product)
{
	push(product);
	printP(id, "produced ", product);
}

void consume(int id)
{
	char result;
	result = pop();
	printC(id, "consumed ", result);
}