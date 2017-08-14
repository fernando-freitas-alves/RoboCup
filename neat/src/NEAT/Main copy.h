#include "Genome.h"
#include "Parameters.h"
#include "Population.h"
#include "NeuralNetwork.h"

#include <vector>
#include <sys/stat.h>

using namespace NEAT;
using namespace std;

#define len(x) x.size()

inline bool fileexists(const string &filePath)
{
    struct stat buffer;
    return !stat(filePath.c_str(), &buffer);
}

double evaluate(Genome &genome);
Population getPopulation(const string &filePath);
