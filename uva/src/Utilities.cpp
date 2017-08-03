#include "Utilities.h"

template<class T, size_t N> constexpr size_t size(T(&)[N])
{
    return N;
}

pair<unsigned int, unsigned int> getBallZone(WorldModel *WM)
{
    VecPosition ballPosition = WM->getGlobalPosition(OBJECT_BALL);
    double BallX = ballPosition.getX();
    double BallY = ballPosition.getY();
    // VecPosition posBall = WM->getBallPos();
    // printf("\r\n   %f   %f",BallX,BallY);
    double rX[] = {1. / 3, 2. / 3, 1},
                  rY[] = {1. / 3, 2. / 3, 1};
    BallZoneX X;
    BallZoneY Y;

    // for (double r : rX)
    for (int i = 0; i < size(rX); i++)
        if (BallX <= (rX[i] - 1. / 2) * PITCH_LENGTH)
        {
            X = BallZoneX(i);
            break;
        }

    for (int i = 0; i < size(rY); i++)
        if (BallY <= (rY[i] - 1. / 2) * PITCH_WIDTH)
        {
            Y = BallZoneY(i);
            break;
        }

    return make_pair(X, Y);
}

// float gradDesc(r,qi,qf,obj,d0,p0,zeta,eta,qmin,alpha,imax,jmax)
// {
//     i = 1;
//     Q = qi;
//     while i < imax
//         qd = norm(Q(i,:)-qf);
//         if qd < qmin
//             break
//         end
//         Fa = Fatt(r,qf,Q(i,:),d0,zeta);
//         Fr = Frep(r,obj,Q(i,:),p0,eta);
//         t  = tau(r,Q(i,:),Fa,Fr);
//         nt = norm(t);
//         if nt ~= 0
//             dq = Q(i,:) - qf;
//             dq = abs(dq) / norm(dq);
//             Q(i+1,:) = Q(i,:) + alpha * t' / nt .* dq.^3;
// %             q(i+1,:) = q(i,:) + alpha * t' / nt;
//         else
//             Q(i+1,:) = Q(i,:);
//         end
//         i = i+1;
//     end
//     if i == imax
//         warning('Max number of iterations reached.')
//     end
// %     Q = addGoal(qf,Q);
//     Q = rmvneg(r,Q);
//     Q = rmvrep(Q,qmin);
//     Q = upsample(Q,qmin);
//     Q = downsample(Q,jmax);
// }
