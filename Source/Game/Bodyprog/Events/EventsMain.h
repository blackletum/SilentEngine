#pragma once

namespace Silent::Game
{
    struct s_MapPoint2d;

    void Event_Update(bool disableButtonEvents);

    bool Event_CollideFacingCheck(s_MapPoint2d* mapPoint);

    bool Event_CollideObbFacingCheck(s_MapPoint2d* mapPoint);

    bool Event_CollideObbCheck(s_MapPoint2d* mapPoint);
}
