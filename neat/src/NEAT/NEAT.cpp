#include "NEAT.h"

string NEAT_filePath;// = "last_population.txt";
string NEAT_block_filePath = "NEAT_running.lock";
// int fd, rc;
FILE* bFile = NULL;
bool updateGen = false;
// rpc::client client("127.0.0.1", 8080);

// Initiatialize Paramertres
void NEAT_init(string ID)
{
    // NEAT_filePath = "last_population_" + ID + ".txt";
    NEAT_filePath = "last_population.txt";
    // client.call("test").as<void>();
}

// Initiatialize Population
Population NEAT_start(string ID)
{
    // printf("\n%s waiting...", ID.c_str());
    // while (fileexists(NEAT_block_filePath));// sleep_for(1ms);
    // FILE* bFile = fopen(NEAT_block_filePath.c_str(), "w");
    // fclose(bFile);
    // printf("\n%s passed!", ID.c_str());

    // do
    // {
    //     fd = open(NEAT_block_filePath.c_str(), O_RDWR | O_CREAT, 0666); // open or create lockfile
    //     rc = flock(fd, LOCK_EX | LOCK_NB); // grab exclusive lock, fail if can't obtain.
    // }
    // while (!rc);
    
    // while (fileexists(NEAT_block_filePath));// sleep_for(1ms);
    // FILE* bFile = fopen(NEAT_block_filePath.c_str(), "w");
    // fclose(bFile);

    // do
    // {
    //     bFile = fopen(NEAT_block_filePath.c_str(), "w");
    //     printf(" stuck_here");
    // }
    // while (bFile == NULL);// sleep_for(1ms);

    return getPopulation(NEAT_filePath);
}

void NEAT_end(Population population)
{
    // Progress of evolution (generation, best fitness, etc.)
    double best = population.GetBestGenome().GetFitness();
    if (updateGen)
        printf("\nBest fitness: %f, Species: %lu\n\n", best, len(population.m_Species));
    
    // Starts a new Epoch
    // This advances to the next generation by creating a new Offpsring and killing their parents
    population.Epoch(); // the magic happens here
    
    // Write to file
    population.Save(NEAT_filePath.c_str());
    NEAT_close();
    updateGen = false;
}

void NEAT_close()
{
    // fclose(bFile);
    // remove(NEAT_block_filePath.c_str());

    // sleep_for(2ms);

    // if (fd < 0) return;
    // remove(NEAT_block_filePath.c_str());
    // close(fd);
}

// GET POPULATION
// Takes a string as a parameter and returns a Population that has the same attributes from the file path of the string or a new Population if the file does not exist
Population getPopulation(const string &filePath)
{
    // Check if file exists
    if (fileexists(filePath))
    {
        // printf("\nReading from file...\n");
        return Population(filePath.c_str());
    }
    else
    {
        // printf("\nInitializing new population...\n");

        // To start a new Population, first we need to create a seed genome and a population from it
        // Before everything though, we create an object which holds all parameters used by NEAT
        // This is usually the point where all custom values for the parameters are set
        Parameters params;
        params.PopulationSize = 10; // population size set to 10 individuals (default value is 300)

        // Now creates a Genome (individual seed)
        // It has with 3 inputs and 2 outputs
        // Also, if the number of inputs you're going to use in your project is n, you need to write n+1 in the constructor. Always add one extra input. The last input is always used as bias and also when you activate the network always set the last input to 1.0 (or any other constant non-zero value)
        // The type of activation function of the outputs and hidden neurons is also set. Hidden neurons are optional
        Genome genome(0,                // ID (can be anything at this point)
                      2*2*1+1, // 2*2*11+1,          // number of input  layers based on all players and ball (x,y) positions
                      5,                // number of hidden layers
                      5,                // number of output layers based on codification of possible action commands for an agent
                      false,            // enables to connect hidden neurons
                      UNSIGNED_SIGMOID, // sigmoidal activation function
                      UNSIGNED_SIGMOID, // sigmoidal activation function
                      1,                // enables to add hidden layers
                      params);          // parameters

        // After the genome is created, creates the population
        // The last two parameters specify whether the population should be randomized and how much. Because we are starting from a new Genome and not one that was previously saved, we randomize the initial population
        return Population(genome,    // first specie's individual seed
                          params,    // parameters
                          true,      // randomize weights
                          1.0,       // randomization range
                          time(0));  // random seed based on time
    }
}

