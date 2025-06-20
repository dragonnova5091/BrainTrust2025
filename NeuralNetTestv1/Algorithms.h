#pragma once
#include "Neuron.h"
#include <fstream>

class Algorithms
{
public:
	static Algorithms *instance;

	std::queue<Neuron*> ActivationQueue;

	std::vector<Neuron*> neurons;
	std::vector<Neuron*> inputNeurons;

	Algorithms();
	~Algorithms();

	void CreateInputNeurons();
	void CreateInputNeuronsFromFile(std::fstream *connectionFile);
	void CreateOutputNeurons(void (*outputFunc)(int16_t));
	void CreateOutputNeuronsFromFile(std::fstream *connectionFile, void (*outputFunc)(int16_t));

	void UpdateWeights();

	int UpdateSynapses();

	void LoadConnectionsFromFile();

protected:
	

};

void PrintOutput(int16_t activity);
void SetOutputTrue(int16_t _);

class ActivityMap
{
	std::vector<Neuron*> inputActivity;
	std::vector<Neuron*> outputActivity;
	std::vector<Neuron*> hiddenActivity;
};