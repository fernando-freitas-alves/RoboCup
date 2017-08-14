#pragma once

#include "Genome.h"
#include "Parameters.h"
#include "Population.h"
#include "NeuralNetwork.h"
// #include <rpc/client.h>
// #include "pbrpc/ServiceManager.hh"

#include <chrono>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <thread>
#include <vector>

#include "../Utilities.h"

using namespace NEAT;
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
// using namespace pbrpc;
// using namespace rpc;

extern bool updateGen;
// extern ServiceManager srvMan;

#define len(x) x.size()

inline bool fileexists(const string &filePath)
{
    struct stat buffer;
    return !stat(filePath.c_str(), &buffer);
}

void NEAT_init(string ID);
Population NEAT_start(string ID);
void NEAT_end(Population population);
void NEAT_close();
Population getPopulation(const string &filePath);
