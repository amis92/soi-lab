#pragma once

class ConsumerAwait : private Monitor
{
private:
	int _counter;
public:
	ConsumerAwait()
	{
		_counter = 0;
	}

	void inc()
	{
		enter();
		++_counter;
		leave();
	}

	void dec()
	{
		enter();
		--_counter;
		leave();
	}

	bool isZero()
	{
		bool result;
		enter();
		result = _counter == 0;
		leave();
		return result;
	}
};