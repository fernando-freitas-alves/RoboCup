// #include <stdlib.h>
#include <cstdio>
#include <utility>

using namespace std;

pair<unsigned int, unsigned int> getBallZone(WorldModel *WM);

enum BallZoneX
{
    DEFENSE,
    MIDFIELD,
    ATTACK
};

enum BallZoneY
{
    LEFT,
    MIDDLE,
    RIGHT
};
