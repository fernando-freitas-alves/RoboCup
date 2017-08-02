// #include <stdlib.h>
#include <cstdio>
#include <utility>
#include "WorldModel.h"

using namespace std;

pair<unsigned int, unsigned int> getBallZone(WorldModel *WM);

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
