#pragma once

/* Consumers utilities */

static int awaitingConsumers = 0;
static Semaphore awaitingConsumersLock = Semaphore(1);

void increaseAwaitingConsumers()
{
	awaitingConsumersLock.p();
	++awaitingConsumers;
	awaitingConsumersLock.v();
}

void decreaseAwaitingConsumers()
{
	awaitingConsumersLock.p();
	--awaitingConsumers;
	awaitingConsumersLock.v();
}

bool isZeroAwaitingConsumers()
{
	bool isZero;
	awaitingConsumersLock.p();
	isZero = awaitingConsumers == 0;
	awaitingConsumersLock.v();
	return isZero;
}

/* Producers utilities */

static int awaitingProducers = 0;
static Semaphore awaitingProducersLock = Semaphore(1);

void increaseAwaitingProducers()
{
	awaitingProducersLock.p();
	++awaitingProducers;
	awaitingProducersLock.v();
}

void decreaseAwaitingProducers()
{
	awaitingProducersLock.p();
	--awaitingProducers;
	awaitingProducersLock.v();
}

bool isZeroAwaitingProducers()
{
	bool isZero;
	awaitingProducersLock.p();
	isZero = awaitingProducers == 0;
	awaitingProducersLock.v();
	return isZero;
}