#include "Algorithms.h"


Algorithms::Algorithms()
{
	//create empty neurons
	

	CreateInputNeurons();
	CreateOutputNeurons(SetOutputTrue);
}

Algorithms::~Algorithms()
{
	while (neurons.size() > 0)
	{
		Neuron* n = neurons.back();

		//connections
		while (n->targetSynapses.size() > 0)
		{
			Connection* c = n->targetSynapses.back();
			delete c;
			n->targetSynapses.pop_back();
		}

		delete n;
		neurons.pop_back();
	}
}

int Algorithms::UpdateSynapses()
{
	try
	{
		for (int i = 0; i < 1000; i++)
		{
			if (ActivationQueue.size() <= 0 )
			{
				return 0;
			}
			Neuron* current = ActivationQueue.front();

			if (current->activity >= current->threshold)
			{
				for (int j = 0; j < current->targetSynapses.size(); j++)
				{
					Neuron* target = current->targetSynapses.at(j)->target;
					if (!target->inQueue)
					{
						ActivationQueue.push(target);
						target->inQueue = true;
					}
					target->activity += current->targetSynapses.at(j)->weight++;
					target->activity = (target->activity > 255) ? 255 : target->activity;
				}

				if (current->isOutput)
				{
					current->outputFunc(current->activity);
				}
			}
			else
			{
				for (int j = 0; j < current->sourceSynapses.size(); j++)
				{
					current->sourceSynapses.at(j)->weight -= 10;
					current->sourceSynapses.at(j)->weight = current->sourceSynapses.at(j)->weight < 0 ? 0 : current->sourceSynapses.at(j)->weight;
					current->threshold += 5;
					current->threshold = current->threshold > 255 ? 255 : current->threshold;
				}
			}

			

			ActivationQueue.pop();
			current->inQueue = false;
			current->activity = 0;
		}
	}
	catch (std::exception e)
	{
		printf(e.what());
		return 1;
	}

	return 0;
}

void Algorithms::CreateInputNeurons()
{
	for (int i = 0; i < INITIALNEURONS; i++)
	{
		Neuron* n = new Neuron();
		n->activity = 0;
		n->inQueue = false;
		n->threshold = 150;

		inputNeurons.push_back(n);
	}
	
}

void Algorithms::CreateInputNeuronsFromFile(std::fstream* connectionsFile) {}

void Algorithms::CreateOutputNeurons(void (*outputFunc)(int16_t))
{
	for (int i = 0; i < OUTPUTNEURONS; i++)
	{
		Neuron* n = new Neuron();
		n->activity = 0;
		n->inQueue = false;
		n->isOutput = true;
		n->threshold = 125;
		n->outputFunc = outputFunc;
	}
}

void Algorithms::CreateOutputNeuronsFromFile(std::fstream *connectionsFile, void (*outputFunc)(int16_t))
{
	for (int i = 0; i < OUTPUTNEURONS; i++)
	{
		Neuron* n = new Neuron();
		n->activity = 0;
		n->inQueue = false;
		n->isOutput = true;
		n->threshold = 125;
		n->outputFunc = outputFunc;

		//load connections from file
		int num;
		*connectionsFile >> num;
		while (num != -1)
		{
			Connection* c = new Connection();
			c->target = n;
			c->source = neurons.at(num);
			*connectionsFile >> num;
			c->weight = num;
			*connectionsFile >> num;
			c->source->targetSynapses.push_back(c);
			n->sourceSynapses.push_back(c);
		}

	}
}

void Algorithms::LoadConnectionsFromFile()
{

	//create connections from file
	std::fstream connectionFile("Connections.txt", std::ios_base::in);

	for (int i = 0; i < neurons.size(); i++)
	{
		Neuron* n = neurons.at(i);;
		int num;
		connectionFile >> num;
		while (num != -1)
		{
			Connection* c = new Connection();
			c->source = n;
			c->target = neurons.at(num);
			connectionFile >> num;
			c->weight = num;
			connectionFile >> num;
			c->target->sourceSynapses.push_back(c);
			n->targetSynapses.push_back(c);
		}
	}

	CreateInputNeuronsFromFile(&connectionFile);
	CreateOutputNeuronsFromFile(&connectionFile, PrintOutput);

	//neuronFile.close();
	connectionFile.close();
}



void PrintOutput(int16_t activity) 
{ 
	printf("%d ", activity);
}

void SetOutputTrue(int16_t _)
{
}