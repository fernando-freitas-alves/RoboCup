
void test(void)
{
    printf("\r\n\r\ntest...\r\n\r\n");
}

pair<unsigned int, unsigned int> getBallZone(WorldModel *WM)
{
    double BallX = WM->getGlobalPosition(OBJECT_BALL).getX();
    double BallY = WM->getGlobalPosition(OBJECT_BALL).getY();
    // VecPosition posBall = WM->getBallPos();

    vector<double> rX = {1/3, 2/3, 1},
                        rY = {1/3, 2/3, 1};
    vector<double> X, Y;

    for (double r : rX) X.push_back(r * PITCH_LENGTH);
    for (double r : rY) Y.push_back(r * PITCH_WIDTH);

    for (unsigned int i  = 0; i < X.size(); i++)
    {
        x = X[i]
        if (BallX <= X[i]) break;
    }
    for (unsigned int i  = 0; i < Y.size(); i++)
    {
        y = Y[i]
        if (BallY <= Y[i]) break;
    }

    fprintf("X = %d\tY = %d",x,y);

    return make_pair(x,y);
}
