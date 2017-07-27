#include <stdlib.h>

using namespace std;

void test(void);
std::pair<unsigned int, unsigned int> getBallZone(WorldModel *WM);

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
