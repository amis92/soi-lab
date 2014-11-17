#pragma once

/* Consumers utilities */

static int awaitingConsumers = 0;
static Semaphore awaitingConsumersLock = Semaphore(0);
static Semaphore awaitingConsumersCountLock = Semaphore(1);

void increaseAwaitingConsumers()
{
	awaitingConsumersCountLock.p();
	++awaitingConsumers;
	awaitingConsumersCountLock.v();
}

void decreaseAwaitingConsumers()
{
	awaitingConsumersCountLock.p();
	--awaitingConsumers;
	awaitingConsumersCountLock.v();
}

bool isZeroAwaitingConsumers()
{
	bool isZero;
	awaitingConsumersCountLock.p();
	isZero = awaitingConsumers == 0;
	awaitingConsumersCountLock.v();
	return isZero;
}

/* Producers utilities */

static int awaitingProducers = 0;
static Semaphore awaitingProducersLock = Semaphore(0);
static Semaphore awaitingProducersCountLock = Semaphore(1);

void increaseAwaitingProducers()
{
	awaitingProducersCountLock.p();
	++awaitingProducers;
	awaitingProducersCountLock.v();
}

void decreaseAwaitingProducers()
{
	awaitingProducersCountLock.p();
	--awaitingProducers;
	awaitingProducersCountLock.v();
}

bool isZeroAwaitingProducers()
{
	bool isZero;
	awaitingProducersCountLock.p();
	isZero = awaitingProducers == 0;
	awaitingProducersCountLock.v();
	return isZero;
}