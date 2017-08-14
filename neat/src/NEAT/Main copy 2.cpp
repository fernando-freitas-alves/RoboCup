#include "Main.h"

// MAIN FUNCTION
// The code starts and ends execution here
int main()
{
    // Initiate Population
    string filePath = "last_population.txt";
    Population population = getPopulation(filePath);

    // Basic generational evolution loop based on generations of Species
    uint16_t number_of_generations = 100;
    for(uint16_t generation = 1; generation <= number_of_generations; generation++)
    {
        // For each Specie in the Population
        for(size_t s = 0; s < len(population.m_Species); s++)
        {
            Species *specie = &population.m_Species[s];

            // For each Individual in that Specie
            for(size_t i = 0; i < len(specie->m_Individuals); i++)
            {
                Genome *individual = &specie->m_Individuals[i];

                // Calculates the fitness of that Individual in the World
                double fitness = evaluate(*individual);
                individual->SetFitness(fitness);
            }
        }

        // Progress of evolution (generation, best fitness, etc.)
        double best = population.GetBestGenome().GetFitness();
        printf("\n[%d] Best fitness: %f, Species: %lu", generation, best, len(population.m_Species));
        // genome.PrintAllTraits();
        
        // Starts a new Epoch
        // This advances to the next generation by generating a new Offpsring and killing their parents
        population.Epoch();
    }

    // Final stats of the evolution
    Genome bestIndividual = population.m_Species[0].m_Individuals[0];
    double bestFitness = evaluate(bestIndividual);
    printf("\n? Best fitness: %f, Species: %lu\n", bestFitness, len(population.m_Species));
    
    // Write to file
    population.Save(filePath.c_str());
}


// GET POPULATION
// Takes a string as a parameter and returns a Population that has the same attributes from the file path of the string or a new Population if the file does not exist
Population getPopulation(const string &filePath)
{
    // Check if file exists
    if (fileexists(filePath))
    {
        printf("\nReading from file...\n");
        return Population(filePath.c_str());
    }
    else
    {
        printf("\nCreating new population...\n");

        // To start a new Population, first we need to create a seed genome and a population from it
        // Before everything though, we create an object which holds all parameters used by NEAT
        // This is usually the point where all custom values for the parameters are set
        Parameters params;
        params.PopulationSize = 100; // population size set to 100 individuals (default value is 300)

        // Now creates a Genome (individual)
        // It has with 3 inputs and 2 outputs
        // Also, if the number of inputs you're going to use in your project is n, you need to write n+1 in the constructor. Always add one extra input. The last input is always used as bias and also when you activate the network always set the last input to 1.0 (or any other constant non-zero value)
        // The type of activation function of the outputs and hidden neurons is also set. Hidden neurons are optional
        Genome genome(0, 3, 0, 2, false,
                      UNSIGNED_SIGMOID, // sigmoidal activation function
                      UNSIGNED_SIGMOID, // sigmoidal activation function
                      0, params);

        // After the genome is created, creates the population
        // The last two parameters specify whether the population should be randomized and how much. Because we are starting from a new Genome and not one that was previously saved, we randomize the initial population
        return Population(genome, params, true, 1.0, time(0));
    }
}


// EVALUATION FUNCTION
// Takes a Genome as a parameter and returns a float that is the fitness of the Genome's phenotype in the World
double evaluate(Genome &genome)
{
    // Creates a neural network (phenotype) from the genome
    NeuralNetwork net;
    genome.BuildPhenotype(net);

    // let's input just one pattern to the net, activate it once and get the output
    vector<double> input = {1.0, 0.0, 1.0};
    net.Input(input);
    net.Activate();
    vector<double> output = net.Output();

    // Calculates the fitness
    double fitness = 1.0 - output[0];
    return fitness;
}
