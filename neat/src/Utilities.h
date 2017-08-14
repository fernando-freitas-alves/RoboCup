#pragma once

// #include <stdlib.h>
#include <cstdio>
#include <utility>
#include <cmath>
#include <vector>

// #include "BasicPlayer.h"
#include "Player.h"
#include "ServerSettings.h"
#include "SoccerTypes.h"
#include "WorldModel.h"

using namespace std;

#define getRelPos(Y,X) WM->getGlobalPosition(Y) - WM->getGlobalPosition(X)
#define bool2sign(x) (2*x - 1)
#define sign(x) bool2sign(x >= 0)

template<class T, size_t N> constexpr size_t size(T(&)[N])
{
    return N;
}

enum BallZoneX
{
    DEFENSE,
    CENTER,
    ATTACK
};

enum BallZoneY
{
    LEFT,
    MIDDLE,
    RIGHT
};

pair<uint, uint> getBallZone(WorldModel *WM);
pair<uint, VecPosition> gradDesc(Player *p, WorldModel  *WM, double dConfThr,
                                 double      da0, double dr0,
                                 double      ka,  double kr,
                                 double      k,   double Fmin);
VecPosition Fatt(VecPosition dp, double da0, double ka);
VecPosition Frep(VecPosition dp, double dr0, double kr);
ObjectT getClosestInFieldInSetTo(WorldModel *WM,
                                 ObjectSetT set,    ObjectT objTarget,
                                 double     *dDist, double  dConfThr);


struct WorldState
{
    VecPosition ball;
    vector<VecPosition> player;
};

WorldState getWorldState(WorldModel *WM);
vector<double> WorldAnalyseInput(WorldState state);
size_t WorldAnalyzeOutput(vector<double> output);
double evaluateWorldState(WorldModel *WM);
