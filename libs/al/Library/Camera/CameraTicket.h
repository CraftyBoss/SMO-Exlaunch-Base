#pragma once

#include <al/Library/Placement/PlacementId.h>

namespace al {

    class CameraPoser;

    class CameraTicketId {
    public:
        CameraTicketId(al::PlacementId const*,char const*);
        void isEqual(al::CameraTicketId const&);
        void isEqual(al::CameraTicketId const&,al::CameraTicketId const&);
        void isEqual(al::ByamlIter const&);
        void tryGetObjId(void);
        void getObjId(void);

        al::PlacementId *mPlacement;
        const char *mTicketName;

    };

    class CameraTicket {
    public:
        CameraTicket(CameraPoser *,CameraTicketId const*,int);
        void setPriority(int);

        CameraPoser *mPoser;
        CameraTicketId *mTicketID;
        int mPriority;
        bool unkBool;
    };
}