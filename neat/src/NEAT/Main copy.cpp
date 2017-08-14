// Getting Started

#include "Genome.h"
#include "Population.h"
#include "NeuralNetwork.h"
#include "Parameters.h"
#include "Substrate.h"

#include <vector>
// #include <iostream>
// #include <boost/asio.hpp>
// #include <boost/thread.hpp>
// #include <boost/bind.hpp>
// #include <boost/date_time/posix_time/posix_time.hpp>

using namespace NEAT;
using namespace std;

#define len(x) x.size()


// We need an evaluation function. It takes a Genome as a parameter and returns a float that is the fitness of the genome's phenotype.
double evaluate(Genome &genome)
{
    // this creates a neural network (phenotype) from the genome
    NeuralNetwork net;
    genome.BuildPhenotype(net);

    // let's input just one pattern to the net, activate it once and get the output
    vector<double> input = {1.0, 0.0, 1.0};
    net.Input(input);
    net.Activate();
    vector<double> output = net.Output();

    // the output can be used as any other iterable. For the purposes of the tutorial,
    // we will consider the fitness of the individual to be the neural network that outputs constantly
    // 0.0 from the first output (the second output is ignored)
    double fitness = 1.0 - output[0];
    return fitness;
}

// // Get all genomes from the population
// vector<shared_ptr<Genome>> GetGenomeList(Population &population)
// {
//     vector<shared_ptr<Genome>> genome_list;
//     // for (auto specie : population->m_Species)
//     for (size_t s = 0; s < len(population->m_Species); s++)
//     {
//         Species *specie = &population->m_Species[s];
//         for (size_t i = 0; i < len(specie->m_Individuals); i++)
//             genome_list.push_back(make_shared<Genome>(specie->m_Individuals[i]));
//         // for (Genome* individual : *specie.m_Individuals)
//             // genome_list.push_back(individual);
//     }
//     return genome_list;
// }

// vector<Genome> GetGenomeList(Population &population)
// {
//     vector<Genome> genome_list;
//     for (auto specie : population.m_Species)
//         for (auto individual : specie.m_Individuals)
//             genome_list.push_back(individual);
//     return genome_list;
// }

int main()
{
    // To begin evolution, we need to create a seed genome and a population from it. Before everything though, we create an object which holds all parameters used by NEAT:
    // This is usually the point where all custom values for the parameters are set. Here we set the population size to 100 individuals (default value is 300).
    Parameters params;
    params.PopulationSize = 100;
    uint16_t number_of_generations = 100;

    // Now we create a genome with 3 inputs and 2 outputs. Notice that we set more properties of the genome than just number of inputs/outputs. Also, if the number of inputs you're going to use in your project is 2, you need to write 3 in the constructor. Always add one extra input. The last input is always used as bias and also when you activate the network always set the last input to 1.0 (or any other constant non-zero value). The type of activation function of the outputs and hidden neurons is also set. Hidden neurons are optional.
    Genome genome(0, 3, 0, 2, false,
                  UNSIGNED_SIGMOID,
                  UNSIGNED_SIGMOID,
                  0, params);

    // After the genome is created, we create the population. The last two parameters specify whether the population should be randomized and how much. Because we are starting from a new genome and not one that was previously saved, we randomize the initial population.
    Population population(genome, params, true, 1.0, time(0));

    // Evolution can run now. We can enter the basic generational evolution loop.
    for(uint16_t generation = 1; generation <= number_of_generations; generation++)
    {
        // for (Species specie : population.m_Species)
        //     for (Genome individual : specie.m_Individuals)
        for(size_t s = 0; s < len(population.m_Species); s++)
            for(size_t i = 0; i < len(population.m_Species[s].m_Individuals); i++)
            {
                Genome *individual = &population.m_Species[s].m_Individuals[i];
                double fitness = evaluate(*individual);
                individual->SetFitness(fitness);
                // printf("\n%f", fitness);
            }


        // // retrieve a list of all genomes in the population
        // vector<shared_ptr<Genome>> genome_list = GetGenomeList(&population);

        // // // apply the evaluation function to all genomes
        // // // for (Genome* genome : genome_list)
        // // // for (size_t i = 0; i < len(genome_list); i++)
        // // for(vector<Genome*>::iterator i = genome_list.begin(); i != genome_list.end(); i++)
        // for (auto genome : genome_list)
        // {
        // //     Genome* genome = *i;
        // //     // // Genome genome = *genome_list[i];
        //     double fitness = evaluate(*genome);
        //     genome->SetFitness(fitness);
        //     printf("\n%f", fitness);
        // }

        // // retrieve a list of all genomes in the population
        // vector<Genome> genome_list = GetGenomeList(population);

        // // apply the evaluation function to all genomes
        // for (auto genome : genome_list)
        // {
        //     double fitness = evaluate(&genome);
        //     genome.SetFitness(fitness);
        //     printf("\n%f", fitness);
        // }

        // at this point we may output some information regarding the progress of evolution, best fitness, etc.
        // it's also the place to put any code that tracks the progress and saves the best genome or the entire
        // population. We skip all of this in the tutorial.
        double best = population.GetBestGenome().GetFitness();
        // genome.PrintAllTraits();
        printf("\n[%d] Best fitness: %f, Species: %lu", generation, best, len(population.m_Species));

        // advance to the next generation
        population.Epoch();
    }

    // The rest of the algorithm is controlled by the parameters we used to initialize the population. One can modify the parameters during evolution, accessing the population.Parameters object. When a population is saved, the parameters are saved along with it.
    printf("\nBest fitness: %f, Species:%lu\r\n", population.m_Species[0].GetLeader().GetFitness(), len(population.m_Species));
        // // print('? Best fitness:', evaluate(population.Species[0].GetLeader()), 'Species:', len(population.Species))

    // // write to file
    // import pickle
    // with open("last_population.txt", "wb") as file:
    //     pickle.dump(population, file)
    //     // fileByteArray = bytearray(population)
    //     // file.write(fileByteArray)

}
