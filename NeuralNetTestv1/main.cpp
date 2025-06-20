#include "Neuron.h";
#include "Algorithms.h"
#include <iostream>


int main()
{
	Algorithms::instance = new Algorithms();

	Algorithms::instance->neurons.front()->activity = 255;
	Algorithms::instance->ActivationQueue.push(Algorithms::instance->neurons.front());

	return Algorithms::instance->UpdateSynapses();
}