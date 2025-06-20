#pragma once
#include <stdint.h>
#include <vector>
#include <queue>
#include "Globals.h"

struct Neuron;

struct Connection
{
	Neuron* source;
	Neuron *target;
	int16_t weight;
};

class Neuron
{
public:
	bool inQueue;
	bool isOutput = false;
	void (*outputFunc)(int16_t);

	int16_t activity;
	int16_t threshold;
	std::vector<Connection*> targetSynapses;
	std::vector<Connection*> sourceSynapses;
};