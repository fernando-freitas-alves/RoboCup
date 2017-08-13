/*
    Copyright (c) 2000-2003, Jelle Kok, University of Amsterdam
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the University of Amsterdam nor the names of its
    contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*! \file PlayerTeams.cpp
    <pre>
    <b>File:</b>          PlayerTest.cpp
    <b>Project:</b>       Robocup Soccer Simulation Team: UvA Trilearn
    <b>Authors:</b>       Jelle Kok
    <b>Created:</b>       10/12/2000
    <b>Last Revision:</b> $ID$
    <b>Contents:</b>      This file contains the class definitions for the
                      Player that are used to test the teams' high level
                      strategy.
    <hr size=2>
    <h2><b>Changes</b></h2>
    <b>Date</b>             <b>Author</b>          <b>Comment</b>
    10/12/2000        Jelle Kok       Initial version created
    </pre>
*/

#include "Player.h"
#include "Utilities.h"

/*! This method is the first complete simple team and defines the actions taken
    by all the players on the field (excluding the goalie). It is based on the
    high-level actions taken by the simple team FC Portugal that it released in
    2000. The players do the following:
    - if ball is kickable
       kick ball to goal (random corner of goal)
    - else if i am fastest player to ball
       intercept the ball
    - else
       move to strategic position based on your home position and pos ball */
SoccerCommand Player::deMeer5()
{
    SoccerCommand soc(CMD_ILLEGAL);
    VecPosition   posAgent = WM->getAgentGlobalPosition();
    VecPosition   posBall  = WM->getBallPos();
    int           iTmp;
    
    // if is before kick off, ...
    if (WM->isBeforeKickOff())
    {
        // if our team has the ball for kick off and PLAYER 9 is in the loop, ...
        if (WM->isKickOffUs() && WM->getPlayerNumber() == 9)
        {
            // (...) if kick the ball is allowable, [KICK BALL W/ MAX SPEED]
            if (WM->isBallKickable())
            {
                VecPosition posGoal(PITCH_LENGTH / 2.0,
                                    (-1 + 2 * (WM->getCurrentCycle() % 2)) *
                                    0.4 * SS->getGoalWidth());
                soc = kickTo(posGoal, 0*SS->getBallSpeedMax());
                Log.log(100, "take kick off");
            }

            // (...) else, [MOVE TO THE BALL]
            else
            {
                soc = intercept(false);
                Log.log(100, "move to ball to take kick-off");
            }

            // ACT->putCommandInQueue(soc);
            // ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            return soc;
        }
//if (WM->getPlayerNumber() == 1 && WM->getSide() == SIDE_RIGHT) { /*printf("\r\nno. 1\r\n"); */  ACT->putCommandInQueue(soc = teleportToPos(VecPosition(20,0))); } else {
        // if not in kick off formation, [GO TO kick_off FORMATION]
        if (formations->getFormation() != FT_INITIAL ||
            posAgent.getDistanceTo(WM->getStrategicPosition()) > 2.0)
        {
            formations->setFormation(FT_INITIAL);
            ACT->putCommandInQueue(soc = teleportToPos(WM->getStrategicPosition()));
        }

        // else, [TURN BODY TO MIDDLE CENTER]
        else
        {
            ACT->putCommandInQueue(soc = turnBodyToPoint(VecPosition(0, 0), 0));
            ACT->putCommandInQueue(alignNeckWithBody());
        }
//}
    }

    // else if not kick off, ...
    else
if (WM->getCurrentCycle() % 1 == 0)// && !(WM->getPlayerNumber() == 1 && WM->getSide() == SIDE_RIGHT))
    {
        formations->setFormation(FT_433_OFFENSIVE);
        soc.commandType = CMD_ILLEGAL;

        // if ball pos unknown, [SEARCH BALL]
        if (WM->getConfidence(OBJECT_BALL) < PS->getBallConfThr())
        {
            ACT->putCommandInQueue(soc = searchBall());
            ACT->putCommandInQueue(alignNeckWithBody());
        }

        // else if ball is kickable, [KICK BALL W/ MAX SPEED]
        else if (WM->isBallKickable())
        {
            // VecPosition posGoal(PITCH_LENGTH / 2.0,
            //                     (-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth());
            // soc = kickTo(posGoal, SS->getBallSpeedMax());
            double conf =  0.5, // Minimum confidence
                   da0  = 20,   // Region of influence of attractive potential
                   dr0  = 10,   // Region of influence of repulsive potential (obstacles)
                   ka   = 12,   // Influence strength of attractive potential
                   kr   = 12,   // Influence strength of repulsive potential (obstacles)
                   k    =  1,   // Step size of iteration
                   Fmin =  8;   // Minimum force
            pair <uint, VecPosition> gd = gradDesc(this, WM, conf, da0, dr0, ka, kr, k, Fmin);
                                             // PS->getPlayerConfThr());
            switch (gd.first)
            {
                case 0:
                {
                    printf("\r\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                    printf("\r\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                    printf("\r\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                    printf("\r\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                    printf("\r\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                    printf("\r\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                    ObjectT clTm = getClosestInFieldInSetTo(WM, OBJECT_SET_TEAMMATES, WM->getAgentObjectType(), NULL, 0.5);
                    printf("\r\nClosest obj: %d", clTm);
                    VecPosition posClTm = WM->getGlobalPosition(clTm);
                    if (WM->isInField(posClTm, 0))
                    {
                        printf("\r\n IS IN FIELD");
                        printf("\r\nobj:\t\t%d", clTm - OBJECT_TEAMMATE_1 + 1);
                        printf("\r\npos:\t\t"); posClTm.show();
                        soc = directPass(posClTm, PASS_FAST);
                        break;
                    }
                    else printf("\r\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                }
                case 1:
                {
                    printf("\r\nKicking...");
                    VecPosition posTarget = gd.second;
                    printf("\r\nfrom pos:\t"); WM->getGlobalPosition(WM->getAgentObjectType()).show();
                    printf("to pos:\t\t"); posTarget.show();
                    soc = kickTo(posTarget, 0);//0.01*SS->getBallSpeedMax());
                    // soc = kickBallCloseToBody(angle, 1);
                    // break;
                }
            }
            ACT->putCommandInQueue(soc);
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            Log.log(100, "kick ball");
        }

        // else if fastest to ball, ...
        else if (WM->getFastestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp)
                 == WM->getAgentObjectType()  && !WM->isDeadBallThem())
        {
            Log.log(100, "I am fastest to ball; can get there in %d cycles", iTmp);
            soc = intercept(false); // action: intercept the ball

            // (...) if stamina is low, [DASH SLOW]
            if (soc.commandType == CMD_DASH &&
                WM->getAgentStamina().getStamina() <
                SS->getRecoverDecThr()*SS->getStaminaMax() + 200)
            {
                soc.dPower = 30.0 * WM->getAgentStamina().getRecovery();
                ACT->putCommandInQueue(soc);
                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }

            // (...) else if stamina is high, [DASH AS INTENDED]
            else
            {
                ACT->putCommandInQueue(soc);
                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }
        }

        // else if not near strategic pos, ...
        else if (posAgent.getDistanceTo(WM->getStrategicPosition()) >
                 1.5 + fabs(posAgent.getX() - posBall.getX()) / 10.0)
        {
            // (...) if stamina high, [MOVE TO STRATEGIC POS]
            if (WM->getAgentStamina().getStamina() >
                SS->getRecoverDecThr()*SS->getStaminaMax() + 800)
            {
                soc = moveToPos(WM->getStrategicPosition(),
                                PS->getPlayerWhenToTurnAngle());
                ACT->putCommandInQueue(soc);
                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }

            // (...) else, [WATCH THE BALL]
            else
            {
                ACT->putCommandInQueue(soc = turnBodyToObject(OBJECT_BALL));
                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }
        }

        // else if ball is watchable, [WATCH THE BALL]
        else if (fabs(WM->getRelativeAngle(OBJECT_BALL)) > 1.0)
        {
            ACT->putCommandInQueue(soc = turnBodyToObject(OBJECT_BALL));
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
        }

        // else, [NOTHING TO DO]
        else
            ACT->putCommandInQueue(SoccerCommand(CMD_TURNNECK, 0.0));
    }

    return soc;
}

/*! This method is a simple goalie based on the goalie of the simple Team of
    FC Portugal. It defines a rectangle in its penalty area and moves to the
    position on this rectangle where the ball intersects if you make a line
    between the ball position and the center of the goal. If the ball can
    be intercepted in the own penalty area the ball is intercepted and catched.
*/
SoccerCommand Player::deMeer5_goalie()
{
    int i;
    SoccerCommand soc;
    VecPosition   posAgent = WM->getAgentGlobalPosition();
    AngDeg        angBody  = WM->getAgentGlobalBodyAngle();
    // define the top and bottom position of a rectangle in which keeper moves
    static const VecPosition posLeftTop(-PITCH_LENGTH / 2.0 +
                                        0.7 * PENALTY_AREA_LENGTH, -PENALTY_AREA_WIDTH / 4.0);
    static const VecPosition posRightTop(-PITCH_LENGTH / 2.0 +
                                         0.7 * PENALTY_AREA_LENGTH, +PENALTY_AREA_WIDTH / 4.0);
    // define the borders of this rectangle using the two points.
    static Line  lineFront = Line::makeLineFromTwoPoints(posLeftTop, posRightTop);
    static Line  lineLeft  = Line::makeLineFromTwoPoints(
                                 VecPosition(-50.0, posLeftTop.getY()), posLeftTop);
    static Line  lineRight = Line::makeLineFromTwoPoints(
                                 VecPosition(-50.0, posRightTop.getY()), posRightTop);

    if (WM->isBeforeKickOff())
    {
        if (formations->getFormation() != FT_INITIAL || // not in kickoff formation
            posAgent.getDistanceTo(WM->getStrategicPosition()) > 2.0)
        {
            formations->setFormation(FT_INITIAL);         // go to kick_off formation
            ACT->putCommandInQueue(soc = teleportToPos(WM->getStrategicPosition()));
        }
        else                                            // else turn to center
        {
            ACT->putCommandInQueue(soc = turnBodyToPoint(VecPosition(0, 0), 0));
            ACT->putCommandInQueue(alignNeckWithBody());
        }

        return soc;
    }

    if (WM->getConfidence(OBJECT_BALL) < PS->getBallConfThr())
    {
        // confidence ball too  low
        ACT->putCommandInQueue(searchBall());          // search ball
        ACT->putCommandInQueue(alignNeckWithBody());
    }
    else if (WM->getPlayMode() == PM_PLAY_ON || WM->isFreeKickThem() ||
             WM->isCornerKickThem())
    {
        if (WM->isBallCatchable())
        {
            ACT->putCommandInQueue(soc = catchBall());
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
        }
        else if (WM->isBallKickable())
        {
            soc = kickTo(VecPosition(0, posAgent.getY() * 2.0), 2.0);
            ACT->putCommandInQueue(soc);
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
        }
        else if (WM->isInOwnPenaltyArea(getInterceptionPointBall(&i, true)) &&
                 WM->getFastestInSetTo(OBJECT_SET_PLAYERS, OBJECT_BALL, &i) ==
                 WM->getAgentObjectType())
        {
            ACT->putCommandInQueue(soc = intercept(true));
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
        }
        else
        {
            // make line between own goal and the ball
            VecPosition posMyGoal = (WM->getSide() == SIDE_LEFT)
                                    ? SoccerTypes::getGlobalPositionFlag(OBJECT_GOAL_L, SIDE_LEFT)
                                    : SoccerTypes::getGlobalPositionFlag(OBJECT_GOAL_R, SIDE_RIGHT);
            Line lineBall = Line::makeLineFromTwoPoints(WM->getBallPos(), posMyGoal);
            // determine where your front line intersects with the line from ball
            VecPosition posIntersect = lineFront.getIntersection(lineBall);

            // outside rectangle, use line at side to get intersection
            if (posIntersect.isRightOf(posRightTop))
                posIntersect = lineRight.getIntersection(lineBall);
            else if (posIntersect.isLeftOf(posLeftTop))
                posIntersect = lineLeft.getIntersection(lineBall);

            if (posIntersect.getX() < -49.0)
                posIntersect.setX(-49.0);

            // and move to this position
            if (posIntersect.getDistanceTo(WM->getAgentGlobalPosition()) > 0.5)
            {
                soc = moveToPos(posIntersect, PS->getPlayerWhenToTurnAngle());
                ACT->putCommandInQueue(soc);
                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }
            else
            {
                ACT->putCommandInQueue(soc = turnBodyToObject(OBJECT_BALL));
                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }
        }
    }
    else if (WM->isFreeKickUs() == true || WM->isGoalKickUs() == true)
    {
        if (WM->isBallKickable())
        {
            if (WM->getTimeSinceLastCatch() == 25 && WM->isFreeKickUs())
            {
                // move to position with lesser opponents.
                if (WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,
                                           Circle(posRightTop, 15.0)) <
                    WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,
                                           Circle(posLeftTop,  15.0)))
                    soc.makeCommand(CMD_MOVE, posRightTop.getX(), posRightTop.getY(), 0.0);
                else
                    soc.makeCommand(CMD_MOVE, posLeftTop.getX(), posLeftTop.getY(), 0.0);

                ACT->putCommandInQueue(soc);
            }
            else if (WM->getTimeSinceLastCatch() > 28)
            {
                soc = kickTo(VecPosition(0, posAgent.getY() * 2.0), 2.0);
                ACT->putCommandInQueue(soc);
            }
            else if (WM->getTimeSinceLastCatch() < 25)
            {
                VecPosition posSide(0.0, posAgent.getY());

                if (fabs((posSide - posAgent).getDirection() - angBody) > 10)
                {
                    soc = turnBodyToPoint(posSide);
                    ACT->putCommandInQueue(soc);
                }

                ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
            }
        }
        else if (WM->isGoalKickUs())
        {
            ACT->putCommandInQueue(soc = intercept(true));
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
        }
        else
            ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
    }
    else
    {
        ACT->putCommandInQueue(soc = turnBodyToObject(OBJECT_BALL));
        ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
    }

    return soc;
}
