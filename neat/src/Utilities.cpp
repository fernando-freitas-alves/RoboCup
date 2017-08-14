#include "Utilities.h"

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
        if (BallX <= (rX[i] - 0.5) * PITCH_LENGTH)
        {
            X = BallZoneX(i);
            break;
        }

    for (int i = 0; i < size(rY); i++)
        if (BallY <= (rY[i] - 0.5) * PITCH_WIDTH)
        {
            Y = BallZoneY(i);
            break;
        }

    return make_pair(X, Y);
}

// Calculates a single step of a gradient descent optimization iteration
pair<uint, VecPosition> gradDesc(Player *p, WorldModel  *WM, double dConfThr,
                                 double      da0, double dr0,
                                 double      ka,  double kr,
                                 double      k,   double Fmin)
{
    uint returnType = 1;
    int         i, dir     = 2 * (WM->getSide() == SIDE_LEFT) - 1;
    ObjectT     objAgent   = WM->getAgentObjectType();
    VecPosition posGoal = WM->getPosOpponentGoal();//(PITCH_LENGTH / 2.0, 0);
                        //(-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth());
    VecPosition posAgent   = WM->getAgentGlobalPosition(),
                dPosTarget = posGoal - posAgent,
                dPosObj,
                F(0,0),
                leftSideLine  = posAgent,
                rightSideLine = posAgent,
                ourSideLine   = posAgent,
                theirSideLine = posAgent;
    double dp, Fn;
    ObjectSetT set;

    leftSideLine .setY(-PITCH_WIDTH/2);
    rightSideLine.setY( PITCH_WIDTH/2);
    ourSideLine  .setX(-PITCH_LENGTH/2);
    theirSideLine.setX( PITCH_LENGTH/2);

    // ObjectT clTm = WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,objAgent,NULL,0.1);
    // VecPosition posClTm = WM->getGlobalPosition(clTm);

    //  printf("\r\nF =   "); F.show();
    // // Attractive forces
    // set = OBJECT_SET_TEAMMATES;
    // for (ObjectT obj = WM->iterateObjectStart(i, set, dConfThr);
    //      obj != OBJECT_ILLEGAL;
    //      obj = WM->iterateObjectNext(i, set, dConfThr))
    // {
    //     printf("\r\nthis=   "); WM->show(objAgent);
    //     printf("obj=   "); WM->show(obj);
    //     if (obj != objAgent) // do not include target object
    //     {
    //         dPosObj = WM->getGlobalPosition(obj);// - WM->getGlobalPosition(obj);
    //         F += Fatt(posAgent,dPosObj,da0,ka);
    //         printf("\r\nF+=   "); Fatt(posAgent,dPosObj,da0,ka).show();
    //     }
    // }

    // // F += Fatt(dPosTarget,da0,ka);
    // const char * side  = WM->getSide() == SIDE_RIGHT ? "RIGHT" : "LEFT";
    // const char * oside = WM->getSide() == SIDE_RIGHT ? "LEFT"  : "RIGHT";

    // printf("\r\n## %s %d ########################################", side, WM->getPlayerNumber());
    // printf("\r\nposAgent:\t"); posAgent.show();

    // printf("\r\n");
    // // dPosTarget = VecPosition(0,0) - WM->getGlobalPosition(objAgent);
    // printf("dPosTarget:\t"); WM->getGlobalPosition(OBJECT_OPPONENT_GOALIE).show(); //VecPosition(0,0).show();
    // printf("relPosTarget:\t"); dPosTarget.show();
    F += Fatt(dPosTarget,da0,ka);

    // // Repulsive forces
    // printf("\r\n");
    set = OBJECT_SET_OPPONENTS;
    for (ObjectT obj = WM->iterateObjectStart(i, set, dConfThr);
         obj != OBJECT_ILLEGAL;
         obj = WM->iterateObjectNext(i, set, dConfThr))
    {
        // printf("\r\nobj:\t\t%s %d", oside, obj - OBJECT_OPPONENT_1 + 1);
        // // dPosObj = WM->getRelativePosition(obj);
        dPosObj = getRelPos(obj, objAgent);
        // if (dPosObj.getMagnitude() < 5)
        //     // return NULL; //p->directPass(posClTm, PASS_FAST);
        //     // return make_pair(2, (VecPosition*)NULL); //p->directPass(posClTm, PASS_FAST);
        //     ;//returnType = 0;
        // printf("\r\nposObj:\t\t"); WM->getGlobalPosition(obj).show();
        // printf("relPosObj:\t"); dPosObj.show();
        F -= Frep(dPosObj,dr0,kr);
    }
    F -= Frep(leftSideLine  - posAgent,Fmin,kr);
    F -= Frep(rightSideLine - posAgent,Fmin,kr);
    F -= Frep(ourSideLine   - posAgent,Fmin,kr);
    F -= Frep(theirSideLine - posAgent,Fmin,kr);
    // dPosObj = VecPosition(-20,0) - WM->getGlobalPosition(objAgent);
    // printf("\r\nposObj:\t\t"); VecPosition(-20,0).show();
    // printf("relPosObj:\t"); dPosObj.show();
    // F -= Frep(dPosObj,dr0,kr);
    

    // printf("\r\n");
    // printf("\r\nk:\t\t%f", k);
    // // F = F * dir;
    Fn = F.getMagnitude();
    // printf("\r\nFn:\t\t%f", Fn);
    // // dp = (posAgent - dPosTarget).getMagnitude();
    // // printf("posAgent: "); posAgent.show();
    // // if (Fn) posAgent += F / Fn * k;// * pow(dp,3);
    if (Fn < Fmin)
    {
        // printf("\r\nForce too low! Increasing it.");
        F  = F.setMagnitude(Fmin);
        Fn = F.getMagnitude();
        // printf("\r\nFn:\t\t%f", Fn);
    }
    posAgent += F * k;// * pow(dp,3);
    // // posAgent.normalize();
    // printf("\r\nF:\t\t"); F.show();
    // printf("posAgent:\t"); posAgent.show();
    // printf("\r\n");
    // // return &posAgent;
    // // return make_pair(1, posAgent.getDirection());
    return make_pair(returnType, posAgent);
}

// Hybrid attractive force
VecPosition Fatt(VecPosition dp, double da0, double ka)
{
    double da = dp.getMagnitude();
    // printf("da:\t\t%f", da);
    // if (da <= da0) {printf("  [Parabolic force]"); return dp    * ka;}       // Parabolic force
    // else           {printf("  [Conic force]"); return dp/da * ka;}// * da0;} // Conic force
    if (da <= da0) return dp    * ka;       // Parabolic force
    else           return dp/da * ka;// * da0;} // Conic force
}

// Repulsive force
VecPosition Frep(VecPosition dp, double dr0, double kr)
{
    double dr = dp.getMagnitude();
    // printf("dr:\t\t%f", dr);
    // if (dr <= dr0) {printf("  [Repulsive force]"); return dp/dr * kr;} // * (1/dr - 1/dr0) * 1/pow(dr,2); // Inside ROI
    // else           {printf("  [Non-repulsive force]"); return 0;}                                         // Outside ROI
    if (dr <= dr0) return dp/dr * kr; // * (1/dr - 1/dr0) * 1/pow(dr,2); // Inside ROI
    else           return 0;                                         // Outside ROI
}

ObjectT getClosestInFieldInSetTo(WorldModel *WM,
                                 ObjectSetT set,    ObjectT objTarget,
                                 double     *dDist, double  dConfThr)
{
    ObjectT     closestObject = OBJECT_ILLEGAL;
    double      dMinMag       = 1000.0;
    VecPosition v;
    int         iIndex;

    for (ObjectT o = WM->iterateObjectStart(iIndex, set, dConfThr);
         o != OBJECT_ILLEGAL;
         o = WM->iterateObjectNext(iIndex, set, dConfThr))
        if (o != objTarget) // do not include target object
        {
            v = WM->getGlobalPosition(o);
            if (WM->isInField(v, 0)) // is in field
            {
                v -= WM->getGlobalPosition(objTarget);
                if (v.getMagnitude() < dMinMag)
                {
                    dMinMag       = v.getMagnitude();
                    closestObject = o;
                }
            }
        }
    WM->iterateObjectDone(iIndex);
    if (dDist != NULL)
        *dDist = dMinMag;
    return closestObject;
}

WorldState getWorldState(WorldModel *WM)
{
    int i;
    double dConfThr = 0.5;
    WorldState ws;
    ws.ball = WM->getGlobalPosition(OBJECT_BALL);

    ObjectSetT set = OBJECT_SET_TEAMMATES;
    for (ObjectT obj = WM->iterateObjectStart(i, set, dConfThr);
         obj != OBJECT_ILLEGAL;
         obj = WM->iterateObjectNext(i, set, dConfThr))
        ws.player.push_back(WM->getGlobalPosition(obj)); // getRelPos(obj, objAgent));

    set = OBJECT_SET_OPPONENTS;
    for (ObjectT obj = WM->iterateObjectStart(i, set, dConfThr);
         obj != OBJECT_ILLEGAL;
         obj = WM->iterateObjectNext(i, set, dConfThr))
        ws.player.push_back(WM->getGlobalPosition(obj)); // getRelPos(obj, objAgent));

    return ws;
}

vector<double> WorldAnalyseInput(WorldState state)
{
    vector<double> input;
    input.push_back(state.ball.getX());
    input.push_back(state.ball.getY());
    for (auto player : state.player)
    {
        input.push_back(player.getX());
        input.push_back(player.getY());
    }
    input.push_back(1.);
    return input;
}

size_t WorldAnalyzeOutput(vector<double> output)
{
    size_t selection = 0,
           k = 0;
    double threshold = 0.5;
    for (auto o : output)
    {
        printf("\n o: %f, o > threshold: %d, k: %lu,\t<< k++: %d", o, o>threshold, k, 1 << k);
        selection += ((size_t) (o > threshold)) << (k++);
        printf(",\tselection: %lu", selection);
    }
    printf("\n\n");
    return selection;
}

double evaluateWorldState(WorldModel *WM)
{
    double fitness = 0;
    static int lastGoalDiff = 0;
    if (lastGoalDiff != WM->getGoalDiff())
    {
        fitness += 10*sign(WM->getGoalDiff() - lastGoalDiff);
        lastGoalDiff = WM->getGoalDiff();
    }
    static bool wasInOurPossesion = false;
    if (wasInOurPossesion != WM->isBallInOurPossesion())
    {
        if (wasInOurPossesion)
             fitness += -5;
        else fitness += 2;// 2*bool2sign(WM->isBallInOurPossesion());
        wasInOurPossesion = WM->isBallInOurPossesion();
    }
    fitness -= WM->isBallHeadingToGoal();
    printf("\nFITNESS: %f", fitness);
    return fitness;
}
