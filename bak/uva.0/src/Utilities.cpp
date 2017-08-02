
template<class T, size_t N> constexpr size_t size(T (&)[N]) { return N; }

pair<unsigned int, unsigned int> getBallZone(WorldModel *WM)
{
    VecPosition ballPosition = WM->getGlobalPosition(OBJECT_BALL);
    double BallX = ballPosition.getX();
    double BallY = ballPosition.getY();
    // VecPosition posBall = WM->getBallPos();

    double rX[] = {1/3, 2/3, 1},
           rY[] = {1/3, 2/3, 1};

    BallZoneX X;
    BallZoneY Y;
    for (double r : rX)
        if (BallX <= r * PITCH_LENGTH)
        {
            X = BallZoneX(0);
            break;
        }
    for (double r : rY)
        if (BallY <= r * PITCH_WIDTH)
        {
            Y = BallZoneY(0);
            break;
        }

    printf("\r\nX = %d\tY = %d",X,Y);
    return make_pair(X,Y);
}
