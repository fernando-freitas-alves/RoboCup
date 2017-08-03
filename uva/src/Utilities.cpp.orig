#include "Utilities.h"

template<class T, size_t N> constexpr size_t size(T (&)[N]) { return N; }

pair<unsigned int, unsigned int> getBallZone(WorldModel *WM)
{
    VecPosition ballPosition = WM->getGlobalPosition(OBJECT_BALL);
    double BallX = ballPosition.getX();
    double BallY = ballPosition.getY();
    // VecPosition posBall = WM->getBallPos();

    // printf("\r\n   %f   %f",BallX,BallY);

    double rX[] = {1./3, 2./3, 1},
           rY[] = {1./3, 2./3, 1};

    BallZoneX X;
    BallZoneY Y;
    // for (double r : rX)
    for (int i = 0; i < size(rX); i++)
        if (BallX <= (rX[i]-1./2) * PITCH_LENGTH)
        {
            X = BallZoneX(i);
            break;
        }
    for (int i = 0; i < size(rY); i++)
        if (BallY <= (rY[i]-1./2) * PITCH_WIDTH)
        {
            Y = BallZoneY(i);
            break;
        }

    return make_pair(X,Y);
}
