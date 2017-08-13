// #include <stdlib.h>
#include <cstdio>
#include <utility>
#include <cmath>
#include "WorldModel.h"
#include "SoccerTypes.h"
#include "Player.h"

using namespace std;

#define getRelPos(Y,X) WM->getGlobalPosition(Y) - WM->getGlobalPosition(X)

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